# imgResize
Shrinks all images in a selected folder (because I'm too lazy to do it manually :))

Resizes images to be 300px in height or 500px in width (in that order), or do nothing.
Will only resize images that do not end with "-thmbnl" because that means it's already been resized.

Uses OpenCV 4.0.0

Compile with g++ 
g++ imgResize.cpp -o out `pkg-config --cflags --libs opencv` -std=c++14
