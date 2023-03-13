#include "ImageResolutionQuery.hpp"

ImageResolutionQuery::ImageResolutionQuery(std::string path) {
	image = std::make_unique<cv::Mat>(cv::imread(path, cv::IMREAD_COLOR));
}