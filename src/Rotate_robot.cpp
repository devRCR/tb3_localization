#include <cmath>
#include <geometry_msgs/Pose2D.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <tf/tf.h>

ros::Publisher pub_cmd_vel;
ros::Publisher pub_init_pose;

// Tarea de robotica:
// Usando solo quaterniones hacer que el robot gire sobre su eje hasta PI/2 y
// luego regrese a 0

// double roll, pitch, yaw=0;
double yaw = 0;
double w = 1;
double z = 0;

void odometry_callback(const nav_msgs::Odometry::ConstPtr msg) {
  geometry_msgs::Pose2D pose2d;
  pose2d.x = msg->pose.pose.position.x;
  pose2d.y = msg->pose.pose.position.y;

  /*tf::Quaternion q(
      msg->pose.pose.orientation.x,
      msg->pose.pose.orientation.y,
      msg->pose.pose.orientation.z,
      msg->pose.pose.orientation.w);

  tf::Matrix3x3 m(q);
  m.getRPY(roll, pitch, yaw);*/

  w = msg->pose.pose.orientation.w;
  z = msg->pose.pose.orientation.z;
  yaw = acos(2.0 * w * w - 1.0);
  // std::cout<<"w: "<<msg->pose.pose.orientation.w<<", yaw: "<<yaw<<std::endl;
  std::cout << "w: " << msg->pose.pose.orientation.w
            << ", z: " << msg->pose.pose.orientation.z << std::endl;
}

void turnTillGoalAndReturn(double yaw_goal, double ang_vel) {

  geometry_msgs::Twist twist;

  ros::Rate rate(5);

  // while(abs(yaw-yaw_goal)>0.01) {
  while (w >= cos(M_PI / 2.0 / 2.0) &&
         z <= sin(M_PI / 2.0 / 2.0)) { // theta = M_PI/2.0
    twist.angular.z = ang_vel;
    pub_cmd_vel.publish(twist);
    rate.sleep();
    ros::spinOnce();
  }

  twist.angular.z = 0;
  pub_cmd_vel.publish(twist);
  ros::Duration(0.5).sleep();

  // while((yaw-0)>0.01) {
  while (w < cos(0 / 2) && z > sin(0 / 2.0)) { // theta=0
    twist.angular.z = -ang_vel;
    pub_cmd_vel.publish(twist);
    rate.sleep();
    ros::spinOnce();
  }

  twist.angular.z = 0.0;
  pub_cmd_vel.publish(twist);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "tb3_localization");
  ros::NodeHandle nh;

  ros::Subscriber sub_odom = nh.subscribe("odom", 1, odometry_callback);
  pub_cmd_vel = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);
  pub_init_pose =
      nh.advertise<geometry_msgs::PoseWithCovarianceStamped>("initialpose", 1);
  geometry_msgs::PoseWithCovarianceStamped pose0;

  ros::Rate rate(5);

  for (int i = 0; i < 5; ++i) {
    pose0.header.frame_id = "map";
    pose0.header.stamp = ros::Time::now();
    pose0.pose.pose.position.x = -3.0;
    pose0.pose.pose.position.y = 1.0;
    pose0.pose.pose.position.z = 0.0;
    pose0.pose.pose.orientation.x = 0.0;
    pose0.pose.pose.orientation.y = 0.0;
    pose0.pose.pose.orientation.z = 0.0;
    pose0.pose.pose.orientation.w = 1.0;
    pose0.pose.covariance = {
        0.25, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.25, 0.0,
        0.0,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,  0.0,
        0.0,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,  0.0,
        0.0,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,  0.06853892326654787};
    pub_init_pose.publish(pose0);
    rate.sleep();
  }

  turnTillGoalAndReturn(M_PI / 2.0, M_PI / 4.0);

  return 0;
}
