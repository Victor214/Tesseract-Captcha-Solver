#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <vector>
#include "AlgorithmsEnum.hpp"

class Configuration
{
	public:
		const static std::vector<AlgorithmsEnum> algorithmsPool;
		const static int isDebugEnabled;
		
};
#endif