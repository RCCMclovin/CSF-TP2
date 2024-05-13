#!/bin/bash

docker build -t files_size .

## 5MB
#docker run -v $(pwd)/output:/output -e FILE_SIZE=5000 files_size
## 500k
#docker run -v $(pwd)/output:/output -e FILE_SIZE=500 files_size
## 10MB
docker run -v $(pwd)/output:/output -e FILE_SIZE=10000 files_size
