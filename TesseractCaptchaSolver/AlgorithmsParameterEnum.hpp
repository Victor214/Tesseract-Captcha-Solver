#ifndef ALGORITHMSPARAMETER_ENUM_HPP
#define ALGORITHMSPARAMETER_ENUM_HPP

enum class AlgorithmsParameterEnum
{
    // Threshold
    THRESHOLDVALUE = 0,

    // Island Removal
    ISLANDREMOVALTHRESHOLD,

    // Median Filter
    MEDIANFILTERSIZE,
};

inline std::ostream& operator<<(std::ostream& out, const AlgorithmsParameterEnum value) {
    std::string s{ "" };

#define PROCESS_VAL(p) case(p): s = #p; break;
    switch (value) {
        PROCESS_VAL(AlgorithmsParameterEnum::THRESHOLDVALUE);
        PROCESS_VAL(AlgorithmsParameterEnum::ISLANDREMOVALTHRESHOLD);
        PROCESS_VAL(AlgorithmsParameterEnum::MEDIANFILTERSIZE);
    }
#undef PROCESS_VAL

    std::string remove{ "AlgorithmsParameterEnum::" };
    int pos = s.find(remove);
    s.erase(pos, remove.size());
    return out << s;
}

#endif