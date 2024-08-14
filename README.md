###### NON-RECURSIVE FLOOD-FILL ALGORITHM (C++) AS APPLIED TO THE RICHAT STRUCTURE

![Alt text](https://i.imgur.com/R4Fsi56.png)

    C++ code to apply the non-recursive flood-fill algorithm to the
    Richat Structure in Mauritania. Uses a 1-band (single-layer) Geotiff image
    file containing Digital Elevation Model (DEM) data as input. Program is 
    expected to be run in a UNIX and/or Linux-like command-line environment.

    It will be expected you have the following command-line tools installed:
      1. aws
      2. git
      3. docker
       
###### COMMAND-LINE USAGE WITH DOCKER:

    Get the code:
    $ git clone https://github.com/satelliteArchaeology/flood_fill_richat_structure.git
    $ cd flood_fill_richat_structure/

    Get the input data:
    $ aws s3 cp s3://satellitearchaeology/subsetted_final.tif .

    Build docker image and run as container:
    $ docker build -f Dockerfile -t floodfill .
    $ DIR=$(pwd)
    $ docker run -v $DIR:$DIR floodfill $DIR/subsetted_final.tif 2000 1200 $DIR 438

###### USAGE WITHOUT DOCKER:

    Get the code and data:
    $ git clone https://github.com/satelliteArchaeology/flood_fill_richat_structure.git
    $ cd flood_fill_richat_structure/
    $ aws s3 cp s3://satellitearchaeology/subsetted_final.tif .

    Compile and run: 
    $ g++ demFloodFill.cpp geotiff.cpp -o floodfill -I/usr/include/gdal -lgdal -lm -std=c++2a
    $ ./floodfill subsetted_final.tif 2000 1200 $(pwd) 440
    
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
    14 August 2024
