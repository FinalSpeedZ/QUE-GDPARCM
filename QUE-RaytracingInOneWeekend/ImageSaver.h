#ifndef IMAGE_SAVER_H
#define IMAGE_SAVER_H

#include <vector>
#include "opencv2/core.hpp"
#include <opencv2/imgcodecs.hpp> 

class ImageSaver 
{
public:
	ImageSaver(const int imageWidth, const int imageHeight);
	void setPixel(int x, int y, float r, float g, float b, int samplesPerPixel);

	void saveImage(cv::String& filename) const;

private:
	std::unique_ptr<cv::Mat> pixels;
	int imageHeight;
	int imageWidth;

	std::mutex guard;

};

#endif



