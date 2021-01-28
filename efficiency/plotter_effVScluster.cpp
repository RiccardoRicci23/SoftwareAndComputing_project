// Riccardo Ricci
// January 8th, 2021
//Updated January 14th, 2021


// ::::::::::::::::::::::::::::: TOTAL EFFICIENCY VS RUN PLOTTER ::::::::::::::::::::::::::::::::::://
// the following macro builds a simple TGraph by taking clusterVSrun.csv file, which is the output of clusterVSrun.cpp
// to execute the macro, type:
            //  .x macro_name.cpp   //


void plotter_TotalEfficiencyVSClusterSize(){// Tgraph setting

    // TGraphAsymmErrors (const char *filename, const char *format="%lg %lg %lg %lg %lg %lg", Option_t *option="")
    // :::::::::::::::::::::::   GRAPH   :::::::::::::::::::::::::: //

	TGraphErrors *g = new TGraphErrors("../eff_vs_cluster/eff_vs_cluster.csv", "%lg %lg %lg %lg", ","); //this format applies to .csv files. // %*lg formatting option tells to avoid that certain column.
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
	
	//EVENTUALLY can be useful:
	// TAxis::ChangeLabel (Int_t labNum=0, Double_t labAngle=-1., Double_t labSize=-1., Int_t labAlign=-1, Int_t labColor=-1, Int_t labFont=-1, TString labText="")

	g->Draw("AP");
    
   
    
	// :::::::::::::::::::::::   LEGEND   :::::::::::::::::::::::::: //
	//canvas->BuildLegend();  //automatically build legend in some empty space
	TLegend *legend = new TLegend(0.48,0.8,0.88,0.88);
		legend->AddEntry(g);
		legend->Draw();

    
    // "and finally..."
canvas->Draw();
canvas->Print("../eff_vs_cluster/TotalEfficiencyVSClusterSize.png");
};


//////////////////////////////////////  
//////////////////////////////////////
//
//   OVERLOAD | RUN NUMBER RANGE    //
//
//////////////////////////////////////  
//////////////////////////////////////


void plotter_TotalEfficiencyVSClusterSize(double clust1, double clust2){// Tgraph setting

    // TGraphAsymmErrors (const char *filename, const char *format="%lg %lg %lg %lg %lg %lg", Option_t *option="")
    // :::::::::::::::::::::::   GRAPH   :::::::::::::::::::::::::: //

	TGraphErrors *g = new TGraphErrors("../eff_vs_cluster/eff_vs_cluster.csv", "%lg %lg %lg %lg", ","); //this format applies to .csv files. // %*lg formatting option tells to avoid that certain column.
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
	TLegend *legend = new TLegend(0.48,0.8,0.88,0.88);
		legend->AddEntry(g);
		legend->Draw();

    
    // "and finally..."
canvas->Draw();
canvas->Print("../eff_vs_cluster/TotalEfficiencyVSClusterSize.png");
}