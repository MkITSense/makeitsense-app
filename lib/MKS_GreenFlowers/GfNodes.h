#ifndef GFNodes_h
#define GFNodes_h

class GfNode {
    public:
        uint8_t macAddress[6];
        int id;
        String name;

        GfNode(int id, String name, const uint8_t macAddress[]) {
            GfNode::id = id;
            GfNode::name = name;
            GfNode::macAddress[0] = macAddress[0];
            GfNode::macAddress[1] = macAddress[1];
            GfNode::macAddress[2] = macAddress[2];
            GfNode::macAddress[3] = macAddress[3];
            GfNode::macAddress[4] = macAddress[4];
            GfNode::macAddress[5] = macAddress[5];
        }
};

const uint8_t MAIN_NODE_ADDRESS[] = {0x24, 0x6F, 0x28, 0x44, 0xE6, 0xB8}; // ESP32 LilyGo
const uint8_t DEEP_WELL_NODE_ADDRESS[] = {0x18, 0xFE, 0x34, 0xF1, 0x76, 0xB9};
const uint8_t MAIN_WATER_TANK_NODE_ADDRESS[] = {0x5C, 0xCF, 0x7F, 0x8C, 0x8D, 0xAE};

enum GfNodesId {
    MAIN_NODE = 0,
    DEEP_WEELL_NODE = 1,
    MAIN_WATER__TANK = 2,
};

GfNode GF_NODES[] ={
        GfNode(MAIN_NODE, "Broker Principal", MAIN_NODE_ADDRESS),
        GfNode(DEEP_WEELL_NODE, "Pozo Profundo", DEEP_WELL_NODE_ADDRESS),
        GfNode(MAIN_WATER__TANK, "Tanque Principal", MAIN_WATER_TANK_NODE_ADDRESS),
    };

#endif