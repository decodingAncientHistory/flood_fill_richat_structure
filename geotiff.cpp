#include "geotiff.h"

// overloaded constructors
// ***********************
geotiff::geotiff() {};

geotiff::geotiff(const char* fname) {
  filename = fname;
  GDALAllRegister();

  // open dataset, get dims.
  // ************
  ds = (GDALDataset*) GDALOpen(filename, GA_ReadOnly);
  nrows = ds->GetRasterYSize();
  ncols = ds->GetRasterXSize();
};

// destructor
// **********
geotiff::~geotiff() {
  GDALClose(ds);
  GDALDestroyDriverManager();
};

const char* geotiff::getFileName() {
  // get the filename
  // ****************
  return filename;
};

const char* geotiff::getProjection() {
  // get the projection
  // ******************
  return ds->GetProjectionRef();
};

double* geotiff::getGeotransform() {
  // get the geotransform
  // ********************
  ds->GetGeoTransform(geotransform);
  return geotransform;
};

int* geotiff::getDimensions() {
  // get the dimensions
  // ******************
  dimensions[0] = nrows;
  dimensions[1] = ncols;
  return dimensions;
};

void geotiff::writeGeotiff(
		String outname, const char* prj, 
		double* gt, char** data, int nrows, int ncols) {
  // class (static) method (not used with instance) to write a Geotiff
  // that contains byte data ... 1 band of 2d array data bytes
  // *****************************************************************
  
  // remove file if already exists
  // *****************************
  if(access(outname.c_str(), F_OK) != -1) {
    std::remove(outname.c_str());
  }
	
  GDALDataset *geotiffDataset;
  GDALDriver *driverGeotiff;
  driverGeotiff = GetGDALDriverManager()->GetDriverByName(
		  "GTiff");
  geotiffDataset = driverGeotiff->Create(
		  outname.c_str(), ncols, nrows, 1, GDT_Byte, NULL);
  geotiffDataset->SetGeoTransform(gt);
  geotiffDataset->SetProjection(prj);
 
  char *rowBuff = (char*) CPLMalloc(sizeof(char) * ncols);
 
  for(int row = 0; row < nrows; row++) {
    for(int col = 0; col < ncols; col++) {
      if(data[row][col] == 1) {
        rowBuff[col] = (char)data[row][col];
      } else {
        rowBuff[col] = 0;
      }
    }
    CPLErr err = geotiffDataset->GetRasterBand(1)->RasterIO(
		    GF_Write, 0, row, ncols, 1, 
		    rowBuff, ncols, 1, GDT_Byte, 0, 0);
  }
  CPLFree(rowBuff);
  GDALClose(geotiffDataset);
}

int** geotiff::getArrayData() {
  // read band from geotiff as a 2d Array of ints
  // ********************************************
  GDALDataType bandType = GDALGetRasterDataType(ds->GetRasterBand(1));
  int nbytes = GDALGetDataTypeSizeBytes(bandType);
  int **bandLayer = new int*[nrows];

  // allocate pointer to memory block for one row (scanline) 
  // in 2D Geotiff array.
  // *******************************************************  
  int16_t *rowBuff = (int16_t*) CPLMalloc(nbytes * ncols);
  
  for(int row = 0; row < nrows; row++)
  {
    // read the scanline into the
    // dynamically allocated row-buffer
    // ********************************
    CPLErr e = ds->GetRasterBand(1)->RasterIO(
      GF_Read, 0, row, ncols, 1, rowBuff, ncols, 1, bandType, 0, 0);
    if(!(e == 0)) {
      std::cout << "Warning: Unable to read scanline in Geotiff!" << std::endl;
      exit(1);
    }
    bandLayer[row] = new int[ncols];
    for(int col = 0; col < ncols; col++) {
      bandLayer[row][col] = (int) rowBuff[col];
    }
  }
  CPLFree(rowBuff);
  return bandLayer;
};
