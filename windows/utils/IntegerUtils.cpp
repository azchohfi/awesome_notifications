#include "IntegerUtils.h"

/*
int IntegerUtils::ExtractInteger(Object object) {
    return extractInteger(object, 0);
}

int IntegerUtils::ConvertToInt(Object object) {
    int intValue = 0;
    if(object != null) {

        if (object instanceof Number) {
            intValue = ((Number) object).intValue();
        } else
        if (object instanceof Enum) {
            intValue = ((Enum) object).ordinal();
        } else
        if (object instanceof String) {
            try {
                intValue = Integer.valueOf((String) object);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
    return intValue;
}
*/

bool IntegerUtils::IsBetween(int value, int min, int max) {
    return value >= min && value <= max;
}

/*
int IntegerUtils::ExtractInteger(Object value, Object defaultValue) {
    if(value == null){
        return ConvertToInt(defaultValue);
    }
    return ConvertToInt(value);
}
*/

int IntegerUtils::GenerateNextRandomId() {
    return distribution(generator);
}

IntegerUtils::IntegerUtils() {

}
