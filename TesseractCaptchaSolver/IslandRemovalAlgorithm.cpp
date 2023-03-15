#include <opencv2/opencv.hpp>
#include "IslandRemovalAlgorithm.hpp"

IslandRemovalAlgorithm::IslandRemovalAlgorithm()
	:Algorithm{ AlgorithmsEnum::ISLANDREMOVAL } {
	insertMaxParameterConfiguration();
}

void IslandRemovalAlgorithm::process(ImageResolutionQuery& imageResolutionQuery) {
	cv::Mat& image = *(imageResolutionQuery.image);
	cv::Mat invertedImage = cv::Scalar::all(255) - image;
	cv::Mat mask = cv::Mat::zeros(invertedImage.size(), CV_8UC1);

	// Get information about components and their sizes
	cv::Mat labels, stats, centroids;
	int totalComponents = cv::connectedComponentsWithStats(invertedImage, labels, stats, centroids, 8, CV_32S);

	// Iterate through components, removing the ones below threshold by total area
	int areaThreshold = minThreshold + (this->parameters[AlgorithmsParameterEnum::ISLANDREMOVALTHRESHOLD] * (maxThreshold - minThreshold)) / (this->maxParameters[AlgorithmsParameterEnum::ISLANDREMOVALTHRESHOLD] - 1);
	for (int i = 1; i < totalComponents; i++)
	{
		if (stats.at<int>(i, cv::CC_STAT_AREA) < areaThreshold)
		{
			// Creates a component mask with all of current island's pixels, and adds it up to mask.
			cv::Mat componentMask;
			cv::compare(labels, i, componentMask, cv::CMP_EQ);
			mask.setTo(255, componentMask);
		}
	}

	// Removes mask from inverted image, and outputs to image
	cv::compare(invertedImage, mask, image, cv::CMP_EQ);
	//cv::imshow("Result", image);
	//cv::waitKey(0);

	Algorithm::process(imageResolutionQuery);
}