# SoftwareAndComputing_project

This framework starts from a little group of macros i wrote to perform the analysis of ALPIDE-bent chips under study upgrade of the ALICE Inner Tracking System (ITS3) during CERN LHC Long Shutdown 3 (LS3). 

The aim is to analyse the output .root files coming from the Corryvreckan program - used to process/reinterpret raw data coming from the August testbeam at DESY (inserire qualcosa dalla TWIKI qui magari). 

# The Setup

The experimental setup is made of 3 ALPIDE flat chips + 1 ALPIDE BENT chip + 3 ALPIDE flat chips, where the central BENT chip in the middle is called Detector Under Test (DUT). 

 







Large part of the macros originally comes from SWAN, where i have written them as a first step: so that also some notebooks are present in this work. 

The framework consists of 3 main structures/phases:

- run checking
- data extraction
- data analysis 


## 1. Run checking: magari dire come sono definite queste quantità...
Look at the IMAGE below: many tries have been made to match the geometry of the problem, since it was the first time with such configuration. 
The run checker extracts 4 main quantities from 3 different .root files: prealignment.root, aligment.root and analysis.root, which correspond to respectively different outputs by Corryvreckan.

These 4 quantities are: 

1. Cluster Size: number of hit pixels associated to every reconstructed track;
2. Residuals
3. 2-D efficiency map of the ALPIDE chip as a function of (x,y) coordinates in terms of pixel row, column;
4. Total Efficiency of the chip;





## 2. Data extraction
## 3. Data analysis

