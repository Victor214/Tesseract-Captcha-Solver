#include "Configuration.hpp"

const std::vector<AlgorithmsEnum> Configuration::algorithmsPool{ AlgorithmsEnum::GREYSCALE, AlgorithmsEnum::CONTRAST, AlgorithmsEnum::ISLANDREMOVAL };
constexpr int Configuration::isDebugEnabled = 1;