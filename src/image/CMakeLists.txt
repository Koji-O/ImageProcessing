cmake_minimum_required(VERSION 2.8)

add_library(Image STATIC
  image.cpp
  coreSharpening.cpp    
  coreRemoveNoise.cpp
  coreExtractObject.cpp 
  coreExtractContour.cpp
  )