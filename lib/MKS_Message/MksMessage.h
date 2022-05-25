#ifndef MksSensorValue_h
#define MksSensorValue_h

struct MksSensorValue {
    int type;
    int variable;
    float value;
    int units;
};

struct MksMessage {
    uint8_t *from;
    int id;
    int numValues;
    MksSensorValue *values;
};

enum MksDataType {
    TEMPERATURE = 0,
    DISTANCE = 1,
    PERCENTAJE = 2,
};

enum MksVariableType {
    WATER = 0,
};

enum MksValueUnit {
    CENTIMETERS = 0,
    CELSIUS = 1,
};

#endif