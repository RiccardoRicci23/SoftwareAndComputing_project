// Riccardo Ricci
// created in February 2nd, 2021

// TheFileBoat is a simple collection of similar macros devoted to some
// ROOT I/O tasks and open files/store array of files contained in the selected folder


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


////////////////////   PREALIGNMENT-START  ///////////////////////////
            if (!file->IsDirectory() && fname.EndsWith(ext) && fname.BeginsWith("prealignment")){
				// extract only run number and ADD it to run_number vector
				string buffer_string = fname.Data();
				buffer_string.replace(0,16,""); // PREALIGNMENT
				buffer_string.replace(9,22,""); // ALL
                run_number.push_back(buffer_string);


                //OPEN .root file then:
                file_to_open = new TFile(dirname+fname);
                // file_to_open->ls(); // wanna see the folder content? uncomment this line            
                cout << "prealignment is OK" << endl;


			//////////////
			//
			// 	TASKS
			//
			//////////////
	
			} //end internal if

			
			
		}//end while
		
		
	}//end external if


for(auto x:run_number) cout << x << endl;


}//end function
//
//
//
//
//