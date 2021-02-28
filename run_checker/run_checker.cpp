/* Riccardo Ricci
 created in February 2nd, 2021
 last update on February 20th, 2021


 :::::::::::::::
 run_checher.cpp
 :::::::::::::::
 Collection of 3 functions devoted to ROOT I/O tasks and open files/store array of files contained 
 in the selected folder.
GENERAL STRUCTURE: 
    1. "if" loop to scan inside the folder searching for .root files
        2. internal "while" cycle to loop over each .root file
            3. a) sub-internal "if" to select only certain files depending on their name.  
               b) data extraction and plotting


 


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 INSTRUCTIONS
 launch these macros from the main ./ folder. 


 1. Open ROOT on your terminal
 2. ".L ./run_checker/run_checker.cpp" 
 3. execute one of the three functions by calling them: "function()"

 It is analogously possible to use a ROOT C++ notebook (SWAN, Jupyter) and run the same commands
 (use .L or the #include "./run_checker/run_checker.cpp" depending on your preferences)
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/








/* //////////////////   PREALIGNMENT-START  ////////////////////////
 1) This function opens prealignment.root files from the targeted folder passed as argument. 
 2) It loops over all the prealignment.root output files from different runs. 
 3) For each run, it extracts correlations plots for X and Y coordinate 
    of the chip surface, and 2D correlation plots.*/

void open_prealignment(const char* dirname = "./_data_/August_BENT/not_checked/", const char *ext = ".root"){
        
		// this vector strings will contain the names of the .root file of interest
		// the use of vector string allows for further modifications in the future eventually
		vector <string> run_number; 
		TSystemDirectory dir(dirname, dirname); 
		TList *files = dir.GetListOfFiles();



/*:::::::::::::::::   if-while external block :::::::::::::::::::: //
inside this piece of code i will finaly make a list of .root files to open scanning the folder
*/
    if (files){
        TSystemFile *file;
        TString fname;
        TFile *file_to_open; 
        TIter next(files);   
        
		
		// this annidated while-loop selects the name of each file and initializes it. 
        while ((file = (TSystemFile *) next())){
            fname = file->GetName();
            cout << "Looking for .root files..." << endl;
				
            // this block selects only the "prealignment_run**.root" files
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
                
				
                // enter inside the file and extract then
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
                //correlationX->GetXaxis()->SetRangeUser(-9,-6); //uncomment and modify to use it eventually
                correlationX->GetXaxis()->SetLabelSize(0.05);
                correlationX->GetYaxis()->SetLabelSize(0.05);
                gStyle->SetOptFit(1011); // to see fit parameters on the legend
                correlationX->Draw();
                canvas->cd(1)->Draw();
                
                canvas->cd(2);
                gStyle->SetOptFit(1011); // to see fit parameters on the legend
                correlationY->GetXaxis()->SetLabelSize(0.05);
                correlationY->GetYaxis()->SetLabelSize(0.05);
                //correlationY->GetXaxis()->SetRangeUser(-4,2); //uncomment and modify to use it eventually
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
			

		}//end while
	}//end external if
			else { cout << "there are not prealignment.root files inside the targeted folder, please check. Quitting..." << endl;
                    return 0;}// end "external" else


cout << endl << "checked runs are: " << endl;
for(auto x:run_number) cout << x << endl;
cout << endl << "check the output in ./run_checker/ " << endl;
}
////////////////////   PREALIGNMENT-END  ///////////////////////////







/* //////////////////   ALIGNMENT-START  ////////////////////////
 1) This function opens alignment.root files from the targeted folder passed as argument. 
 2) It loops over all the alignment.root output files from different runs. 
 3) For each run, it extracts:
        a) # reconstructed straight tracks per 6 required passage points on each reference chip
            (namely ALPIDE_i, i = 1, ..., 6)
        b) measured track angle in X an Y direction. */

void open_alignment(const char* dirname = "./_data_/August_BENT/not_checked/", const char *ext = ".root"){
        
		// this vector strings will contain the names of the .root file of interest
		// the use of vector string allows for further modifications in the future evetually
		vector <string> run_number;
		
		TSystemDirectory dir(dirname, dirname); 
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
                
				
                // extraction
				{gFile->cd("TrackingSpatial");
				cout << "prealignment is OK" << endl;
                TCanvas *canvas = new TCanvas;

                // clustersPerTrack plot
                TH1F *clustersPerTrack = new TH1F;
                gDirectory->GetObject("clustersPerTrack", clustersPerTrack);
                clustersPerTrack -> Draw();
                canvas->Draw();
                canvas -> Print("./run_checker/run"+buffer+"_clusterPerTrack.png"); 

                TH1F *trackAngleX = new TH1F;
                gDirectory->GetObject("trackAngleX", trackAngleX);
                trackAngleX -> Draw();
                canvas->Draw();
                canvas -> Print("./run_checker/run"+buffer+"_trackAngleX.png");

                TH1F *trackAngleY = new TH1F;
                gDirectory->GetObject("trackAngleY", trackAngleY);
                trackAngleX -> Draw();
                canvas->Draw();
                canvas -> Print("./run_checker/run"+buffer+"_trackAngleY.png");

                } // extraction block - end     }
					
			} //end internal if

        
		}//end while
	}//end external if
        else { cout << "there are not alignment.root files inside the the targeted folder, please check. Quitting..." << endl;
                    return 0;}// end else



cout << endl << "checked runs are: " << endl;
for(auto x:run_number) cout << x << endl;
cout << endl << "check the output in ./run_checker/ " << endl;
} // end function
////////////////////   ALIGNMENT-END  ///////////////////////////







/* //////////////////   ANALYSIS-START  ////////////////////////
 1) This function opens analysis.root files from the targeted folder passed as argument. 
 2) It loops over all the alignment.root output files from different runs. 
 3) For each run, it extracts and plots only quantities related to the ALPIDE_BENT DUT (Detector Under Test):
        a) Value of the residuals wrt X and Y coordinate
        b) efficiency map wrt the DUT chip surface
        c) total efficiency of the DUT */

void open_analysis(const char* dirname = "./_data_/August_BENT/not_checked/", const char *ext = ".root"){
        
		// this vector strings will contain the names of the .root file of interest
		// the use of vector string allows for further modifications in the future evetually
		vector <string> run_number;
		TSystemDirectory dir(dirname, dirname); 
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
                

				// instructions block
                {gFile->cd("AnalysisDUT;1/ALPIDE_3;1");
                TH1F *residualsX;
                TH1F *residualsY;
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
                canvas = new TCanvas ("c1", "ALPIDE_3 chipEfficiency Map", 200, 10, 750, 500);
                    canvas->SetRightMargin(0.09);
                    canvas->SetLeftMargin(0.15);
                    canvas->SetBottomMargin(0.15);
                
                    chipEfficiencyMap_trackPos->Draw("colz");            
                    canvas->Draw();
                    chipEfficiencyMap_trackPos->GetXaxis()->SetTitleSize(0.05);
                    chipEfficiencyMap_trackPos->GetYaxis()->SetTitleSize(0.05);
					canvas->Print("./run_checker/run"+buffer+"_chipEfficiencyMap_trackPos.png");
				}//block end 
								
					
			    } //end internal if
		    
		}//end while
	}//end external if
        else { cout << "there are not analysis.root files inside the targeted folder, please check. Quitting..." << endl;
                    return 0;}// end else


cout << endl << "checked runs are: " << endl;
for(auto x:run_number) cout << x << endl;
cout << endl << "check the output in ./run_checker/ " << endl;
} // end function
////////////////////   ANALYSIS-END  ///////////////////////////


