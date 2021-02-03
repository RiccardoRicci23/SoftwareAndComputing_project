// Riccardo Ricci
// run_checker

// 2021, January 15th
// updated JAnuary 25th


// the following macro exstracts the main parameters from the output of the Corryvreckan framework. 
 

///////////// INSTRUCTIONS ///////////////
//					//
// 0. Open ROOT				//
//     "root -l"			//
//					//
// 1. Load the macro: 			//
// 		".L run_checker.cpp" 	//	
// or using #include "run_checker.cpp" 	//
//					//
// 2. then execute:			//
//	"run_checker(run_number)"	//
//					//
// where run_number is the name of the  //
// considered run_number to be checked  //
// (same as its folder name: 		//
// ./run_checker/run_number)		//
// and should be encloed by ""		//
//					//
// Alternatively use the command: 	//
//	".x run_checker(run_number)"	//
//					//
//////////////////////////////////////////



void run_checker(TString run_name){
        TString dirname = "./run_checker/" + run_name ; 
        dirname += "/";
        const char *ext = ".root";
        TString run_number = run_name.Replace(0,3,"");
            run_number.Replace(9,16,"");
        
            cout << "run number is: " << run_number << endl; 
            cout << "Looking for .root files..." << endl;
			
			
			
    // this vector strings will contain the names of the .root file of interest
	// the use of vector stringa allows for further modifications in the future evetually
    vector <string> run_number_analysis, run_number_prealignment, run_number_alignment; 
    TSystemDirectory dir(dirname, dirname); //directory, but in ROOT language
    TList *files = dir.GetListOfFiles();
    TCanvas *canvas;
       
			
			
	
    
        
        
//:::::::::::::::::   if-while external block :::::::::::::::::::: //
// inside this piece of 	code i will finaly make a list of .root files to open.
    if (files) {
        TSystemFile *file;
        TString fname;
        TFile *file_to_open; 
        TIter next(files);   
        
		// this annidated while-loop selects the name of each file and initializes it. 
        while ((file = (TSystemFile *) next())) {
            fname = file->GetName();
                
				
				
				
				
// from now on, there are 3 different blocks per each filename & filetype to be open/analyzed	

////////////////////   PREALIGNMENT-START  ///////////////////////////
            if (!file->IsDirectory() && fname.EndsWith(ext) && fname.BeginsWith("prealignment")){
				// extract only run number and ADD it to run_number vector
				string buffer_string = fname.Data();
				run_number_prealignment.push_back(buffer_string);
                
                //OPEN .root file then:
                file_to_open = new TFile(dirname+fname);
                // file_to_open->ls(); // wanna see the folder content? uncomment this line            
                cout << "prealignment is OK" << endl;
                gFile->cd("Prealignment/ALPIDE_3");
                
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
                canvas = new TCanvas ("c1", "prealignment - run" + run_number, 200, 10, 2400, 1400);
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
                canvas->Print("./run_checker/run"+run_number+"_prealignment_DUTcorrelations.png");               
}//end INTERNAL if  ////////////////////////  PREALIGNMENT-STOP  //////////////////        
                //
                //
                //
                //
                //
                //
                //
                //
                //
                //
                //
                //      //alignment not implemented yet, it does not contain useful quantities for now
////////////////////   ALIGNMENT-START ///////////////////////////           
            if (!file->IsDirectory() && fname.EndsWith(ext) && fname.BeginsWith("alignment") && fname.BeginsWith("pre")==false){
				// extract only run number and ADD it to run_number vector
				string buffer_string = fname.Data();
                run_number_alignment.push_back(buffer_string);
}//end INTERNAL if  ////////////////////////  ALIGNMENT-END  //////////////////
                //
                //
                //
                //
                //
                //
                //
                //
                //
                //
                //
                //
////////////////////   ANALYSIS-START  ///////////////////////////
            if (!file->IsDirectory() && fname.EndsWith(ext) && fname.BeginsWith("analysis")){
 				// extract only run number and ADD it to run_number vector
				string buffer_string = fname.Data();
                run_number_analysis.push_back(buffer_string);
                                          
               
                //OPEN .root file
                file_to_open = new TFile(dirname+fname);
                // file_to_open->ls(); // wanna see the folder content? uncomment this
                cout << "analysis is OK" << endl;
                
                
                
                //::::::::::: RESIDUALS X,Y EXTRACTION ::::::::::::::::::::::: //
                //define some pointers for the 2 histos                 
                gFile->cd("AnalysisDUT;1/ALPIDE_3;1");
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
                    canvas->Print("./run_checker/run"+run_number+"_residualsXY.png");
				//::::::::::: RESIDUALS EXTRACTION ::::  END  ::::::::::::::::::: //
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
                    canvas->Print("./run_checker/run"+run_number+"_totalEfficiency.png");
                    
                
				
				
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
					canvas->Print("./run_checker/run"+run_number+"_chipEfficiencyMap_trackPos.png");
					
                //::::::::::: EFFICIENCY EXTRACTION ::::  END  ::::::::::::::::::: //
}//end INTERNAL if  ////////////////////////  ANALYSIS-END  //////////////////



			//////////////////
			//		//	
			// END of all	//	
			// the		//	
			// extractions	//	
			//		//	
			//////////////////
            
			
        }//end external while
    }// end external if 
        else {
        cout << "No .root files found. Change the path in run_checker.cpp" << endl;
    }//end else
    
// ::: runs to be written in a .csv file, to be read by a TGraph ::: //

        
// check from this output if the file openings has gone OK
              int n = run_number_analysis.size();
              cout << "number of analysis.root files: "<< n << endl; 
              int m = run_number_prealignment.size();
              cout << "number of prealignment.root files: "<< m << endl;
              int s = run_number_alignment.size();
              cout << "number of alignment.root files: " <<  s << endl;
    delete files;
  
    
    
}// END
