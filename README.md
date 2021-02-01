# SoftwareAndComputing_project

In this framework i'm showing part of my Master Thesis work. 
The core of this work is a little group of macros i wrote to perform the analysis of ALPIDE-bent chips, which are under study for the upgrade of the ALICE Inner Tracking System (ITS3), during CERN LHC Long Shutdown 3 (LS3). 

The aim is to analyse the output .root files coming from the Corryvreckan program - used to process/reinterpret raw data coming from the August testbeam at DESY (inserire qualcosa dalla TWIKI qui magari). 

# Short Setup description

The experimental setup is made of 3 ALPIDE flat chips + 1 ALPIDE BENT chip + 3 ALPIDE flat chips, where the central BENT chip in the middle is called Detector Under Test (DUT). 


////// IMAGE WITH THE SETUP & ALPIDE PHOTO/S


# The program
Large part of the macros originally comes from SWAN, where i have written them as a first step: so that also some notebooks are present in this work as example. 

The framework consists of 3 main structures/phases:

- run checking
- data extraction
- data analysis 


## 1. Run checking: magari dire come sono definite queste quantità...
Look at the IMAGE below: many tries have been made to match the geometry of the problem, since it was the first time with such configuration. 
The run_checker.cpp macro extracts 4 main quantities from 3 different .root files: prealignment.root, aligment.root and analysis.root, which correspond to respectively different outputs as they are computed by Corryvreckan from the .raw data file. 

These 4 quantities are: 
1. Cluster Size: number of hit pixels associated to every reconstructed track;
2. Residuals wrt to X and Y coordinates. Their value is stricly related to the spatial resolution of the detector (SAY HOW, PLEASE);
3. 2-D Efficiency Map of the ALPIDE chip as a function of (x,y) coordinates in terms of pixel row and column;
4. Total Efficiency of the chip.

It is possible to find further instructions opening run_checker.cpp file. in the main folder. A sample run (run....509) has already been analyzed. There is also the possibility to make the same plots using the other run_number as argument. 


## 2. Data extraction
## 3. Data analysis

