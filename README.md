# SoftwareAndComputing_project

In this framework i'm showing part of my Master Thesis work. 
The core of this work is a group of macros i have written to perform the analysis of MAPS (Monolythic Active Pixel Sensors) ALPIDE-bent chips, which are under study for the upgrade of the ALICE Inner Tracking System (ITS3), during CERN LHC Long Shutdown 3 (LS3). 

`git clone https://github.com/RiccardoRicci23/SoftwareAndComputing_project`
`dd`




# Short Setup description
![Screenshot (83)](https://user-images.githubusercontent.com/61977057/109390754-b43a6f00-7913-11eb-977b-4896d965c661.png)


The testbeam was carried out at DESY and to perform the chip charachterization a 5.4 GeV electron beam has been chosen.
The experimental setup is made of 3 ALPIDE flat chips + 1 ALPIDE BENT chip + 3 ALPIDE flat chips, where the central BENT chip in the middle is called Detector Under Test (DUT) and the others have been considered as reference planes.  
The adjustable position of the cylindrical structure the chip was attached to allowed to center the beam direction on different regions of the chip. 


Each run gives a .raw data file as output. 
A first analysis of each single .raw file has been performed using a specific software, Corryvreckan (https://gitlab.cern.ch/alice-its3-wp3/its-corryvreckan-tools). 



# The program
The final aim is to analyse the output .root files coming from the Corryvreckan to study the ALPIDE_BENT performance in the August testbeam. 
Each .root file contains some crucial quantities (like the chip total efficiency): since the runs number is high, is not convenient to extract data one-by-one by terminal or by using ROOT TBrowser. 
In particular, some macros to extract/analyse with the capability to extract and compare automatically their value among different runs or given a certain run/time range were needed. 

To accomplish that, i wrote first a simple macro-block in ROOT C++. 
This is the "core" of all the others, because it allows to open N .root files inside the folder/path of interest and loop every type of operation over the file set. 
All the macros i have written start from this block and then complete their specific task.

Since large part of the code originally comes from SWAN - where i have written it as a first step before switching to Git - also some Jupyter notebooks are present in this work, as an example. 

Given a single run as example, the typical workflow consists of 3 main steps:

- run checking
- data extraction
- data analysis 


## 1. Run checking: 
Look at the IMAGE below: many tries have been made to match the geometry of the problem, since it was the first time with such configuration. 
The run_checker.cpp macro extracts 4 main quantities from 3 different .root files: prealignment.root, aligment.root and analysis.root, which correspond to respectively different outputs as they are computed by Corryvreckan from the .raw data file. 

The 4 extracted quantities are: 
1. Cluster Size: number of hit pixels associated to every reconstructed track (more than 1 fired px can result from single track). A center-of-gravity technique is then used to estimate the hit position; 
2. Residuals wrt to X and Y coordinates. They are estimated as the row and column distance between the as99 sociated clusters and the track intercept and their value is stricly related to the spatial resolution of the detector;
3. 2-D Efficiency Map of the ALPIDE chip as a function of (x,y) coordinates in terms of pixel row and column;
4. Total Efficiency of the chip. 

It is possible to find further instructions opening run_checker.cpp file. in the main folder. A sample run (run....509) has already been analyzed. There is also the possibility to make the same plots using the other run_number as argument. 


## 2. Data extraction
![chipEfficiencyMap_trackPos](https://user-images.githubusercontent.com/61977057/109392205-25c9eb80-791b-11eb-99e3-6185fe02e250.png)

Here the same plot is shown (after some corrections in the geometry description):

![run355234407_chipEfficiencyMap_trackPos](https://user-images.githubusercontent.com/61977057/109392247-688bc380-791b-11eb-94e7-559f620a9219.png)



## 3. Data analysis (show plotters)
This part is simple indeed. Once the .csv output files are created, ...
