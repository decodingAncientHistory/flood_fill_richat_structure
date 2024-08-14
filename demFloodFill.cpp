/*
Read Digital Elevation Model (DEM) file, and perform flood-fill algorithm. 
Write flood-fill binary mask to byte Geotiff file for use in GIS.

Usage: Compile/use a Linux or UNIX-like command-line. Use g++ compiler 
     and supply appropriate flags to local installation of the C/C++ 
     Geospatial Data Abstraction Library (GDAL).

     Also pass in file-name of Geotiff image file or similar (e.g. JPG),
     starting x and y coordinates (x first, then y), output directory, and
     optionally, a threshold value for elevation in the DEM (default below is 438m for Richat).

     $ g++ demFloodFill.cpp geotiff.cpp -o floodfill -I/usr/include/gdal -lgdal -lm -std=c++17
     $ ./floodfill subsetted_final.tif 2000 1200 $(pwd) 440
       or
     $ ./floodfill subsetted_final.tif 2000 1200 $(pwd)

     Note: Replace path /usr/include/gdal with your local C/C++ directory of GDAL
       "include" and/or GDAL header files.

Environment:
  DEBUG=1 -- Enable debugging.

Dependencies:
  Use local installation of C/C++ Geospatial Data and Abstraction Library (GDAL)
  and related binaries.

History:
  G. Michalitsianos (Annapolis, MD) 2024-08-03
*/
#include <iostream>
#include <string>
#include "stdlib.h"
#include <stdexcept>
#include <sstream>
#include <filesystem>

#include <tuple>
#include <set>

#include "geotiff.h"
typedef std::string String;

// constants - DEBUG = 0 is false, 1 is true
// *****************************************
#define DEBUG 0
#define ELEVATION_THRESH 438

void flood_fill(char** mask, int nrows, int ncols, int sx, 
		int sy, int** dem, int thresh = ELEVATION_THRESH) {
  // define sets of tuples for pixels filled, not-filled 
  // ***************************************************
  std::set<std::tuple<int, int>> filled;
  std::set<std::tuple<int, int>> fill;
  fill.insert(std::make_tuple(sy, sx));
  mask[sy][sx] = 1;

  while(fill.size() > 0) {
    // get the last element in the fill-list of pixels,
    // then remove or "pop()" it
    // ************************************************
    std::tuple<int, int> lastXY = *fill.rbegin();
    auto y = std::get<0>(lastXY);
    auto x = std::get<1>(lastXY);
    fill.erase(std::prev(fill.end()));

    if((y == nrows - 1) || (x == ncols - 1) || (x < 0) || (y < 0)) {
      continue;
    }

    if(dem[y][x] >= thresh) {
      continue;
    }

    if(mask[y][x] == 1) {
      // update the mask and surrounding pixels
      // **************************************
      mask[y][x] = 1;
      mask[y][x - 1] = 1;
      mask[y][x + 1] = 1;
      mask[y - 1][x] = 1;
      mask[y + 1][x] = 1;

      filled.insert(std::make_tuple(y, x));
      
      const bool southFilled = filled.find(
		      std::make_tuple(y - 1, x)) != filled.end();
      const bool northFilled = filled.find(
		      std::make_tuple(y + 1, x)) != filled.end();
      const bool eastFilled = filled.find(
		      std::make_tuple(y, x + 1)) != filled.end();
      const bool westFilled = filled.find(
		      std::make_tuple(y, x - 1)) != filled.end();

      if(!northFilled) fill.insert(
		      std::make_tuple(y + 1, x));
      if(!southFilled) fill.insert(
		      std::make_tuple(y - 1, x));
      if(!eastFilled) fill.insert(
		      std::make_tuple(y, x + 1));
      if(!westFilled) fill.insert(
		      std::make_tuple(y, x - 1));
    }
  }
}

