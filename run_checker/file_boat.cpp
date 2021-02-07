// Riccardo Ricci
// created in February 2nd, 2021

// TheFileBoat 
// Collection of 3 macros devoted to 
// ROOT I/O tasks and open files/store array of files contained in the selected folder


// INSTRUCTIONS
// launch these macros from the main ./ folder. 

// 1. Open ROOT on your terminal
// 2. ".L ./run_checker/file_boat.cpp"
// 3. execute one of the three functions by calling them: "function()"



////////////////////   PREALIGNMENT-START  ///////////////////////////
void open_prealignment(const char* dirname = "./_data_/August_BENT/", const char *ext = ".root"){
        
		// this vector strings will contain the names of the .root file of interest
		// the use of vector string allows for further modifications in the future evetually
		vector <string> run_number;
		
		TSystemDirectory dir(dirname, dirname); //directory, but in ROOT language
		TList *files = dir.GetListOfFiles();


//:::::::::::::::::   if-while external block :::::::::::::::::::: //
// inside this piece of code i will finaly make a list of .root files to open.
    if (files){
        TSystemFile *file;
        TString fname;
        TFile *file_to_open; 
        TIter next(files);   
        
		
		// this annidated while-loop selects the name of each file and initializes it. 
        while ((file = (TSystemFile *) next())){
            fname = file->GetName();
            cout << "Looking for .root files..." << endl;
				
// from now on, there are 3 different blocks per each filename & filetype to be open/analyzed	

            if (!file->IsDirectory() && fname.EndsWith(ext) && fname.BeginsWith("prealignment")){
				// extract only run number and ADD it to run_number vector
				string run_number_ith = fname.Data();
				run_number_ith.replace(0,16,""); // PREALIGNMENT
				run_number_ith.replace(9,22,""); // ALL
                run_number.push_back(run_number_ith);
				TString buffer = run_number_ith;

                //OPEN .root file then:
                file_to_open = new TFile(dirname+fname);
                // file_to_open->ls(); // wanna see the folder content? uncomment this line            
                
				
				{gFile->cd("Prealignment/ALPIDE_3");
				cout << "prealignment is OK" << endl;


// extract correlations
                TH1F *correlationX;
                    gDirectory->GetObject("correlationX",correlationX);
                TH1F *correlationY;
                    gDirectory->GetObject("correlationY",correlationY);
                TH2F *correlationX_2D;
                    gDirectory->GetObject("correlationX_2Dlocal",correlationX_2D);
                TH2F *correlationY_2D;
                    gDirectory->GetObject("correlationY_2Dlocal",correlationY_2D);
                
                //draw 
                TCanvas *canvas = new TCanvas ("c1", "prealignment - run" + buffer, 200, 10, 2400, 1400);
                canvas -> Divide (2, 2);
                
                canvas->cd(1)->SetRightMargin(0.09);
                canvas->cd(1)->SetLeftMargin(0.15);
                canvas->cd(1)->SetBottomMargin(0.15);
                
                canvas->cd(2)->SetRightMargin(0.09);
                canvas->cd(2)->SetLeftMargin(0.15);
                canvas->cd(2)->SetBottomMargin(0.15);

                canvas->cd(3)->SetRightMargin(0.09);
                canvas->cd(3)->SetLeftMargin(0.15);
                canvas->cd(3)->SetBottomMargin(0.15);

                canvas->cd(4)->SetRightMargin(0.09);
                canvas->cd(4)->SetLeftMargin(0.15);
                canvas->cd(4)->SetBottomMargin(0.15);

                
                canvas->cd(1);
                correlationX->Fit("gaus");
                //correlationX->GetXaxis()->SetRangeUser(-9,-6);
                correlationX->GetXaxis()->SetLabelSize(0.05);
                correlationX->GetYaxis()->SetLabelSize(0.05);
                gStyle->SetOptFit(1011); // to see fit parameters on the legend
                correlationX->Draw();
                canvas->cd(1)->Draw();
                
                canvas->cd(2);
                gStyle->SetOptFit(1011); // to see fit parameters on the legend
                correlationY->GetXaxis()->SetLabelSize(0.05);
                correlationY->GetYaxis()->SetLabelSize(0.05);
                //correlationY->GetXaxis()->SetRangeUser(-4,2);
                correlationY->Fit("gaus");
                correlationY->Draw();
                canvas->cd(2)->Draw();
                
                canvas->cd(3);
                correlationX_2D->GetXaxis()->SetLabelSize(0.04);
                correlationX_2D->GetYaxis()->SetLabelSize(0.04);
                correlationX_2D->Draw("colz");
                canvas->cd(3)->Draw();
                
                canvas->cd(4);
                correlationY_2D->GetXaxis()->SetLabelSize(0.05);
                correlationY_2D->GetYaxis()->SetLabelSize(0.05);
                correlationY_2D->Draw("colz");
                canvas->cd(4)->Draw();
                
                // print
                canvas->Print("./run_checker/run"+buffer+"_prealignment_DUTcorrelations.png");}           		
	
			} //end internal if
			// ELSE IN CASE OF EMPTY FOLDER????
			
		}//end while
	}//end external if
for(auto x:run_number) cout << x << endl;


}
////////////////////   PREALIGNMENT-END  ///////////////////////////
//
//
//
//
//
//
////////////////////   ALIGNMENT-START  ///////////////////////////
void open_alignment(const char* dirname = "./_data_/August_BENT/", const char *ext = ".root"){
        
		// this vector strings will contain the names of the .root file of interest
		// the use of vector string allows for further modifications in the future evetually
		vector <string> run_number;
		
		TSystemDirectory dir(dirname, dirname); //directory, but in ROOT language
		TList *files = dir.GetListOfFiles();


//:::::::::::::::::   if-while external block :::::::::::::::::::: //
// inside this piece of code i will finaly make a list of .root files to open.
    if (files){
        TSystemFile *file;
        TString fname;
        TFile *file_to_open; 
        TIter next(files);   
        
		
		// this annidated while-loop selects the name of each file and initializes it. 
        while ((file = (TSystemFile *) next())){
            fname = file->GetName();
            cout << "Looking for .root files..." << endl;
				
// from now on, there are 3 different blocks per each filename & filetype to be open/analyzed	

            if (!file->IsDirectory() && fname.EndsWith(ext) && fname.BeginsWith("alignment") && fname.BeginsWith("pre")==false){
				// extract only run number and ADD it to run_number vector
				string run_number_ith = fname.Data();
				run_number_ith.replace(0,13,""); // ALIGNMENT
				run_number_ith.replace(9,22,""); // ALL
                run_number.push_back(run_number_ith);
				TString buffer = run_number_ith;

                //OPEN .root file then:
                file_to_open = new TFile(dirname+fname);
				
                //file_to_open->ls(); // wanna see the folder content? uncomment this line            
                
				//not implemented yet
				//{gFile->cd("Prealignment/ALPIDE_3");
				//cout << "Alignent is OK" << endl; 
				//}
								
				
					
			} //end internal if
		}//end while
	}//end external if
	cout << endl << "checked runs are: " << endl;
for(auto x:run_number) cout << x << endl;
} // end function
////////////////////   ALIGNMENT-END  ///////////////////////////
//
//
//
//
//
//
////////////////////   ANALYSIS-START  ///////////////////////////
void open_analysis(const char* dirname = "./_data_/August_BENT/", const char *ext = ".root"){
        
		// this vector strings will contain the names of the .root file of interest
		// the use of vector string allows for further modifications in the future evetually
		vector <string> run_number;
		TSystemDirectory dir(dirname, dirname); //directory, but in ROOT language
		TList *files = dir.GetListOfFiles();


//:::::::::::::::::   if-while external block :::::::::::::::::::: //
// inside this piece of code i will finaly make a list of .root files to open.
    if (files){
        TSystemFile *file;
        TString fname;
        TFile *file_to_open; 
        TIter next(files);   
        
		
		// this annidated while-loop selects the name of each file and initializes it. 
        while ((file = (TSystemFile *) next())){
            fname = file->GetName(); 
            cout << "Looking for .root files..." << endl;
				
// from now on, there are 3 different blocks per each filename & filetype to be open/analyzed	

            if (!file->IsDirectory() && fname.EndsWith(ext) && fname.BeginsWith("analysis")){
				// extract only run number and ADD it to run_number vector
				string run_number_ith = fname.Data();
				run_number_ith.replace(0,13,""); // ANALYSIS
				run_number_ith.replace(9,22,""); // ALL
                run_number.push_back(run_number_ith);
				TString buffer = run_number_ith;
				TCanvas *canvas;

                //OPEN .root file then:     
                file_to_open = new TFile(dirname+fname);
                file_to_open->ls(); // wanna see the folder content? uncomment this line            
                
				
/* 				{gFile->cd("AnalysisDUT;1/ALPIDE_3;1");
                TH1F *residualsX;
                TH1F *residualsY;
                //assing residualsX,Y to the respective pointers
                    gDirectory->GetObject("residualsX", residualsX);
                    gDirectory->GetObject("residualsY", residualsY);

                    residualsX->GetXaxis()->SetTitleSize(0.05);
                    residualsX->GetYaxis()->SetTitleSize(0.05);
               
                    residualsY->GetXaxis()->SetTitleSize(0.05);
                    residualsY->GetYaxis()->SetTitleSize(0.05);
           
		   
				//draw and print
                canvas = new TCanvas ("c1", "Residuals X,Y", 200, 10, 1300, 500);
                canvas -> Divide (2, 1);
               
                canvas->cd(1)->SetRightMargin(0.09);
                canvas->cd(1)->SetLeftMargin(0.25);
                canvas->cd(1)->SetBottomMargin(0.25);
                
                canvas->cd(2)->SetRightMargin(0.09);
                canvas->cd(2)->SetLeftMargin(0.25);
                canvas->cd(2)->SetBottomMargin(0.25);
                
                    canvas->cd(1);
                    residualsX->Draw();

                    canvas->cd(2);
                    residualsY->Draw();
                    canvas->Draw();
                    canvas->Print("./run_checker/run"+buffer+"_residualsXY.png");
				//::::::::::: RESIDUALS EXTRACTION ::::  END  ::::::::::::::::::: //
                //
				//
                //
                //
                //
                //
                //::::::::::: DETECTOR TOTAL EFFICIENCY EXTRACTION ::::::::::::::::::::::: //
                TEfficiency *Eff;
                gFile->cd("AnalysisEfficiency/ALPIDE_3");
                gDirectory->GetObject("eTotalEfficiency", Eff);             
                    canvas = new TCanvas ("c1", "eTotalEfficiency", 200, 10, 750, 500);
                    canvas->SetRightMargin(0.09);
                    canvas->SetLeftMargin(0.25);
                    canvas->SetBottomMargin(0.25);
                
                    Eff->Draw();            
                    canvas->Draw();
                    canvas->Print("./run_checker/run"+buffer+"_totalEfficiency.png");
                    
                
				
				
                //::::::::::: DETECTOR EFFICIENCY MAP EXTRACTION ::::::::::::::::::::::: //
                TProfile2D *chipEfficiencyMap_trackPos;
                gDirectory->GetObject("chipEfficiencyMap_trackPos", chipEfficiencyMap_trackPos);
                canvas = new TCanvas ("c1", "chipEfficiencyMap_trackPos", 200, 10, 750, 500);
                    canvas->SetRightMargin(0.09);
                    canvas->SetLeftMargin(0.15);
                    canvas->SetBottomMargin(0.15);
                
                    chipEfficiencyMap_trackPos->Draw("colz");            
                    canvas->Draw();
                    chipEfficiencyMap_trackPos->GetXaxis()->SetTitleSize(0.05);
                    chipEfficiencyMap_trackPos->GetYaxis()->SetTitleSize(0.05);
					canvas->Print("./run_checker/run"+buffer+"_chipEfficiencyMap_trackPos.png");
				}//block end */
								
					
			} //end internal if
		}//end while
	}//end external if
	cout << endl << "checked runs are: " << endl;
for(auto x:run_number) cout << x << endl;
} // end function
////////////////////   ANALYSIS-END  ///////////////////////////


