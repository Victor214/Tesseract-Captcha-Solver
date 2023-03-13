#ifndef IMAGE_RESOLUTION_QUERY_HPP
#define IMAGE_RESOLUTION_QUERY_HPP

#include <iostream>
#include <memory>
#include <opencv2/opencv.hpp>

class ImageResolutionQuery
{
	public:
		std::unique_ptr<cv::Mat> image;
		ImageResolutionQuery(std::string path);
};

#endif
