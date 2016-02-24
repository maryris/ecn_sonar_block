#include <sstream>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include "ros/ros.h"
#include <sensor_msgs/PointCloud.h>
#include <freefloating_gazebo/BodySetpoint.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace cv;
using namespace std;

class Listener
    {
    public : sensor_msgs::PointCloud last_msg;
        bool test;
        void Callback(const sensor_msgs::PointCloud& msg) {last_msg = msg; test = true;}
        };

int main(int argc, char **argv){

    Listener listener;
    bool automode = true ;

    ros::init(argc, argv, "display_node");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("/ecn_auv/sonar", 1, & Listener::Callback, & listener);
    ros::Rate loop_rate(100);

    namedWindow("Sea Bed");
    startWindowThread();

    // Create black empty images
    int sizey = 800;
    int sizex = 700;
    Mat display_image = Mat::zeros(sizey-250, sizex, CV_8UC3);

    while(ros::ok())
        {
        if (listener.test) {

            int nbpoints = listener.last_msg.points.size();
            for (int i=0 ; i<nbpoints ; i++){
                float x = listener.last_msg.points[i].x;
                float y = listener.last_msg.points[i].y;
                float z = listener.last_msg.points[i].z;
                float intensity = listener.last_msg.channels[0].values[i];
                float dist = sqrt(x*x+y*y+z*z);
                Scalar greyscale = Scalar::all(0.33*intensity/dist);
                if (automode == true){
                    int samples = 50 ;
                    float y_i = listener.last_msg.points[0].y;
                    float z_i = listener.last_msg.points[0].z;
                    /*
                    float y_r_u = listener.last_msg.points[nbpoints-70*samples].y;
                    float z_r_u = listener.last_msg.points[nbpoints-70*samples].z;
                    float y_l_u = listener.last_msg.points[nbpoints-70*samples-1].y;
                    float z_l_u = listener.last_msg.points[nbpoints-70*samples-1].z;
                    float y_l_d = listener.last_msg.points[nbpoints-1].y;
                    float z_l_d = listener.last_msg.points[nbpoints-1].z;
                    float y_r_d = listener.last_msg.points[nbpoints-samples].y;
                    float z_r_d = listener.last_msg.points[nbpoints-samples].z;*/

                    circle(display_image, Point(sizex/2+y*250/y_i, sizey/2-z*300/z_i), dist*0.1, greyscale ,-1,8,0);
/*
                    circle(display_image, Point(sizex/2+y_r_u*250/y_i, sizey/2-z_r_u*300/z_i), 2, Scalar::all(255) ,-1,8,0);
                    circle(display_image, Point(sizex/2+y_l_u*250/y_i, sizey/2-z_l_u*300/z_i), 2, Scalar::all(255) ,-1,8,0);
                    circle(display_image, Point(sizex/2+y_l_d*250/y_i, sizey/2-z_l_d*300/z_i), 2, Scalar::all(255) ,-1,8,0);
                    circle(display_image, Point(sizex/2+y_r_d*250/y_i, sizey/2-z_r_d*300/z_i), 2, Scalar::all(255) ,-1,8,0);

                    float m_l = (z_l_u-z_l_d)/(y_l_u-y_l_d);
                    float p_l = z_l_u-m_l*y_l_u;
                    float m_r = (z_r_u-z_r_d)/(y_r_u-y_r_d);
                    float p_r = z_r_u-m_r*y_r_u;
                    line(display_image,Point(sizex/2+0*250/y_i,sizey/2-(0*m_l+p_l)*300/z_i),
                                        Point(sizex/2+200*250/y_i,sizey/2-(200*m_l+p_l)*300/z_i),Scalar::all(255),1,8,0);
                    line(display_image,Point(sizex/2+0*250/y_i,sizey/2-(0*m_r+p_r)*300/z_i),
                                        Point(sizex/2+2000*250/y_i,sizey/2-(2000*m_r+p_r)*300/z_i),Scalar::all(255),1,8,0);*/
                }
                else{
                    // line(display_image, Point(sizex/2+y*10, sizey/2-z*10), Point(sizex/2+y*10, sizey/2-z*10), Scalar(255,255,255),1,8);
                    circle(display_image, Point(sizex/2+y*10, sizey/2-z*10), dist*0.1, greyscale ,-1,8,0);
                }

            }
            // Display
            imshow("Sea Bed", display_image );
            waitKey(100);
            display_image = Mat::zeros(sizey-250, sizex, CV_8UC3);
        }

        ros::spinOnce();
        loop_rate.sleep();
        }

    cout << "clear" << endl;
    return 0;
}

