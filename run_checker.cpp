// Riccardo Ricci
// run_checker

// 2021, January 15th
// updated JAnuary 25th


// the following macro exstracts the main parameters from the output of the Corryvreckan framework. 
 

///////////// INSTRUCTIONS ///////////////
//										//
//1. Load the macro: 					//
// 		".L run_checker" 				//	
//or using #include. 					//
//										//
//then execute:							//
//		"run_checker(run_number)"		//
//where run_number is the name of the considered run_number to be checked (same as its folder name: ./run_checker/run_number)
//										//
//Alternatively use the command: 		//
//		".x run_checker(run_number)"	//	
//////////////////////////////////////////




Alternatively use the command ".x run_checker"

//2. execute



// :::::::::::::  FIRST DEFINITIONSSSS :::::::::::::::::::::::: //
void run_checker(TString run_name){
        TString dirname = "./run_checker/" + run_name ;
        dirname += "/";
        const char *ext = ".root";
        TString run_number = run_name.Replace(0,3,"");
            run_number.Replace(9,16,"");
        
            cout << "run number is: " << run_number << endl; 
            cout << "Looking for .root files..." << endl;
    //store array of .root filenames
    vector <string> run_number_analysis, run_number_prealignment, run_number_alignment; //here i will save the names of my root file for many different uses
    TSystemDirectory dir(dirname, dirname); //directory, but in ROOT language
    TList *files = dir.GetListOfFiles();
    TCanvas *canvas;
       
			
			
	
    
        
        
//:::::::::::::::::   if-while external block :::::::::::::::::::: //
    if (files) {
        TSystemFile *file;
        TString fname;
        TFile *file_to_open; // pointer: initialized with a new file.root at each loop
        TIter next(files);   // iterator
        
        while ((file = (TSystemFile *) next())) {
            fname = file->GetName();
                //
                //
                //
                //
                //
                //
////////////////////   PREALIGNMENT-START  ///////////////////////////
            
            if (!file->IsDirectory() && fname.EndsWith(ext) && fname.BeginsWith("prealignment")){
				// extract only run number and ADD it to run_number vector
				string buffer_string = fname.Data();
				//buffer_string.replace(0,9,"");  //August Data have different namelenghts
				//buffer_string.replace(6,5,"");
                run_number_prealignment.push_back(buffer_string);
                
                 //OPEN .root file
                file_to_open = new TFile(dirname+fname);
                // file_to_open->ls(); // wanna see the folder content? uncomment this             
                cout << "prealignment is OK" << endl;
                
                //here i must implement correlationsX,Y and correlation2D
                //.....
                
                gFile->cd("Prealignment/ALPIDE_3");
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
                //      
////////////////////   ALIGNMENT-START  ///////////////////////////
            
            if (!file->IsDirectory() && fname.EndsWith(ext) && fname.BeginsWith("alignment") && fname.BeginsWith("pre")==false){
 
				
				// extract only run number and ADD it to run_number vector
				string buffer_string = fname.Data();
				//buffer_string.replace(0,9,"");  //August Data have different namelenghts
				//buffer_string.replace(6,5,"");
                run_number_alignment.push_back(buffer_string);

                
                
                //here i must implement reference planes Residuals eventually
                //.....
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
                
                
                
                //::::::::::: RESIDUALS EXTRACTION ::::::::::::::::::::::: //
                //define some pointers for the 2 histos                 
                gFile->cd("AnalysisDUT;1/ALPIDE_3;1");
                TH1F *residualsX;
                TH1F *residualsY;
                //assing residualsX,Y to the respective pointers
                    gDirectory->GetObject("residualsX", residualsX);
                    gDirectory->GetObject("residualsY", residualsY);

                //to fit, please uncomment
                    //residualsX->Fit("gaus");
                    //residualsX->GetFunction("gaus")->SetLineColor(2);
                    //residualsX->GetFunction("gaus")->SetLineStyle(2);
                    residualsX->GetXaxis()->SetTitleSize(0.05);
                    residualsX->GetYaxis()->SetTitleSize(0.05);
               
                    //residualsY->Fit("gaus");
                    //residualsY->GetFunction("gaus")->SetLineColor(2);
                    //residualsY->GetFunction("gaus")->SetLineStyle(2);
                    residualsY->GetXaxis()->SetTitleSize(0.05);
                    residualsY->GetYaxis()->SetTitleSize(0.05);
           
                canvas = new TCanvas ("c1", "Residuals X,Y", 200, 10, 1300, 500);
                canvas -> Divide (2, 1);
               
                canvas->cd(1)->SetRightMargin(0.09);
                canvas->cd(1)->SetLeftMargin(0.25);
                canvas->cd(1)->SetBottomMargin(0.25);
                
                canvas->cd(2)->SetRightMargin(0.09);
                canvas->cd(2)->SetLeftMargin(0.25);
                canvas->cd(2)->SetBottomMargin(0.25);
                // fit legend
                   //gStyle->SetOptFit(1011); // to see fit parameters on the legend

               
                //Finally plot please
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
                //::::::::::: TOTAL EFFICIENCY EXTRACTION ::::::::::::::::::::::: //
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
                    
                
                 //::::::::::: EFFICIENCY MAP EXTRACTION ::::::::::::::::::::::: //
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
					//canvas->BuildLegend(0.1, 0.8, 0.4, 0.88);
					canvas->Print("./run_checker/run"+run_number+"_chipEfficiencyMap_trackPos.png");
					
                 //::::::::::: EFFICIENCY EXTRACTION ::::  END  ::::::::::::::::::: //
}//end INTERNAL if  ////////////////////////  ANALYSIS-END  //////////////////

         
            
            
            
 
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
        }//end while
    }// end 1st if 
        else {
        cout << "No .root files found. Change the path in run_checker.cpp" << endl;
    }//end else
    
// ::: runs to be written in a .csv file, to be read by a TGraph ::: //

        
        
        
    //FOR NOW NO REASON TO PRINT
        ///////// print on .csv file		  
              int n = run_number_analysis.size();
              cout << "number of analysis.root files: "<< n << endl; 
              int m = run_number_prealignment.size();
              cout << "number of prealignment.root files: "<< m << endl;
              int s = run_number_alignment.size();
              cout << "number of alignment.root files: " <<  s << endl;
        //ofstream of("./run_checker/check.csv"); // output stream to new.csv file
       
       //  for (int i = 0; i < n; ++i)
         //            {of << run_number[i] << "," << endl;} 
   
 
    delete files;
  
    
    
}// END
