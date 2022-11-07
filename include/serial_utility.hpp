
#ifndef CATKIN_SERIAL_COMMUNICATION_SERIAL_UTILITY_HPP
#define CATKIN_SERIAL_COMMUNICATION_SERIAL_UTILITY_HPP


typedef union {
    struct {
        char startcode[3]; // use '$MR'
        int32_t anInt;
        char aChar;
    };
    unsigned char bytes[8];
}IntChar;

//#define CAT32(a,b,c,d) (((a & 0x000000FF) << 24) | ((b & 0x000000FF) << 16) | ((c & 0x000000FF) << 8) | ((d & 0x000000FF) << 0))
#define CAT32(a,b,c,d) (((a & 0x000000FF) << 0) | ((b & 0x000000FF) << 8) | ((c & 0x000000FF) << 16) | ((d & 0x000000FF) << 24))

#endif //CATKIN_SERIAL_COMMUNICATION_SERIAL_UTILITY_HPP
