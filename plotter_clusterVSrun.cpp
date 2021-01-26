// Riccardo Ricci
// January 8th, 2021
//Updated January 14th, 2021



// ::::::::::::::::::::::::::::: CLUSTERSIZE VS RUN PLOTTER ::::::::::::::::::::::::::::::::::://
// the following macro builds a simple TGraph by taking clusterVSrun.csv file, which is the output of clusterVSrun.cpp
// to execute the macro, type:
            //  .x macro_name.cpp   //

// there are some problems when declaring it as a function that i haven't overcome yet...
// that's a problem to solve because it implies a redefinition of variables (so an error) and i must restart root each time i use it...





void plotter_clusterVSrun(){// Tgraph setting

    
    // :::::::::::::::::::::::   GRAPH   :::::::::::::::::::::::::: //
    TGraph *g = new TGraph("./cluster/ClusterSizeAssociatedVSrun.csv", "%lg %lg", ","); //this format applies to .csv files. // %*lg formatting option tells to avoid that certain column.
TCanvas *canvas = new TCanvas;
g->SetTitle("ClusterSize VS RunNumber");
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
    X->SetTitle("RunNumber");
    X->SetTitleOffset(1.4);
    X->SetTitleSize(0.05);
    X->CenterTitle();
    X->SetNdivisions(5);
    X->SetLabelSize(0.03);
    X->SetNoExponent(kTRUE);

    //Y axis
TAxis *Y = g->GetYaxis();
    Y->SetTitle("ClusterSizeAssociated");
    Y->SetTitleOffset(1.4);
    Y->SetRangeUser(0,4);
    Y->SetTitleSize(0.05);
    //g.GetYaxis()->CenterTitle();
    Y->SetNdivisions(20);
    Y->SetTitleOffset(1.3);
    Y->SetLabelSize(0.03);

    //change X labels ?
    ////.....
   
g->Draw("AP");
    
   
    
// :::::::::::::::::::::::   LEGEND   :::::::::::::::::::::::::: //
//canvas->BuildLegend();  //automatically build legend in some empty space
TLegend *legend = new TLegend(0.48,0.8,0.88,0.88);
   //legend->SetHeader("The Legend Title","C"); // option "C" allows to center the header
    legend->AddEntry(g);
   //legend->AddEntry("f1","Function abs(#frac{sin(x)}{x})","l");
   //legend->AddEntry("gr","Graph with error bars","lep");
    legend->Draw();

    
    // and finally...
canvas->Draw();
    canvas->Print("./cluster/ClusterVSrun.png");

// e niente, qua si tratta di proseguire
// ora sarebbe interessante trovare i run di giugno
};




///overload



void plotter_clusterVSrun(int run1, int run2){// Tgraph setting

    
    // :::::::::::::::::::::::   GRAPH   :::::::::::::::::::::::::: //
TGraph *g = new TGraph("./cluster/ClusterSizeAssociatedVSrun.csv", "%lg %lg %*lg", ","); //this format applies to .csv files. // %*lg formatting option tells to avoid that certain column. TCanvas *canvas = new TCanvas;
g->SetTitle("ClusterSize VS RunNumber");
TCanvas *canvas = new TCanvas;
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
    //X->SetNdivisions();
    X->SetTitleOffset(1.3);
    X->SetLabelSize(0.03);
	X->SetRangeUser(run1-0.5,run2+0.5);

    //Y axis
TAxis *Y = g->GetYaxis();
    Y->SetTitle("ClusterSizeAssociated");
    Y->SetTitleOffset(1.4);
    Y->SetRangeUser(1,2);
    Y->SetTitleSize(0.04);
    //g.GetYaxis()->CenterTitle();
    Y->SetNdivisions(20);
    Y->SetTitleOffset(1.3);
    Y->SetLabelSize(0.03);

    //change X labels ?
    ////.....
   
g->Draw("AP");
    
   
    
// :::::::::::::::::::::::   LEGEND   :::::::::::::::::::::::::: //
//canvas->BuildLegend();  //automatically build legend in some empty space
TLegend *legend = new TLegend(0.48,0.8,0.88,0.88);
   //legend->SetHeader("The Legend Title","C"); // option "C" allows to center the header
    legend->AddEntry(g);
   //legend->AddEntry("f1","Function abs(#frac{sin(x)}{x})","l");
   //legend->AddEntry("gr","Graph with error bars","lep");
    legend->Draw();

    
    // and finally...
canvas->Draw();
    canvas->Print("./cluster/ClusterVSrun.png");

// e niente, qua si tratta di proseguire
// ora sarebbe interessante trovare i run di giugno
}