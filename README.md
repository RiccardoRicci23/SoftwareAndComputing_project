# SoftwareAndComputing_project

In this framework i'm showing part of my Master Thesis work. 
The core of this work is a group of macros i have written to perform the analysis of MAPS (Monolythic Active Pixel Sensors) ALPIDE-bent chips, which are under study for the upgrade of the ALICE Inner Tracking System (ITS3), during CERN LHC Long Shutdown 3 (LS3). 


## Requirements
To clone the repository type on your terminal: 

`git clone https://github.com/RiccardoRicci23/SoftwareAndComputing_project`

Software requirements: ROOT (https://root.cern/), git (https://git-scm.com/). 
It is also possible to use SWAN (https://swan.web.cern.ch/swan/). In this case, all the .ipynb notebooks become usable since SWAN has complete compatibility with ROOT C++ Jupyter notebooks. 


# Short Setup description
![Screenshot (83)](https://user-images.githubusercontent.com/61977057/109390754-b43a6f00-7913-11eb-977b-4896d965c661.png)


The testbeam was carried out at DESY and to perform the chip charachterization a 5.4 GeV electron beam has been chosen.
The experimental setup is made of 3 ALPIDE flat chips + 1 ALPIDE BENT chip + 3 ALPIDE flat chips, where the central BENT chip in the middle is called Detector Under Test (DUT) and the others have been considered as reference planes. 


Each run gives a .raw data file as output. 
A first analysis of each single .raw file has been performed using a specific software, Corryvreckan (https://gitlab.cern.ch/alice-its3-wp3/its-corryvreckan-tools). 



# The program
The final aim is to analyse the output .root files coming from the Corryvreckan to study the ALPIDE_BENT performance in the August testbeam. 
Each .root file contains some crucial quantities (like the chip total efficiency): since the runs number is high, is not convenient to extract data one-by-one by terminal or by using ROOT TBrowser. 
In particular, some macros to extract and compare automatically the value and variation of some crucial features/quantities among different runs or given a certain run/time range were needed. 

To accomplish that, i wrote first a simple macro-block in ROOT C++. 
This is the "core" of all the others, because it allows to open N .root files inside the folder/path of interest and loop every type of operation over the file set. 
All the macros i have written start from this block and then complete their specific task.

Since large part of the code originally comes from SWAN - where i have written it as a first step before switching to Git - also some Jupyter notebooks are present in this work, as an example. 

Given a single run as example, the typical workflow consists of 3 main steps:

- run checking
- data extraction
- data analysis 


## 1. Run checking: run_checker.cpp 
The images below show the efficiency map of the same chip wrt the same runs. 
The different efficiency map shapes and total efficiency level (about 40% and 99.2% in the first and second case, respectively) comes from mismatching between the real geometry setup and its code description in the Corryvreckan software. 
Many tries have been made to match the geometry of the problem and obtain the current efficiency values shown in the second picture. 


<img align="left" width="475" height="285" src="https://user-images.githubusercontent.com/61977057/109416289-8dd10e00-79bd-11eb-848e-145eb0703baf.png">


<img align="left" width="475" height="285" src="https://user-images.githubusercontent.com/61977057/109475553-275bf680-7a76-11eb-93a2-fc45736650e9.png">




In order to perform a fast check of quantities like these, the run_checker.cpp macro extracts data from 3 different .root files: prealignment.root, aligment.root and analysis.root, which correspond to respectively different outputs as they are computed by Corryvreckan from the .raw data file. Its output gives a "global" check of the quality of the Corryvreckan geometry description.

  Most important are: 
  1. Cluster Size: number of hit pixels associated to every reconstructed track (more than 1 fired px can result from single track). A center-of-gravity technique is then used     to estimate the hit position; 
  2. Residuals wrt to X and Y coordinates. They are estimated as the row and column distance between the as99 sociated clusters and the track intercept and their value is         stricly related to the spatial resolution of the detector;
  3. 2-D Efficiency Map of the ALPIDE chip as a function of (x,y) coordinates in terms of pixel row and column;
  4. Total Efficiency of the chip. 

It is possible to find further instructions opening run_checker.cpp file in `./run_checker/` folder. A sample run (run355234407_200828235509) has already been analyzed, but it is possible to check N runs at once pasting the relative .root files inside `./_data_/August_BENT/not_checked/`.


Usage: open ROOT on your terminal in the main folder `./` and type: 

`.L ./run_checker/run_checker.cpp` 

`run_checker()`

You can check the macro and relative plots inside `./run_checker/`.



## 2. Data extraction: clusterVSrun.cpp and efficiency macros
The following macros extract some fundamental quantities related to the DUT performance. 

### clusterVSrun.cpp

This macro extract the MPV of the ClusterSize over the DUT surface per each associated track. For now, we decided to keep using landau fit over the distribution, but we would like to focus better on it and write an appropriate parametrization for the fit.
It also prints a .csv file with the run as first column and the cluster size MPV as second one.

![355234407](https://user-images.githubusercontent.com/61977057/109395535-2e2b2200-792d-11eb-924d-c1d839872f1f.png)

Usage: open ROOT on your terminal in the main folder `./` and type: 

`.L ./cluster/clusterVSrun.cpp` 

`clusterVSrun()`

You can check the macro and relative plots inside `./cluster/`.


### efficiencyVSrun.cpp & efficiencyVScluster.cpp

These two macros extracts the total efficiency (%) of the chip and the efficiency 2D plot over the whole chip surface (as for the run_checker.cpp case). They also print 2 .csv file, respectively, with the efficiency value as first column and the run or cluster as second one.

Usage: open ROOT on your terminal in the main folder `./` and type: 

`.L ./efficiency/efficiencyVSrun.cpp`

`efficiencyVSrun()` 

or 

`.L ./efficiency/efficiencyVScluster.cpp`

`efficiencyVScluster()`

You can check the macros and relative plots inside `./efficiency/`.



## 3. Other plots
This part is simple indeed. Once the .csv output files are created, there is the possibility to plot some quantities VS the run or the cluster size by using a simple ROOT TGraph and giving the .csv file as input argument. 


Usage: open ROOT on your terminal in the main folder `./` and type: 

`.L ./cluster/plotter_clusterVSrun.cpp`

then `plotter_clusterVSrun()`.

It is possible also to use an overload and insert an interval of run numbers:

`plotter_clusterVSrun()`. 

This is going to be useful in the future when performing the final analysis over all the dataset, in order to select a certain run period. Also efficiency can be plotted VS run number or cluster MPV with analogous macros.
You can check the macros and relative plots inside `./cluster/` and `./efficiency/`.



### The output branch
It is also possible to check/compare the outputs switching to the `output_checking` branch, from the project main page on Github. In this one, large parte of the plots is already there.



## Conclusion
This framework is continously evolving and being updated (since this is an exam-devoted project, a CERN-GitLab version will be available soon for this purpose), since we are updating the way to describe the bent geometry of the DUT ALPIDE chip: so also the macros devoted to the analysis will hopefully grow better.
Surely this work has been useful when comparing the big changes in the first geometry configurations (when trying to match the geometry of the problem with the Corryvreckan code description), switching from 0% to 40% efficiency levels, and then about 99% in the end.
We hopefully aim to be able to completely analyse the full August dataset before the end of March, 2021. 
This will be a great test also for the next tesbeam datasets (DESY, December 2020 and March, 2021). 
