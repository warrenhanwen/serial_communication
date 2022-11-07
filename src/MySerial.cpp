//
// Created by qzj on 2021/3/17.
//

#include "MySerial.h"
#include "serial_utility.hpp"


MySerial::MySerial(const string &com)
{
    try {
        ros_ser.setPort(com);
        ros_ser.setBaudrate(115200);
        serial::Timeout to = serial::Timeout::simpleTimeout(1000);
        ros_ser.setTimeout(to);
        ros_ser.open();
    }
    catch (serial::IOException &e) {
        ROS_ERROR_STREAM("Unable to open port ");
    }
    if (ros_ser.isOpen())
        ROS_INFO_STREAM("Serial Port opened");
    else
        ROS_ERROR_STREAM("Unable to open port ");

    while(!allMsg.empty())
        allMsg.pop();
    curMsg.clear();
}

void MySerial::Receive() {
    std::vector<uint8_t> data;
    if (ros_ser.available()) {
        size_t p = ros_ser.available(); //获取串口数据个数
        ros_ser.read(data, p);
    }

    static std::string rcved_startcode;

    for (auto iter:data){
        if(rcved_startcode.size() < 3){
            if(iter=='$'||iter=='M'||iter=='B')
                rcved_startcode.push_back(iter); // startcode "$MB", no end code
            else
                rcved_startcode.clear();
        }else if(iter=='$'){ // redetection of $ means the start of the next msg
            rcved_startcode.clear();
            rcved_startcode.push_back(iter);

            if(curMsg.size() == 5)
                allMsg.push(curMsg);
            curMsg.clear();
        }else
            if(rcved_startcode == "$MB")
                curMsg.push_back(iter);
    }

    while(!allMsg.empty()){
        int anInt = CAT32(allMsg.front()[0], allMsg.front()[1], allMsg.front()[2], allMsg.front()[3]);
        char aChar = allMsg.front()[4];
        std::cout << "int: " << anInt << ", char: " << aChar << std::endl;
        allMsg.pop();
    }
}

void MySerial::Send(){
    IntChar intChar;
    intChar.startcode[0] = 'S';
    intChar.startcode[1] = 'M';
    intChar.startcode[2] = 'B';
    intChar.anInt = 12;
    intChar.aChar = 'a';
    ros_ser.write(intChar.bytes,8);
}