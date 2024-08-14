#ifndef GEOTIFF_H_
#define GEOTIFF_H_
#include "gdal_priv.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <string>
typedef std::string String;

class geotiff {
  private:
    const char* filename = nullptr;
    GDALDataset *ds;
    double geotransform[6];
    int dimensions[2];
    int nrows, ncols;
  public:
    // constructor and deconstructor
    // *****************************
    geotiff();
    geotiff(const char*);
    ~geotiff();

    // instance methods
    // ****************
    const char* getFileName();
    const char* getProjection();
    double *getGeotransform();
    int *getDimensions();
    static void writeGeotiff(
    String, const char*, double*, char**, int, int);
    int **getArrayData();
};
#endif
