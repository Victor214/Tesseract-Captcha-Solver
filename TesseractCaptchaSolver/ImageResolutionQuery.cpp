#include <stdexcept>
#include "ImageResolutionQuery.hpp"

ImageResolutionQuery::ImageResolutionQuery(std::string path)
	:path{path} {
	// Load captcha solution from name
	std::string name{ path };
	std::string remove{ "image/" };
	int pos{ static_cast<int>(name.find(remove)) };
	name.erase(pos, remove.size());

	pos = name.find(".");
	name.erase(pos); // Remove file extension
	this->captchaSolution = name;
}

void ImageResolutionQuery::loadImage() {
	if (path.empty())
		throw std::invalid_argument("Path is not valid");

	image = std::make_unique<cv::Mat>(cv::imread(path, cv::IMREAD_COLOR));
}

bool ImageResolutionQuery::isCorrectSolution() {
	if (captchaSolution.empty() || captchaProposedSolution.empty())
		throw std::invalid_argument("Provided captcha solutions are empty");

	return captchaSolution == captchaProposedSolution;
}