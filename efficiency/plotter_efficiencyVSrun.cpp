/* Riccardo Ricci
 created in 2021, January 8th
 

 ::::::::::::::::
 plotter_efficiencyVSrun.cpp
 ::::::::::::::::
 the following macro builds a simple TGraphErrors by taking TotalEfficiencyVSrun.csv file, 
 which is the output of efficiencyVSrun.cpp


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 INSTRUCTIONS
 launch these macros from the main ./ folder. 

 1. Open ROOT on your terminal
 2. ".L ./efficiency/plotter_efficiencyVSrun.cpp" 
 3. execute the function by calling it: "plotter_efficiencyVSrun()"

 It is analogously possible to use a ROOT C++ notebook (SWAN, Jupyter) and run the same commands
 (use .L or the #include "./cluster/clusterVSrun.cpp" depending on your preferences)
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/







// ::::::::::::::::::::::::::::: TOTAL EFFICIENCY VS RUN PLOTTER ::::::::::::::::::::::::::::::::::://
void plotter_efficiencyVSrun(){
    // TGraphAsymmErrors (const char *filename, const char *format="%lg %lg %lg %lg %lg %lg", Option_t *option="")
    // :::::::::::::::::::::::   GRAPH   :::::::::::::::::::::::::: //

	TGraphErrors *g = new TGraphErrors("./efficiency/TotalEfficiencyVSrun.csv", "%lg %lg %lg %lg", ","); //this format applies to .csv files. // %*lg formatting option tells to avoid that certain column.
	TCanvas *canvas = new TCanvas;
	g->SetTitle("TotalEfficiency VS RunNumber");
	canvas->SetGrid();
	canvas->Draw();
	canvas->SetRightMargin(0.09);
    canvas->SetLeftMargin(0.25);
    canvas->SetBottomMargin(0.25);


    //markers
    g->SetMarkerStyle(21);
    g->SetMarkerColor(1);
    g->SetMarkerSize(1);

    //X axis
	TAxis *X = g->GetXaxis();
		X->SetTitle("RunNumber");
		X->SetTitleOffset(1.4);
		X->SetTitleSize(0.04);
		X->CenterTitle(); 
		X->SetNdivisions(5);
		X->SetTitleOffset(1.3);
		X->SetLabelSize(0.03);


    //Y axis
	TAxis *Y = g->GetYaxis();
		Y->SetTitle("TotalEfficiency");
		Y->SetTitleOffset(1.4);
		//Y->SetRangeUser(0.9999,1.);
		Y->SetTitleSize(0.04);
		//g.GetYaxis()->CenterTitle();
		Y->SetNdivisions(10);
		Y->SetTitleOffset(1.3);
		Y->SetLabelSize(0.03);
		Y->SetNoExponent(kTRUE);
	
	//EVENTUALLY: remember this.
	// TAxis::ChangeLabel (Int_t labNum=0, Double_t labAngle=-1., Double_t labSize=-1., Int_t labAlign=-1, Int_t labColor=-1, Int_t labFont=-1, TString labText="");   
	g->Draw("AP");
    
   
    
// :::::::::::::::::::::::   LEGEND   :::::::::::::::::::::::::: //
//canvas->BuildLegend();  //automatically build legend in some empty space
	TLegend *legend = new TLegend(0.48,0.4,0.8,0.48);
		//legend->SetHeader("The Legend Title","C"); // option "C" allows to center the header
		legend->AddEntry(g);
		//legend->AddEntry("f1","Function abs(#frac{sin(x)}{x})","l");
		//legend->AddEntry("gr","Graph with error bars","lep");
		legend->Draw();

    // "and finally..."
canvas->Draw();
canvas->Print("./efficiency/TotalEfficiencyVSrun.png");

cout << endl << " .csv file has been found! Check the output in ./efficiency/ folder." << endl;

};






//////////////////////////////////////  
//////////////////////////////////////
//									
//   OVERLOAD including RUN NUMBER RANGE    
//
//////////////////////////////////////  
//////////////////////////////////////


void plotter_TotalEfficiencyVSrun(int run1, int run2){// Tgraph setting

    // TGraphAsymmErrors (const char *filename, const char *format="%lg %lg %lg %lg %lg %lg", Option_t *option="")
    // :::::::::::::::::::::::   GRAPH   :::::::::::::::::::::::::: //

	TGraphErrors *g = new TGraphErrors("./efficiency/TotalEfficiencyVSrun.csv", "%lg %lg %lg %lg", ","); //this format applies to .csv files. // %*lg formatting option tells to avoid that certain column.
	TCanvas *canvas = new TCanvas;
	g->SetTitle("TotalEfficiency VS RunNumber");
	canvas->SetGrid();
	canvas->Draw();



    //markers
    g->SetMarkerStyle(21);
    g->SetMarkerColor(1);
    g->SetMarkerSize(1);
    //g.SetMarkerLineWidth(0);

    //X axis
	TAxis *X = g->GetXaxis();
		X->SetTitle("RunNumber");
		X->SetTitleOffset(1.4);
		X->SetTitleSize(0.04);
		X->CenterTitle();
		//X->SetNdivisions(5);
		X->SetTitleOffset(1.3);
		X->SetLabelSize(0.03);
		X->SetRangeUser(run1-0.5,run2+0.5);

    


    //Y axis
	TAxis *Y = g->GetYaxis();
		Y->SetTitle("TotalEfficiency");
		Y->SetTitleOffset(1.4);
		Y->SetRangeUser(0.9999,1.);
		Y->SetTitleSize(0.04);
		//g.GetYaxis()->CenterTitle();
		Y->SetNdivisions(10);
		Y->SetTitleOffset(1.3);
		Y->SetLabelSize(0.03);
		Y->SetNoExponent(kTRUE);

	g->Draw("AP");
    
   
    
	// :::::::::::::::::::::::   LEGEND   :::::::::::::::::::::::::: //
	//canvas->BuildLegend();  //automatically build legend in some empty space
	TLegend *legend = new TLegend(0.48,0.4,0.88,0.48);
		//legend->SetHeader("The Legend Title","C"); // option "C" allows to center the header
		legend->AddEntry(g);
		legend->Draw();

    
    // "and finally..."
canvas->Draw();
canvas->Print("./efficiency/TotalEfficiencyVSrun.png");

cout << endl << " .csv file has been found! Check the output in ./efficiency/ folder." << endl;

}// end of the overload