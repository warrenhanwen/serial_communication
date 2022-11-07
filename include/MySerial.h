#ifndef SRC_MYSERIAL_H
#define SRC_MYSERIAL_H
#include <string>
#include <serial/serial.h>
#include <queue>
#include <ros/publisher.h>

using namespace std;
typedef unsigned char uint8;

class MySerial {

public:
    MySerial(const string &com);

    void Run();

    void Receive();
    void Send();

private:
    serial::Serial ros_ser;
    string curMsg;
    queue<string> allMsg;
};


#endif //SRC_MYSERIAL_H
