#ifndef MksSensorValue_h
#define MksSensorValue_h

struct MksReading {
    int sensorType;
    int unit;
    int unitType;
    float value;
};

struct MksMessage {
    int from;
    float values[4];
};

enum MksReadingUnitType {
    TEMPERATURE = 0,
    DISTANCE = 1,
};

enum MksSensorType {
    WATER_LEVEL = 0,
    WATER_TANK = 1,
};

enum MksReadingUnit {
    CENTIMETERS = 0,
    CELSIUS = 1,
};

#endif