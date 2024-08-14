# use Ubuntu Linux OS
# -------------------
FROM ubuntu:latest

# install relevant software
# -------------------------
RUN apt-get update
RUN apt-get install -y apt-utils
RUN apt-get -y install make
ENV LC_ALL='en_US.utf8'

# install GCC/g++ compiler for C++
# --------------------------------
RUN apt install g++ -y

# install Geospatial Data Abstraction Library
# -------------------------------------------
RUN apt-get install gdal-bin -y
RUN apt-get install libgdal-dev -y

# Update C env vars so compiler can find gdal
# -------------------------------------------
ENV CPLUS_INCLUDE_PATH=/usr/include/gdal
ENV C_INCLUDE_PATH=/usr/include/gdal

# Add source files root path of docker container
# ----------------------------------------------
ADD demFloodFill.cpp .
ADD geotiff.cpp .
ADD geotiff.h . 

# compile the C/C++ code
# ----------------------
ARG CPP="demFloodFill.cpp geotiff.cpp"
ARG INCLUDE_DIR="/usr/include/gdal"
ARG COMPILE_FLAGS="-lgdal -lm -std=c++2a"
RUN g++ ${CPP} -o floodfill -I${INCLUDE_DIR} ${COMPILE_FLAGS}
ENTRYPOINT ["./floodfill"]
