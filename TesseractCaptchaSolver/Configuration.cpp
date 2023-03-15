#include "Configuration.hpp"
#include <utility>

const std::vector<AlgorithmsEnum> Configuration::algorithmsPool
	{ AlgorithmsEnum::GREYSCALE, AlgorithmsEnum::THRESHOLD, AlgorithmsEnum::ISLANDREMOVAL, AlgorithmsEnum::MEDIANFILTER, AlgorithmsEnum::TRIMWHITESPACE };

// Threshold depends on Greyscale (If threshold exists, but greyscale doesn't, then it is an invalid combination. However, if greyscale exists, but threshold doesn't, it is still valid)
const std::vector<std::pair<AlgorithmsEnum, AlgorithmsEnum>> Configuration::algorithmDependencyList = {
	{std::make_pair(AlgorithmsEnum::THRESHOLD, AlgorithmsEnum::GREYSCALE)},
	{std::make_pair(AlgorithmsEnum::ISLANDREMOVAL, AlgorithmsEnum::THRESHOLD)},
	{std::make_pair(AlgorithmsEnum::TRIMWHITESPACE, AlgorithmsEnum::GREYSCALE)},

	// Temp
	//{std::make_pair(AlgorithmsEnum::MEDIANFILTER, AlgorithmsEnum::ISLANDREMOVAL)},
	//{std::make_pair(AlgorithmsEnum::TRIMWHITESPACE, AlgorithmsEnum::MEDIANFILTER)},
	//{std::make_pair(AlgorithmsEnum::GREYSCALE, AlgorithmsEnum::THRESHOLD)},
	//{std::make_pair(AlgorithmsEnum::THRESHOLD, AlgorithmsEnum::ISLANDREMOVAL)},
	//{std::make_pair(AlgorithmsEnum::ISLANDREMOVAL, AlgorithmsEnum::MEDIANFILTER)},
	//{std::make_pair(AlgorithmsEnum::MEDIANFILTER, AlgorithmsEnum::TRIMWHITESPACE)},
};

constexpr int Configuration::isDebugEnabled{ 1 };

const std::string Configuration::tesseractPath{ "C:/Program Files/Tesseract-OCR/tessdata" };
const std::string Configuration::tesseractCharPool{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" };

constexpr int Configuration::maxPrintAmount{ 5 };