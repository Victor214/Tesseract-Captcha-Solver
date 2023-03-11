#ifndef ALGORITHMS_ENUM_HPP
#define ALGORITHMS_ENUM_HPP

#include <iostream>
#include <string>

enum class AlgorithmsEnum
{
    EMPTY = 0,
    GREYSCALE,
    CONTRAST,
    ISLANDREMOVAL
};

inline std::ostream& operator<<(std::ostream& out, const AlgorithmsEnum value) {
    std::string s = "";

#define PROCESS_VAL(p) case(p): s = #p; break;
    switch (value) {
        PROCESS_VAL(AlgorithmsEnum::EMPTY);
        PROCESS_VAL(AlgorithmsEnum::GREYSCALE);
        PROCESS_VAL(AlgorithmsEnum::CONTRAST);
        PROCESS_VAL(AlgorithmsEnum::ISLANDREMOVAL);
    }
#undef PROCESS_VAL

    std::string remove = "AlgorithmsEnum::";
    int pos = s.find(remove);
    s.erase(pos, remove.size());
    return out << s;
}

#endif