void usage() {
  std::cout << "Usage (example): " << std::endl;
  std::cout << "  $ INCLUDE_DIR=/usr/include/gdal" << std::endl;
  std::cout << "  $ g++ demFloodFill.cpp geotiff.cpp \\ " << std::endl;
  std::cout << "    -o floodfill -I$INCLUDE_DIR -lgdal -lm -std=c++2a" << std::endl;
  std::cout << "  $ ./floodfill <image_file_name|str> <start_x|int> " << std::endl;
  std::cout << "    <start_y|int> <outdir|str> <thresh|int>" << std::endl;
  std::cout << "Note optional final argument 'thresh' or elevation threshold. to pass-in." << std::endl;
  exit(1);
}

int main(int argc, char* argv[]) {

  // make sure we have appropriate number of args.
  // *********************************************	
  if(argc < 5) {
    usage();
    throw std::invalid_argument("ERROR: received wrong no. of args.");
  }

  // get starting point coordinates
  //  e.g. x, y = 2000, 1200
  // ******************************
  int start_x = 0; 
  int start_y = 0;
  int elevation_thresh = -9999;

  const char* start_x_str = argv[2];
  const char* start_y_str = argv[3];
  const char* outdir = argv[4];
  const char* elevation_thresh_str = "";
  
  if(argc > 4) {
    elevation_thresh_str = argv[5];
  }

  // attempt to get starting x (column) coordinate
  // *********************************************
  try {
    start_x = atoi(start_x_str);
  } catch(...) {
    std::cout << "ERROR: For start x, integer is required." << std::endl;
    usage();
  };

  // attempt to get starting y (row) coordinate
  // ******************************************
  try {
    start_y = atoi(start_y_str);
  } catch(...) {
    std::cout << "ERROR: For start y, integer is required." << std::endl;
    usage();
  }

  // get input elevation threshold, if passed-in
  // *******************************************
  if(argc > 5) {
    try {
      elevation_thresh = atoi(elevation_thresh_str);
    } catch(...) {
      std::cout << "Threshold (integer) not passed-in. Defaulting to 438." << std::endl;
    }
  }

  // make sure elevation threshold is above zero
  // *******************************************
  if((elevation_thresh < 1) && (argc > 5)) {
    std::cout << "Threshold passed-in must be POSITIVE (>0) integer. Exiting ..." << std::endl;
    usage();
  }

  // get the input filename of geotiff, open it up
  // *********************************************
  const char* tiffname = argv[1];
  geotiff tiff(tiffname);

  // get dimensions of input DEM geotiff image file (2d)
  // also get DEM data itself as array of integers
  // ***************************************************
  int* dimensions = (&tiff)->getDimensions();
  int **dem = (&tiff)->getArrayData();
  int nrows = dimensions[0];
  int ncols = dimensions[1];

  // make sure start x, y are within domain of image
  // ***********************************************
  if(start_x >= ncols) {
    throw std::invalid_argument("ERROR: start x exceeds image X dimension.");
  } else if(start_y >= nrows) {
    throw std::invalid_argument("ERROR: start y exceeds image Y dimension.");
  } else if(start_x < 1) {
    throw std::invalid_argument("ERROR: start x should be positive integer.");
  } else if(start_y < 1) {
    throw std::invalid_argument("ERROR: start y should be positive integer.");	  
  };

  // allocate memory to hold binary mask of 1s and 0s
  // ************************************************
  char **mask = new char*[nrows];
  for(int r = 0; r < nrows; ++r) mask[r] = new char[ncols];

  if(!(elevation_thresh == -9999)) { // use thresh. passed-in, if it was
    flood_fill(mask, nrows, ncols, start_x, start_y, dem, elevation_thresh);
  } else { // use default value of elevation threshold
    flood_fill(mask, nrows, ncols, start_x, start_y, dem);
  }

  // write out binary Masks of 1's and 0's to
  // a binary mask
  // ****************************************
  String outname = (String)outdir + (String)"/floodFill_final.tif";
  geotiff::writeGeotiff(outname, tiff.getProjection(), 
		  tiff.getGeotransform(), mask, nrows, ncols);
  
  // free up memory
  // **************
  for(int r = 0; r < nrows; ++r) delete [] mask[r]; 
  delete [] mask;
  return 0;
}
