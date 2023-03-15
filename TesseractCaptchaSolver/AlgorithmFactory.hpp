#ifndef ALGORITHM_FACTORY_HPP
#define ALGORITHM_FACTORY_HPP

#include <memory>
#include <functional>
#include <unordered_map>
#include "Algorithm.hpp"
#include "AlgorithmsEnum.hpp"

using AlgorithmFactoryLambda = std::function<std::unique_ptr<Algorithm>()>;

class AlgorithmFactory
{
	public:
		AlgorithmFactory() = delete;
		static std::unique_ptr<Algorithm> createAlgorithm(AlgorithmsEnum algoEnum);

	private:
		const static std::unordered_map<AlgorithmsEnum, AlgorithmFactoryLambda> factoryMap;
};

#endif

