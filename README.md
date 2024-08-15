###### NON-RECURSIVE FLOOD-FILL ALGORITHM (C++) AS APPLIED TO THE RICHAT STRUCTURE

![Alt text](https://i.imgur.com/R4Fsi56.png)

    C++ code to apply the non-recursive flood-fill algorithm to the
    Richat Structure in Mauritania. Uses a 1-band (single-layer) Geotiff image
    file containing Digital Elevation Model (DEM) data as input. Program is 
    expected to be run in a UNIX and/or Linux-like command-line environment.

    It will be expected you have the following command-line tools installed:
      1. git
      2. docker
       
###### COMMAND-LINE USAGE WITH DOCKER:

    Get the code:
    $ git clone https://github.com/satelliteArchaeology/flood_fill_richat_structure.git
    $ cd flood_fill_richat_structure/

    Build docker image and run as container:
    $ docker build -f Dockerfile -t floodfill .
    $ DIR=$(pwd)

    Pass in the following:
    (1) input filename holding DEM data
    (2) starting X coordinate
    (3) starting Y coordinate
    (4) ouput directory
    (5) threshold (optional, default value is 438)
    
    $ docker run -v $DIR:$DIR floodfill $DIR/subsetted_final.tif 2000 1200 $DIR 438

    *For the input data (e.g. the file "subsetted_final.tif"), please email me if you wish
    to have it. If not, you may download publicy-available Shuttle Radar Topography Mission
    (SRTM) DEM data yourself, and create & mosaic a DEM file TIFF on your own, for youself
    to use. Such DEM raster data is available from the USGS or NASA e.g.
      https://search.earthdata.nasa.gov/search?q=SRTM

###### USAGE WITHOUT DOCKER:

    Get the code:
    $ git clone https://github.com/satelliteArchaeology/flood_fill_richat_structure.git
    $ cd flood_fill_richat_structure/

    Compile and run: 
    $ g++ demFloodFill.cpp geotiff.cpp -o floodfill -I/usr/include/gdal -lgdal -lm -std=c++2a

    Pass in the following:
    (1) input filename holding DEM data
    (2) starting X coordinate
    (3) starting Y coordinate
    (4) ouput directory
    (5) threshold (optional, default value is 438)
    
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
    Lakithra@protonmail.com
    14 August 2024
