#include <sstream>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include "ros/ros.h"
#include <nav_msgs/Odometry.h>
#include <freefloating_gazebo/BodySetpoint.h>

using namespace std;

class Listener
    {
    public : nav_msgs::Odometry last_msg;
        bool test;
        void Callback(const nav_msgs::Odometry& msg) {last_msg = msg; test = true;};
        };

int main(int argc, char **argv) {

    Listener listener;

    ros::init(argc, argv, "waypoint_node");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("/ecn_auv/state", 1, & Listener::Callback, & listener);
    ros::Publisher publisher = nh.advertise<freefloating_gazebo::BodySetpoint>("/ecn_auv/body_setpoint", 1);
    ros::Rate loop_rate(100);

    int traj ;
    cout<<"Choose trajectory"<<endl
        <<"0 = straight line"<<endl
        <<"1 = straight line2"<<endl
        <<"2 = big straight line"<<endl
        <<"3 = Square plop2"<<endl;
    cin>>traj;
    int indice = 0;
    int n_points=0;
    freefloating_gazebo::BodySetpoint cmd[16];

    switch(traj){



    // pour faire une ligne droite

          case 0 :
        n_points=4;

        cmd[0].pose.position.x = -20;
        cmd[0].pose.position.y = 5;
        cmd[0].pose.position.z = -10;
        cmd[0].pose.orientation.x = 0;
        cmd[0].pose.orientation.y = 0;
        cmd[0].pose.orientation.z = 0;
        cmd[0].pose.orientation.w = 1;

        cmd[1].pose.position.x = 20;
        cmd[1].pose.position.y = 5;
        cmd[1].pose.position.z = -10;
        cmd[1].pose.orientation.x = 0;
        cmd[1].pose.orientation.y = 0;
        cmd[1].pose.orientation.z = 0;
        cmd[1].pose.orientation.w = 1;

        cmd[2].pose.position.x = 20;
        cmd[2].pose.position.y = 5;
        cmd[2].pose.position.z = -10;
        cmd[2].pose.orientation.x = 0;
        cmd[2].pose.orientation.y = 0;
        cmd[2].pose.orientation.z = 0;
        cmd[2].pose.orientation.w = 1;

        cmd[3].pose.position.x = -20;
        cmd[3].pose.position.y = 5;
        cmd[3].pose.position.z = -10;
        cmd[3].pose.orientation.x = 0;
        cmd[3].pose.orientation.y = 0;
        cmd[3].pose.orientation.z = 0;
        cmd[3].pose.orientation.w = 1;
        break;

        case 1 :
        n_points=4;
        cmd[0].pose.position.x = 0;
        cmd[0].pose.position.y = -20;
        cmd[0].pose.position.z = -5;
        cmd[0].pose.orientation.x = 0;
        cmd[0].pose.orientation.y = 1;
        cmd[0].pose.orientation.z = 1;
        cmd[0].pose.orientation.w = 0;

        cmd[1].pose.position.x = 0;
        cmd[1].pose.position.y = 20;
        cmd[1].pose.position.z = -5;
        cmd[1].pose.orientation.x = 0;
        cmd[1].pose.orientation.y = 1;
        cmd[1].pose.orientation.z = 1;
        cmd[1].pose.orientation.w = 0;

        cmd[2].pose.position.x = 0;
        cmd[2].pose.position.y = 20;
        cmd[2].pose.position.z = -5;
        cmd[2].pose.orientation.x = 0;
        cmd[2].pose.orientation.y = 1;
        cmd[2].pose.orientation.z = 1;
        cmd[2].pose.orientation.w = 0;

        cmd[3].pose.position.x = 0;
        cmd[3].pose.position.y = -20;
        cmd[3].pose.position.z = -5;
        cmd[3].pose.orientation.x = 0;
        cmd[3].pose.orientation.y = 1;
        cmd[3].pose.orientation.z = 1;
        cmd[3].pose.orientation.w = 0;
        break;

        case 2 :
        n_points=4;
        cmd[0].pose.position.x = -30;
        cmd[0].pose.position.y = -30;
        cmd[0].pose.position.z = -5;
        cmd[0].pose.orientation.x = 0;
        cmd[0].pose.orientation.y = 0;
        cmd[0].pose.orientation.z = 0.38268343236;
        cmd[0].pose.orientation.w = 0.92387953251;

        cmd[1].pose.position.x = 30;
        cmd[1].pose.position.y = 30;
        cmd[1].pose.position.z = -5;
        cmd[1].pose.orientation.x = 0;
        cmd[1].pose.orientation.y = 0;
        cmd[1].pose.orientation.z = 0.38268343236;
        cmd[1].pose.orientation.w = 0.92387953251;;

        cmd[2].pose.position.x = 30;
        cmd[2].pose.position.y = 30;
        cmd[2].pose.position.z = -5;
        cmd[2].pose.orientation.x = 0;
        cmd[2].pose.orientation.y = 0;
        cmd[2].pose.orientation.z = 0.38268343236;
        cmd[2].pose.orientation.w = 0.92387953251;;

        cmd[3].pose.position.x = -30;
        cmd[3].pose.position.y = -30;
        cmd[3].pose.position.z = -5;
        cmd[3].pose.orientation.x = 0;
        cmd[3].pose.orientation.y = 0;
        cmd[3].pose.orientation.z = 0.38268343236;
        cmd[3].pose.orientation.w = 0.92387953251;
        break;


        case 3:
        n_points=16;
        cmd[0].pose.position.x = -10;
        cmd[0].pose.position.y = -10;
        cmd[0].pose.position.z = -5;
        cmd[0].pose.orientation.x = 0;
        cmd[0].pose.orientation.y = 0;
        cmd[0].pose.orientation.z = 0;
        cmd[0].pose.orientation.w = -1;

        cmd[1].pose.position.x = 10;
        cmd[1].pose.position.y = -10;
        cmd[1].pose.position.z = -5;
        cmd[1].pose.orientation.x = 0;
        cmd[1].pose.orientation.y = 0;
        cmd[1].pose.orientation.z = 0;
        cmd[1].pose.orientation.w = -1;

        cmd[2].pose.position.x = 10;
        cmd[2].pose.position.y = -10;
        cmd[2].pose.position.z = -5;
        cmd[2].pose.orientation.x = 0;
        cmd[2].pose.orientation.y = 0;
        cmd[2].pose.orientation.z = -0.707;
        cmd[2].pose.orientation.w = -0.707;

        cmd[3].pose.position.x = 10;
        cmd[3].pose.position.y = 10;
        cmd[3].pose.position.z = -5;
        cmd[3].pose.orientation.x = 0;
        cmd[3].pose.orientation.y = 0;
        cmd[3].pose.orientation.z = -0.707;
        cmd[3].pose.orientation.w = -0.707;

        cmd[4].pose.position.x = 10;
        cmd[4].pose.position.y = 10;
        cmd[4].pose.position.z = -5;
        cmd[4].pose.orientation.x = 0;
        cmd[4].pose.orientation.y = 0;
        cmd[4].pose.orientation.z = -1;
        cmd[4].pose.orientation.w = 0;

        cmd[5].pose.position.x = -10;
        cmd[5].pose.position.y = 10;
        cmd[5].pose.position.z = -5;
        cmd[5].pose.orientation.x = 0;
        cmd[5].pose.orientation.y = 0;
        cmd[5].pose.orientation.z = -1;
        cmd[5].pose.orientation.w = 0;

        cmd[6].pose.position.x = -10;
        cmd[6].pose.position.y = 10;
        cmd[6].pose.position.z = -5;
        cmd[6].pose.orientation.x = 0;
        cmd[6].pose.orientation.y = 0;
        cmd[6].pose.orientation.z = -0.707;
        cmd[6].pose.orientation.w = 0.707;

        cmd[7].pose.position.x = -10;
        cmd[7].pose.position.y = -10;
        cmd[7].pose.position.z = -5;
        cmd[7].pose.orientation.x = 0;
        cmd[7].pose.orientation.y = 0;
        cmd[7].pose.orientation.z = -0.707;
        cmd[7].pose.orientation.w = 0.707;

        cmd[8].pose.position.x = -10;
        cmd[8].pose.position.y = -10;
        cmd[8].pose.position.z = -5;
        cmd[8].pose.orientation.x = 0;
        cmd[8].pose.orientation.y = 0;
        cmd[8].pose.orientation.z = 0;
        cmd[8].pose.orientation.w = 1;

        cmd[9].pose.position.x = 10;
        cmd[9].pose.position.y = -10;
        cmd[9].pose.position.z = -5;
        cmd[9].pose.orientation.x = 0;
        cmd[9].pose.orientation.y = 0;
        cmd[9].pose.orientation.z = 0;
        cmd[9].pose.orientation.w = 1;

        cmd[10].pose.position.x = 10;
        cmd[10].pose.position.y = -10;
        cmd[10].pose.position.z = -5;
        cmd[10].pose.orientation.x = 0;
        cmd[10].pose.orientation.y = 0;
        cmd[10].pose.orientation.z = 0.707;
        cmd[10].pose.orientation.w = 0.707;

        cmd[11].pose.position.x = 10;
        cmd[11].pose.position.y = 10;
        cmd[11].pose.position.z = -5;
        cmd[11].pose.orientation.x = 0;
        cmd[11].pose.orientation.y = 0;
        cmd[11].pose.orientation.z = 0.707;
        cmd[11].pose.orientation.w = 0.707;

        cmd[12].pose.position.x = 10;
        cmd[12].pose.position.y = 10;
        cmd[12].pose.position.z = -5;
        cmd[12].pose.orientation.x = 0;
        cmd[12].pose.orientation.y = 0;
        cmd[12].pose.orientation.z = 1;
        cmd[12].pose.orientation.w = 0;

        cmd[13].pose.position.x = -10;
        cmd[13].pose.position.y = 10;
        cmd[13].pose.position.z = -5;
        cmd[13].pose.orientation.x = 0;
        cmd[13].pose.orientation.y = 0;
        cmd[13].pose.orientation.z = 1;
        cmd[13].pose.orientation.w = 0;

        cmd[14].pose.position.x = -10;
        cmd[14].pose.position.y = 10;
        cmd[14].pose.position.z = -5;
        cmd[14].pose.orientation.x = 0;
        cmd[14].pose.orientation.y = 0;
        cmd[14].pose.orientation.z = 0.707;
        cmd[14].pose.orientation.w = -0.707;

        cmd[15].pose.position.x = -10;
        cmd[15].pose.position.y = -10;
        cmd[15].pose.position.z = -5;
        cmd[15].pose.orientation.x = 0;
        cmd[15].pose.orientation.y = 0;
        cmd[15].pose.orientation.z = 0.707;
        cmd[15].pose.orientation.w = -0.707;
        break;
    }

    while(ros::ok())
        {
        if (listener.test) {

        float x = listener.last_msg.pose.pose.position.x;
        float y = listener.last_msg.pose.pose.position.y;
        float z = listener.last_msg.pose.pose.position.z;
        float ox = listener.last_msg.pose.pose.orientation.x;
        float oy = listener.last_msg.pose.pose.orientation.y;
        float oz = listener.last_msg.pose.pose.orientation.z;
        float ow = listener.last_msg.pose.pose.orientation.w;

        float diff = (cmd[indice].pose.position.x-x)*(cmd[indice].pose.position.x-x)+(cmd[indice].pose.position.y-y)*(cmd[indice].pose.position.y-y)+(cmd[indice].pose.position.z-z)*(cmd[indice].pose.position.z-z);
        float diffo = (cmd[indice].pose.orientation.x-ox)*(cmd[indice].pose.orientation.x-ox)+(cmd[indice].pose.orientation.y-oy)*(cmd[indice].pose.orientation.y-oy);
        diffo = diffo+(cmd[indice].pose.orientation.z-oz)*(cmd[indice].pose.orientation.z-oz)+(cmd[indice].pose.orientation.w-ow)*(cmd[indice].pose.orientation.w-ow);
        //cout << "diff: " << diff << " - x: " << x << " - y: " << y << " - z: " << z << endl;
        if((diff<1.)&&(diffo<0.2))
        {
                cout << "Arrived to the point number " << indice << endl;
                indice = (indice + 1) % n_points;
                cout << "Going to the point number " << indice << endl;
        }

        publisher.publish(cmd[indice]);
        }
        ros::spinOnce();
        loop_rate.sleep();
        }

    cout << "clear" << endl;
    return 0;
}
