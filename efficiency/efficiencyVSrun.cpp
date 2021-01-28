// Riccardo Ricci
// 2021, January 11th
//Updated January 27th, 2021

//this only_1_function - macro is made of 2 blocks
// the "external one" is essentially an "if + while loop" (you will find this structure also in other macros) which finds every file .root in dirname, 
    // where dirname = ./path/to/file of interest
    // ext is the selected file extension - .root in the following case




// vector<TCanvas> *BigCanva; //array of canvas
vector <double> efficiency_vector; // globally declared vector in which i will save value of eTotalEfficiency
vector <double> eff_err_up; // globally declared vector in which i will save value of eTotalEfficiency
vector <double> eff_err_low;



// :::::::::::::  FIRST DEFINITIONSSSS :::::::::::::::::::::::: //
    vector <string> efficiencyVSrun(const char *dirname = "../_data_/August_BENT/", const char *ext = ".root"){
    cout << "Looking for .root files..." << endl;
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
            if (!file->IsDirectory() && fname.EndsWith(ext)) {				
				// extract only run number and ADD it to run_number vector
				string buffer_string = fname.Data();
				buffer_string.replace(0,12,"");
				buffer_string.replace(9,22,"");
                run_number.push_back(buffer_string);
                
                //these lines show the .root file(s) content
                file_to_open = new TFile(dirname+fname);   // dirname+fname = "../path/to/your_file.root"
                
                // file_to_open->ls(); // wanna see the folder content? uncomment this
                file_to_open->cd("AnalysisEfficiency;1/ALPIDE_3;1"); // for test August data
                
                //gDirectory->ls(); wanna see folder content? uncomment these 2 lines
                //cout << endl << endl; 
                

             //:: INTERNAL-LOOP BLOCK :://
			 
//::::::::::: EFFICIENCY EXTRACTION ::::::::::::::::::::::: //
//define some pointers for the 2 histos
TEfficiency *Eff;
//passing clustersSizeAssociated,clustersSizeAssociatedNormalized to the respective pointers
    gDirectory->GetObject("eTotalEfficiency", Eff);             
    cout << Eff->GetEfficiency(1) << endl;
    
                efficiency_vector.push_back(Eff->GetEfficiency(1));    // Eff value
                eff_err_up.push_back(Eff->GetEfficiencyErrorUp(1));    // Eff value
                eff_err_low.push_back(Eff->GetEfficiencyErrorLow(1));    // Eff value
                // fit legend
                TLegend *legend = new TLegend(0.48,0.8,0.88,0.88);
   //legend->SetHeader("The Legend Title","C"); // option "C" allows to center the header
    //legend->AddEntry(landau_fit);
    //legend->Draw();
      //canvas->BuildLegend();          
                
                
                //Finally plot please
    
    canvas = new TCanvas ("c1", "eTotalEfficiency", 200, 10, 750, 500);
    //canvas->cd(1);
    Eff->Draw();            
    canvas->Draw();
            //gStyle->SetOptFit(1011); // to see fit parameters on the legend
   
             
      //print canvas as .png file in ../cluster/ folder
    TString png = ".png";
    TString path = "../efficiency/";
	TString short_name = buffer_string; // "#run name"
    TString canvas_file = path + short_name + png;
                canvas->Print(canvas_file);
               

                
 //::::::::::: EFFICIENCY EXTRACTION ::::  END  ::::::::::::::::::: //

                
            }
        }
    } else {
        cout << "No .root files found. Change the path in rnAnalysis.cc" << endl;
    }
    

    
        ///////// print on .csv file
     ofstream of("../efficiency/TotalEfficiencyVSrun.csv");
       int n = run_number.size();
     for (int i = 0; i < n; ++i)
             // .csv file with 
          of << run_number[i] << "," << efficiency_vector[i] << "," << "0" << "," << eff_err_up[i] << "," << endl;
   

    delete files;
    return run_number;
    
    
}