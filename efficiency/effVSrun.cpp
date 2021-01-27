// Riccardo Ricci
// 2020, January 11th
//Updated January 14th, 2021

//this only_1_function - macro is made of 2 blocks
// the "external one" is essentially an "if + while loop" (you will find this structure also in other macros) which finds every file .root in dirname, 
    // where dirname = ./path/to/file of interest
    // ext is the selected file extension - .root in the following case


// vector<TCanvas> *BigCanva; //array of canvas
vector <double> efficiency_vector; // globally declared vector in which i will save value of eTotalEfficiency
vector <double> eff_err_up; // globally declared vector in which i will save value of eTotalEfficiency
vector <double> eff_err_low;



// :::::::::::::  FIRST DEFINITIONSSSS :::::::::::::::::::::::: //
    vector <string> TotalEfficiencyVSrun(const char *dirname = "./_data_/August_BENT/", const char *ext = ".root"){
    cout << "Looking for .root files..." << endl;
    //store array of .root filenames
    TEfficiency *eff_run = new TEfficiency;
    vector <string> arr;  
	TCanvas *canvas;	//here i will save the names of my root file for many different uses
    TSystemDirectory dir(dirname, dirname); //directory, but in ROOT language
    TList *files = dir.GetListOfFiles();
        int counter = 0;
        
            
    // ::: .csv file to be read by a TGraph ::: //
        TString runs[9] = {
                    "407",
                    "408",
                    "409",               
                    "410",
                    "411"
						};
        
    
        
        
//:::::::::::::::::   if-while external block :::::::::::::::::::: //
    if (files) {
        TSystemFile *file;
        TString fname;
        TFile *file_to_open; // pointer: initialized with a new file.root at each loop
        TIter next(files);   // iterator
        
        while ((file = (TSystemFile *) next())) {
            fname = file->GetName();
            if (!file->IsDirectory() && fname.EndsWith(ext)) {
                //add only .root files to arr, using "ext"
                arr.push_back(fname.Data());
                
                //these lines show the .root file(s) content
                file_to_open = new TFile(dirname+fname);   // dirname+fname = "./path/to/your_file.root"
                
                // file_to_open->ls(); // wanna see the folder content? uncomment this
                //file_to_open->cd("AnalysisEfficiency;1/pALPIDEfs_3;1"); // for June data
                file_to_open->cd("AnalysisEfficiency;1/ALPIDE_3;1"); // for test August data uncomment this
                gDirectory->ls();
                cout << endl << endl; 
                
                
                

                //:: INTERNAL BLOCK ::// 
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
   
             
      //print canvas as .png file in ./cluster/ folder
    TString png = ".png";
                TString path = "./efficiency/";
    TString canvas_file = path + runs[counter] + png;
                canvas->Print(canvas_file);
                counter ++;

                
 //::::::::::: EFFICIENCY EXTRACTION ::::  END  ::::::::::::::::::: //

                
            }
        }
    } else {
        cout << "No .root files found. Change the path in rnAnalysis.cc" << endl;
    }
    

    
        ///////// print on .csv file
     ofstream of("./efficiency/TotalEfficiencyVSrun.csv");
       int n = arr.size();
     for (int i = 0; i < n; ++i)
             // .csv file with 
          of << runs[i] << "," << efficiency_vector[i] << "," << "0" << "," << eff_err_up[i] << "," << endl;
   
    counter++; //increment this counter to 
    delete files;
    return arr;
    
    
}