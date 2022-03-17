#pragma once

#include <random>

class IntegerUtils {
 public:
    // Note: sometimes Json parser converts Integer into Double objects
    //static int ExtractInteger(Object object);

    //static int ConvertToInt(Object object);

    static bool IsBetween(int value, int min, int max);

    // Note: sometimes Json parser converts Integer into Double objects
    //static int ExtractInteger(Object value, Object defaultValue);

    static int GenerateNextRandomId();

 private:
    IntegerUtils();

    static inline std::default_random_engine generator;
    static inline std::uniform_int_distribution<int> distribution;
};
