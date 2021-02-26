/* Riccardo Ricci
 created in 2021, January 8th
 

 :::::::::::::::::::::::::::::::
 plotter_efficiencyVScluster.cpp
 :::::::::::::::::::::::::::::::
 the following macro builds a simple TGraphErrors by taking TotalEfficiencyVScluster.csv file, 
 which is the output of efficiencyVSrun.cpp


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 INSTRUCTIONS
 launch these macros from the main ./ folder. 

 1. Open ROOT on your terminal
 2. ".L ./efficiency/plotter_efficiencyVSrun.cpp" 
 3. execute the function by calling it: "plotter_efficiencyVScluster()"

 It is analogously possible to use a ROOT C++ notebook (SWAN, Jupyter) and run the same commands
 (use .L or the #include "./cluster/clusterVSrun.cpp" depending on your preferences)
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/



#include "../cluster/clusterVSrun.cpp"
#include "../efficiency/efficiencyVSrun.cpp"


void plotter_efficiencyVScluster(){// Tgraph setting
	//eventually:
    // TGraphAsymmErrors (const char *filename, const char *format="%lg %lg %lg %lg %lg %lg", Option_t *option="")
    // :::::::::::::::::::::::   GRAPH   :::::::::::::::::::::::::: //

	clusterVSrun();
	efficiencyVSrun();

	ofstream of("./efficiency/TotalEfficiencyVScluster.csv");
		int size_MPV = MPV.size();
		for(int i = 0; i < size_MPV; ++i)
			{of << MPV[i] << "," << efficiency_vector[i] << endl;}
	

	TGraph *g = new TGraph("./efficiency/TotalEfficiencyVScluster.csv", "%lg %lg", ","); //this format applies to .csv files. // %*lg formatting option tells to avoid that certain column.
	TCanvas *canvas = new TCanvas;
	g->SetTitle("TotalEfficiency VS ClusterSize");
	canvas->SetGrid();
	canvas->Draw();
	canvas->SetRightMargin(0.09);
    canvas->SetLeftMargin(0.25);
    canvas->SetBottomMargin(0.25);


    //markers
    g->SetMarkerStyle(21);
    g->SetMarkerColor(1);
    g->SetMarkerSize(1);
    //g.SetMarkerLineWidth(0);

    //X axis
	TAxis *X = g->GetXaxis();
		X->SetTitle("ClusterSize");
		X->SetTitleOffset(1.4);
		X->SetTitleSize(0.04);
		X->CenterTitle(); 
		X->SetNdivisions(size_MPV);
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
	
	//EVENTUALLY can be useful:
	// TAxis::ChangeLabel (Int_t labNum=0, Double_t labAngle=-1., Double_t labSize=-1., Int_t labAlign=-1, Int_t labColor=-1, Int_t labFont=-1, TString labText="")

	g->Draw("AP");
    
   
    
	// :::::::::::::::::::::::   LEGEND   :::::::::::::::::::::::::: //
	//canvas->BuildLegend();  //automatically build legend in some empty space
	TLegend *legend = new TLegend(0.48,0.4,0.8,0.48); // (x1,y1,x2,y2)
		legend->AddEntry(g);
		legend->Draw();

    
    // "and finally..."
canvas->Draw();
canvas->Print("./efficiency/efficiencyVScluster.png");
cout << endl << " .csv file has been found! Check the output in ./efficiency/ folder." << endl;
};




//////////////////////////////////////  
//////////////////////////////////////
//
//   OVERLOAD | WITH RUN NUMBER RANGE    
//
//////////////////////////////////////  
//////////////////////////////////////


void plotter_efficiencyVScluster(double clust1, double clust2){// Tgraph setting

    // TGraphAsymmErrors (const char *filename, const char *format="%lg %lg %lg %lg %lg %lg", Option_t *option="")
    // :::::::::::::::::::::::   GRAPH   :::::::::::::::::::::::::: //

	TGraph *g = new TGraph("./efficiency/efficiencyVScluster.csv", "%lg %lg", ","); //this format applies to .csv files. // %*lg formatting option tells to avoid that certain column.
	TCanvas *canvas = new TCanvas;
	g->SetTitle("TotalEfficiency VS ClusterSize");
	canvas->SetGrid();
	canvas->Draw();


    //markers
    g->SetMarkerStyle(21);
    g->SetMarkerColor(1);
    g->SetMarkerSize(1);
    //g.SetMarkerLineWidth(0);

    //X axis
	TAxis *X = g->GetXaxis();
		X->SetTitle("ClusterSize");
		X->SetTitleOffset(1.4);
		X->SetTitleSize(0.04);
		X->CenterTitle();
		//X->SetNdivisions(5);
		X->SetTitleOffset(1.3);
		X->SetLabelSize(0.03);
		X->SetRangeUser(clust1-0.5,clust2+0.5);


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
	TLegend *legend = new TLegend(0.48,0.4,0.8,0.48);
		legend->AddEntry(g);
		legend->Draw();

    
    // "and finally..."
canvas->Draw();
canvas->Print("./efficiency/efficiencyVScluster.png");
cout << endl << " .csv file has been found! Check the output in ./efficiency/ folder." << endl;
}