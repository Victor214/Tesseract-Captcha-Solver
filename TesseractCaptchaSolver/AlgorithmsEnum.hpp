#ifndef ALGORITHMS_ENUM_HPP
#define ALGORITHMS_ENUM_HPP

#include <iostream>
#include <string>

enum class AlgorithmsEnum
{
    EMPTY = 0,
    IMAGEREADER,
    GREYSCALE,
    THRESHOLD,
    ISLANDREMOVAL,
    TESSERACTSCANNER,
};

inline std::ostream& operator<<(std::ostream& out, const AlgorithmsEnum value) {
    std::string s = "";

#define PROCESS_VAL(p) case(p): s = #p; break;
    switch (value) {
        PROCESS_VAL(AlgorithmsEnum::EMPTY);
        PROCESS_VAL(AlgorithmsEnum::IMAGEREADER);
        PROCESS_VAL(AlgorithmsEnum::GREYSCALE);
        PROCESS_VAL(AlgorithmsEnum::THRESHOLD);
        PROCESS_VAL(AlgorithmsEnum::ISLANDREMOVAL);
        PROCESS_VAL(AlgorithmsEnum::TESSERACTSCANNER);
    }
#undef PROCESS_VAL

    std::string remove = "AlgorithmsEnum::";
    int pos = s.find(remove);
    s.erase(pos, remove.size());
    return out << s;
}

#endif