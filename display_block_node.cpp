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
    // cout << "Autoscale mode ?" << endl;
    bool automode = true ;
    // cin >> automode ;

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

                float tone = 0.2*intensity/dist+rand()%20;
                //Scalar noises = Scalar::all(tone);
                Scalar blues = Scalar(2.5*tone,tone,0.4*tone);

                Scalar greyscale = Scalar::all(0.33*intensity/dist);

                if (automode == true){
                    int samples = 50 ;
                    float y_i = listener.last_msg.points[nbpoints-1].y;
                    float z_i = listener.last_msg.points[nbpoints-1].z;

                    circle(display_image, Point(sizex/2+y*80/z_i, sizey/2+z*80/z_i), dist*0.5, blues ,-1,8,0);
                    circle(display_image, Point(sizex/2+y_i*80/z_i, sizey/2+z_i*80/z_i), 2, Scalar::all(255) ,-1,8,0);
                }
                else{
                    circle(display_image, Point(sizex/2-y*10, sizey/2-z*10), dist*0.1, blues ,-1,8,0);
                }

            }
            for (int j=0 ; j<nbpoints ; j++){
                float x = listener.last_msg.points[j].x;
                float y = listener.last_msg.points[j].y;
                float z = listener.last_msg.points[j].z;
                float intensity = listener.last_msg.channels[0].values[j];
                float dist = sqrt(x*x+y*y+z*z);

                float tone = 0.33*intensity/dist+rand()%20;
                //Scalar noises = Scalar::all(tone);
                Scalar blues = Scalar(2.5*tone,tone,0.4*tone);

                Scalar greyscale = Scalar::all(0.33*intensity/dist);

                if (automode == true){
                    int samples = 50 ;
                    float y_i = listener.last_msg.points[nbpoints-1].y;
                    float z_i = listener.last_msg.points[nbpoints-1].z;

                    int err = 1+0.8*dist ;
                    circle(display_image, Point(sizex/2+y*80/z_i+(rand() % err - err/2), sizey/2+z*80/z_i+(rand() % err - err/2)), dist*0.2, blues ,-1,8,0);
                    circle(display_image, Point(sizex/2+y_i*80/z_i, sizey/2+z_i*80/z_i), 2, Scalar::all(255) ,-1,8,0);
                }
                else{
                    circle(display_image, Point(sizex/2-y*10, sizey/2-z*10), dist*0.1, blues ,-1,8,0);
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
