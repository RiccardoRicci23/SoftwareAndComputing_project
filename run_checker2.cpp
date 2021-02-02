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

#include "./run_checker/file_boat.cpp"

void run_checker(TString run_name){

open_prealignment(run_name);
// ora qui posso fare ogni genere di operazione perché il file ormai è aperto!

open_alignment(run_name);


}