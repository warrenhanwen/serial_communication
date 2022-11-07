#include "MySerial.h"
#include "ros/ros.h"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "serial_communication_node");
    ros::NodeHandle nh;

    MySerial mySerial("/dev/ttyUSB1");

    ros::Rate loop_rate(200); // todo: the rate of msg
    while(ros::ok()){
        mySerial.Receive();
        mySerial.Send();

        loop_rate.sleep();
    }
}
