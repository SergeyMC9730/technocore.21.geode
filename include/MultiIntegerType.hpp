#pragma once

#pragma pack(push, 1)

union MultiIntegerType {
    int asInt;
    float asFloat;
    // use isIntActive[4] to get information about this
    bool isIntActive[5];
};

#pragma pack(pop)