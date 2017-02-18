cmake_minimum_required(VERSION 2.8)

add_library(Image STATIC
  image.cpp
  sharpening.cpp    
  remove_noise.cpp
  extract_object.cpp 
  extract_contour.cpp
  )