#include "Configuration.hpp"
#include <utility>

const std::vector<AlgorithmsEnum> Configuration::algorithmsPool
	{ AlgorithmsEnum::GREYSCALE, AlgorithmsEnum::THRESHOLD, AlgorithmsEnum::ISLANDREMOVAL, AlgorithmsEnum::MEDIANFILTER };

// Threshold depends on Greyscale (If threshold exists, but greyscale doesn't, then it is an invalid combination. However, if greyscale exists, but)
const std::vector<std::pair<AlgorithmsEnum, AlgorithmsEnum>> Configuration::algorithmDependencyList = {
	{std::make_pair(AlgorithmsEnum::THRESHOLD, AlgorithmsEnum::GREYSCALE)},
	{std::make_pair(AlgorithmsEnum::ISLANDREMOVAL, AlgorithmsEnum::THRESHOLD)}
};

constexpr int Configuration::isDebugEnabled = 1;

const std::string Configuration::tesseractPath = "C:/Program Files/Tesseract-OCR/tessdata";
const std::string Configuration::tesseractCharPool = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

constexpr int Configuration::maxPrintAmount = 5;