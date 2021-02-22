/* Riccardo Ricci
 created in 2021, January 9th
 

 ::::::::::::::::
 clusterVSrun.cpp
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
 2. ".L ./cluster/clusterVSrun.cpp" 
 3. execute the function by calling it: "clusterVSrun()"

 It is analogously possible to use a ROOT C++ notebook (SWAN, Jupyter) and run the same commands
 (use .L or the #include "./cluster/clusterVSrun.cpp" depending on your preferences)
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/



vector <double> MPV; // vector in which i will save MPV of ClusterSizeAssociated
vector <double> ClusterMean; 

void clusterVSrun(const char *dirname = "./_data_/August_BENT/", const char *ext = ".root"){
    cout << "Looking for .root files..." << endl;
    //store array of .root filenames
    vector <string> run_number;             //here i will save the names of my root file for many different uses
    TSystemDirectory dir(dirname, dirname); //directory, but in ROOT language
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

            //:: INTERNAL-LOOP BLOCK ::// 
            if (!file->IsDirectory() && fname.EndsWith(ext) && fname.BeginsWith("analysis")) {				
				// extract only run number and ADD it to run_number vector
				string buffer_string = fname.Data();
				buffer_string.replace(0,12,"");
				buffer_string.replace(9,22,"");
                run_number.push_back(buffer_string);

                
                //these lines show the .root file(s) content
                file_to_open = new TFile(dirname+fname);   // dirname+fname = "./path/to/your_file.root"
                
                // file_to_open->ls(); // wanna see the folder content? uncomment this
                file_to_open->cd("AnalysisDUT;1/ALPIDE_3;1"); // for test August data
                
                //gDirectory->ls(); wanna see folder content? uncomment these 2 lines
                //cout << endl << endl; 
                
                
                
			 
                //:::::::::::: CLUSTER_SIZE EXTRACTION ::::::::::::::::::::::: //
                //define some pointers for the 2 histos
                TH1F *CS;
                    gDirectory->GetObject("clusterSizeAssociated", CS);
                                
                                
                    //fit
                    CS->Fit("landau");
                    CS->GetFunction("landau")->SetLineColor(2);
                    CS->GetFunction("landau")->SetLineStyle(2);
                    CS->GetYaxis()->SetRangeUser(0,80000);
                        ClusterMean.push_back(CS->GetMean());

                    
                // :::::::::::::::   07/01/2021	:::::	FIT VALUES EXTRACTION :::::::::::::::::::::: //
                TF1 *landau_fit = CS -> GetFunction ("landau"); // CS = "ClusterSize"                      
                    cout << landau_fit -> GetMaximum() << endl;
                        MPV.push_back(landau_fit -> GetParameter(1));    // MPV
                            
                        // fit legend
                        TLegend *legend = new TLegend(0.48,0.8,0.88,0.88);                     
                        gStyle->SetOptFit(1011); // to see fit parameters on the legend
                // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: //
                           
                                
                                
                                
                // :::::::::::::::::::::: PLOTTING & PRINTING :::::::::::::::::::::::::::::::: //
                TCanvas *canvas = new TCanvas ("c1", "Cluster Size Associated", 200, 10, 750, 500);
                CS->Draw();
                canvas->Draw();
                        
                            
                    //print canvas as .png file in "./cluster/" folder
                    TString png = ".png";
                    TString path = "./cluster/";
                    TString short_name = buffer_string; // "#run name"
                    TString canvas_file = path + short_name + png;
                            canvas->Print(canvas_file);
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: // 
                // :::::::::: CLUSTER_SIZE EXTRACTION ::::  END  :::::::::::::::::: //



            }//end internal if
        }//end while
    }// end external if 
        else {
            cout << "No analysis.root files found. Change the targeted path. Quitting..." << endl;
            return 0;
    }//end else
    
        
        
    
// ::: runs to be written in a .csv file, to be read by a TGraph ::: //
     ofstream of("./cluster/ClusterSizeAssociatedVSrun.csv"); // output stream to new.csv file
         int n = run_number.size(); // #runs  
            cout << "n_run_numbers: "<< n << endl;
         for (int i = 0; i < n; ++i)
                       {of << run_number[i] << "," << MPV[i] << endl;} // better to use MPV and not mean for now
						//{of << run_number[i] << "," << ClusterMean[i] << endl;}
 for (auto x : ClusterMean) cout << x << endl;
        
        
    delete files;
	}// END




