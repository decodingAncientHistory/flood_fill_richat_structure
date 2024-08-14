###### NON-RECURSIVE FLOOD-FILL ALGORITHM (C++) AS APPLIED TO THE RICHAT STRUCTURE

![Alt text](https://i.imgur.com/R4Fsi56.png)

    C++ code to apply the non-recursive flood-fill algorithm to the
    Richat Structure in Mauritania. Uses a 1-band (single-layer) Geotiff image
    file containing Digital Elevation Model (DEM) data as input. Program is 
    expected to be run in a UNIX and/or Linux-like command-line environment.
   
###### INSTALLATION:

    To Be filled in.
       
###### MORE EXAMPLE USAGE WITH DOCKER:

    To be filled in.
      
###### C++ version:
     
    The g++ C++ compiler c++20 or later (g++) appears to work just fine.
    On Ubuntu or similar Debian computers, this can be installed simply with:

    $ sudo apt-get install g++
       
###### Sample Outputs

![Alt text](https://i.imgur.com/1wvkGOe.png)

    A 1-band Geotiff is written out to disk. This Geotiff contains 1s and 0s. The 1s 
    mark areas of so-called "flood-fill." This is the area that is "filled-in" by the 
    algorithm according to the elevation boundaries of the Digital Elevation Model.

    We can use any common plotting software (e.g. Python, Matlab, QGIS, GrADS, etc.)
    to visualize the output (here we are using's Python 3.x's Matplotlib module.
        
###### @author: 
    Gerasimos Michalitsianos
    gerasimosmichalitsianos@protonmail.com
    5 August 2024
