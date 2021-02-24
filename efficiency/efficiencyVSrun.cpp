/* Riccardo Ricci
 created in 2021, January 11th
 

 ::::::::::::::::
 efficiencyVSrun.cpp
 ::::::::::::::::
GENERAL STRUCTURE: 
    1. "if" loop to scan inside the targeted folder searching for .root files
        2. internal "while" cycle to loop over each .root file
            3. a) sub-internal "if" to select only certain files depending on their name.  
               b) clusters extraction and plotting


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 INSTRUCTIONS
 launch these macros from the main ./ folder. 

 1. Open ROOT on your terminal
 2. ".L ./efficiency/efficiencyVSrun.cpp" 
 3. execute the function by calling it: "efficiencyVSrun()"

 It is analogously possible to use a ROOT C++ notebook (SWAN, Jupyter) and run the same commands
 (use .L or the #include "./cluster/clusterVSrun.cpp" depending on your preferences)
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/






void efficiencyVSrun(const char *dirname = "./_data_/August_BENT/", const char *ext = ".root"){
    
    cout << "Looking for analysis.root files..." << endl;
    vector <double> efficiency_vector;
    vector <double> eff_err_up; // globally declared vector in which i will save value of eTotalEfficiency
    vector <double> eff_err_low;
        
    //store array of .root filenames
    TEfficiency *eff_run = new TEfficiency;
    vector <string> run_number;  
	TCanvas *canvas;	//here i will save the names of my root file for many different uses
    TSystemDirectory dir(dirname, dirname); 
    TList *files = dir.GetListOfFiles();
    // :::::::::::::  ::::::::::::::::::::::: :::::::::::::::::::::::: //

        
        
    //:::::::::::::::::   if-while external block - I/O PART     :::::::::::::::::::: //
    if (files) {
        TSystemFile *file;
        TString fname;
        TFile *file_to_open; // pointer: initialized with a new file.root at each loop
        TIter next(files);   // iterator
        
         while ((file = (TSystemFile *) next())) {
            fname = file->GetName();
            if (!file->IsDirectory() && fname.EndsWith(ext) && fname.BeginsWith("analysis")) {				
				// extract only run number and ADD it to run_number vector
				string buffer_string = fname.Data();
				buffer_string.replace(0,12,"");
				buffer_string.replace(9,22,"");
                run_number.push_back(buffer_string);
                
                //these lines show the .root file(s) content
                file_to_open = new TFile(dirname+fname);   // dirname+fname = "./path/to/your_file.root"
                
                // file_to_open->ls(); // wanna see the folder content? uncomment this
                file_to_open->cd("AnalysisEfficiency;1/ALPIDE_3;"); // for test August data
                
                //gDirectory->ls(); wanna see folder content? uncomment these 2 lines
                //cout << endl << endl; 
                

             
			 
	//::::::::::: EFFICIENCY EXTRACTION ::::::::::::::::::::::: //
	TEfficiency *Eff;
    gDirectory->GetObject("eTotalEfficiency", Eff);             
                efficiency_vector.push_back(Eff->GetEfficiency(1));    // Eff value
                eff_err_up.push_back(Eff->GetEfficiencyErrorUp(1));    // Eff value
                eff_err_low.push_back(Eff->GetEfficiencyErrorLow(1));    // Eff value
                // fit legend
                TLegend *legend = new TLegend(0.48,0.8,0.88,0.88);

    
    canvas = new TCanvas ("c1", "eTotalEfficiency", 200, 10, 750, 500);
    Eff->Draw();            
    canvas->Draw();

    //eventually:         
    //print canvas as .png file in ./efficiency/ folder
    //TString png = ".png";
    //TString path = "./efficiency/";
	//TString short_name = buffer_string; // "#run name"
    //TString canvas_file = path + short_name + png;
                //canvas->Print(canvas_file);
 //::::::::::: EFFICIENCY EXTRACTION ::::  END  ::::::::::::::::::: //

                


            }// END INTERNAL IF
        }// END WHILE
    } // END IF
	else {
        cout << "No analysis.root files found. Change the path in efficiencyVSrun.cpp" << endl;
    }// END ELSE
    

    
        ///////// print on .csv file
     ofstream of("./efficiency/TotalEfficiencyVSrun.csv");
        int n = run_number.size(); // #runs  
        if(n>1) {cout << endl << n << " runs have been found! Find the outputs in ./efficiency/ folder." << endl << endl;};
        
        for (int i = 0; i < n; ++i)
        //filling .csv file
        {of << run_number[i] << "," << efficiency_vector[i] << "," << "0" << "," << eff_err_up[i] << "," << endl;};

    delete files;    
}// END