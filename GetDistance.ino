#include <ros.h>
#include <std_msgs/UInt32.h>

ros::NodeHandle  nh;

std_msgs::UInt32 str_msg;
ros::Publisher distance("distance", &str_msg);

const int TrigPin_L = 8;
const int EchoPin_L = 9;

const int TrigPin_R =10;
const int EchoPin_R=11;

int distance_L;
int distance_R;
int Distance;

void setup()
{
  Serial.begin(9600);
  nh.initNode();
  nh.advertise(distance);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(12,LOW);
  digitalWrite(13,HIGH);
  pinMode(EchoPin_L, INPUT);
  pinMode(TrigPin_L, OUTPUT);

  pinMode(EchoPin_R, INPUT);
  pinMode(TrigPin_R, OUTPUT);

  //Serial.println("Ultrasonic sensor:");
}

void loop()
{
  //发一个10μs的高脉冲去触发TrigPin
  digitalWrite(TrigPin_L, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin_L, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin_L, LOW);

  distance_L = pulseIn(EchoPin_L, HIGH) / 58.0;
  if (distance_L>=100){distance_L=99;}
  digitalWrite(TrigPin_R, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin_R, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin_R, LOW);

  distance_R = pulseIn(EchoPin_R, HIGH) / 58.0;
  //distance_L = 11;
  //distance_R = 12;
  if (distance_R>=100){distance_R=99;}
  Distance = distance_L*100 + distance_R;
  //Distance = distance_L;
  str_msg.data = Distance;
  distance.publish(&str_msg);

  //Serial.print(distance_L);
  //Serial.print(Distance);
  //Serial.println();

  nh.spinOnce();
  delay(100);//Get the relationship between the delay and the frequency, delay > 60, frequency =10hz
}
