###### NON-RECURSIVE FLOOD-FILL ALGORITHM (C++) AS APPLIED TO THE RICHAT STRUCTURE

![Alt text](https://64.media.tumblr.com/cd5bad247d8700f31ac712b0b08e2014/aab9e694221b538f-14/s1280x1920/16fb65804eeaeaf8420910c2996e2d8f14b04fc6.pnj)

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
    (2) starting X coordinate (column)
    (3) starting Y coordinate (row)
    (4) ouput directory
    (5) threshold (optional, default value is 438)
    
    $ docker run -v $DIR:$DIR floodfill $DIR/subsetted_final.tif 2000 1200 $DIR 438

    Note:
    The input data "subsetted_final.tif" was created with a mosaic of publicly
    available SRTM data from USGS/NASA. This image file is in this repo.

###### USAGE WITHOUT DOCKER:

    Get the code:
    $ git clone https://github.com/satelliteArchaeology/flood_fill_richat_structure.git
    $ cd flood_fill_richat_structure/

    Compile and run:

    Note that you will need to point to the "include" directory
    containing your GDAL installation header files. Hence, the Geospatial Data
    Abstraction Library (GDAL) will be required, with its relevant C/C++ binaries.
    
    $ g++ demFloodFill.cpp geotiff.cpp -o floodfill -I/usr/include/gdal -lgdal -lm -std=c++2a

    Pass in the following:
    (1) input filename holding DEM data
    (2) starting X coordinate (column)
    (3) starting Y coordinate (row)
    (4) ouput directory
    (5) threshold (optional, default value is 438)
    
    $ ./floodfill subsetted_final.tif 2000 1200 $(pwd) 440
    
###### C++ version:
     
    The g++ C++ compiler c++20 or later (g++) appears to work just fine.
    On Ubuntu or similar Debian computers, this can be installed simply with:

    $ sudo apt-get install g++
       
###### Sample Outputs

![Alt text](https://64.media.tumblr.com/2f0ff695171e7610ca062f3417fb68d2/aab9e694221b538f-6f/s2048x3072/253a779bbccb0bf81bffd07470289727bce2cad0.pnj)

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
