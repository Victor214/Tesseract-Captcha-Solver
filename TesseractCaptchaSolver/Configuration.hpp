#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <vector>
#include <unordered_map>
#include "AlgorithmsEnum.hpp"

class Configuration
{
	public:
		const static std::vector<AlgorithmsEnum> algorithmsPool;
		const static std::vector<std::pair<AlgorithmsEnum, AlgorithmsEnum>> algorithmDependencyList;
		const static int isDebugEnabled;
		const static std::string tesseractPath;
		const static std::string tesseractCharPool;
		const static int maxPrintAmount;
};
#endif