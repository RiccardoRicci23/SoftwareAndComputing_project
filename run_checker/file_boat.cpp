// Riccardo Ricci
// created in February 2nd, 2021

// TheFileBoat is a simple collection of similar macros devoted to some
// ROOT I/O tasks


void open_prealignment(TString run_name){
        TString dirname = "./run_checker/" + run_name ; 
        dirname += "/";
        const char *ext = ".root";
        TString run_number = run_name.Replace(0,3,"");
            cout << "run number is: " << run_number << endl; 
            cout << "Looking for .root files..." << endl;

    // this vector strings will contain the names of the .root file of interest
	// the use of vector stringa allows for further modifications in the future evetually
    vector <string> run_number_analysis, run_number_prealignment, run_number_alignment; 
    TSystemDirectory dir(dirname, dirname); //directory, but in ROOT language
    TList *files = dir.GetListOfFiles();
    TCanvas *canvas;

//:::::::::::::::::   if-while external block :::::::::::::::::::: //
// inside this piece of code i will finaly make a list of .root files to open.
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
			} //end internal if
			
		}//end while
		
	}//end external if


}


//////////////////// ALIGNMENT ///////////
void open_alignment(TString run_name){
        TString dirname = "./run_checker/" + run_name ; 
        dirname += "/";
        const char *ext = ".root";
        TString run_number = run_name.Replace(0,3,"");
            cout << "run number is: " << run_number << endl; 
            cout << "Looking for .root files..." << endl;

    // this vector strings will contain the names of the .root file of interest
	// the use of vector stringa allows for further modifications in the future evetually
    vector <string> run_number_analysis, run_number_prealignment, run_number_alignment; 
    TSystemDirectory dir(dirname, dirname); //directory, but in ROOT language
    TList *files = dir.GetListOfFiles();
    TCanvas *canvas;

//:::::::::::::::::   if-while external block :::::::::::::::::::: //
// inside this piece of code i will finaly make a list of .root files to open.
    if (files) {
        TSystemFile *file;
        TString fname;
        TFile *file_to_open; 
        TIter next(files);   
        
		// this annidated while-loop selects the name of each file and initializes it. 
        while ((file = (TSystemFile *) next())) {
            fname = file->GetName();

				
// from now on, there are 3 different blocks per each filename & filetype to be open/analyzed	

////////////////////   ALIGNMENT-START ///////////////////////////           
            if (!file->IsDirectory() && fname.EndsWith(ext) && fname.BeginsWith("alignment") && fname.BeginsWith("pre")==false){
				// extract only run number and ADD it to run_number vector
				string buffer_string = fname.Data();
                run_number_alignment.push_back(buffer_string);
				
				//OPEN .root file then:
                file_to_open = new TFile(dirname+fname);
                // file_to_open->ls(); // wanna see the folder content? uncomment this line            
                cout << "alignment is OK" << endl;
			}//end INTERNAL if  ////////////////////////  ALIGNMENT-END  //////////////////   
			
		}//end while
		
	}//end external if

}// end open_alignment





