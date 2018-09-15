/**
 * imgResize resizes images to height of 300px or width of 500px (in that order)
 *
 * Input folder to be used as an argument
 *
 */


#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char** argv) {

  // exit if folder not inputted
  if (sizeof(argv) < 2) {
    std::cout << "Enter folder path with images to be mass-resized.\n" <<
    "Exiting..." << std::endl;
    return 0;
  }

  // make sure folder is accessable
  struct stat info;
  if (stat(argv[1], &info) != 0) {
    std::cout << "Cannot access " << argv[1] << std::endl;
    return -1;
  }

  cv::Mat inImage;
  cv::Mat outImage;

  // search through folder and resize those without -thmbnl in it

  std::vector<std::string> fileNames;
  std::vector<cv::Mat> images;
  cv::glob(argv[1], fileNames, false);
  int count = fileNames.size();

  for (int i = 0; i < count; i++) {
    images.push_back(cv::imread(fileNames[i]));
  }

  for (int i = 0; i < images.size(); i++) {
    inImage = images[i];

    // only resize the non thumbnail versions
    if (fileNames[i].find("-thmbnl") != std::string::npos) {
      continue;
    }

    if (!inImage.data) {
      std::cout << "Could not open or find image" << std::endl;
      return -1;
    }

    // resize image proportionally to have height of 300px
    int y = inImage.rows;
    int x = inImage.cols;

    int height = 300; // all images should be of this height

    if (y > height) {
      std::cout << "Resizing " << fileNames[i] << "..." << std::endl;
      int scaleFactor = y / height;

      cv::Size s(x/scaleFactor, y/scaleFactor);
      cv::GaussianBlur(inImage, inImage, cv::Size(45, 45), 1);
      cv::resize(inImage, outImage, s, cv::INTER_LANCZOS4);
    }
    else if (x > 500) {   // uh I guess width of 500
      std::cout << "Resizing " << fileNames[i] << "..." << std::endl;
      int scaleFactor = x / 500;

      cv::Size s(x/scaleFactor, y/scaleFactor);
      cv::resize(inImage, outImage, s, cv::INTER_LANCZOS4);
    }
    else {
      continue;
    }

    std::string name, ext;
    name = ext = fileNames[i];

    ext = ext.erase(0, ext.find("."));
    int length = name.length();
    name = name.erase(length-ext.length(), ext.length()) + "-thmbnl" + ext;

    cv::imwrite(name, outImage);
    std::cout << "New image: " << name << std::endl;
  }

  return 0;
}
