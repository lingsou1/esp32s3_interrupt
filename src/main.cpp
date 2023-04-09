/*
接线说明:2引脚接杜邦线引出来作为电容式接口

程序说明:3引脚作为输出在0-1间变换,在0-1变换时触发中断,触发中断时2引脚测量某种值并通过串口打印出来

作者:灵首

时间:2023_3_8

*/

/*
ESP32S3通过attachInterrupt函数来实现中断。这个函数需要三个参数：

1:interruptNum：ESP32S3引脚的数字编号，用于确定哪个引脚产生中断。
2:ISR：中断服务程序，当中断发生时被调用。
3:mode：LOW CHANGE RISING FALLING
(LOW 当引脚为低电平时，触发中断
CHANGE 当引脚电平发生改变时，触发中断
RISING 当引脚由低电平变为高电平时，触发中断
FALLING 当引脚由高电平变为低电平时，触发中断)


ESP32S3的中断是用于在特定的事件（例如按键按下，边沿检测等）发生时停止程序的正常执行并调用特定的代码。这个特定的代码被称为中断服务程序（ISR）。
在ESP32S3的中断处理中，如果中断被触发，程序的执行将被暂停，直到中断服务程序处理完该中断。这可以使得程序更快地响应外部事件，并使得整个程序更快地执行。

在ESP32S3上使用PlatformIO，中断机制可以用来实现很多功能，例如：
1:监测按键按下事件
2实现边沿检测
3:控制定时器事件
4:实现串口通信等。
在PlatformIO中，你可以使用attachInterrupt函数来实现ESP32S3的中断。你需要指定中断触发引脚，中断服务程序（ISR）和触发方式（RISING, FALLING, CHANGE, LOW）。

打开中断:attachInterrupt(uint8_t pin, void (*)(void), int mode)
关闭中断:detachInterrupt(uint8_t pin)


*/

/*

ESP32-S3 有电容式触摸引脚。它有 34 个 GPIO，其中 18 个具有电容式触摸功能，
这些引脚的编号为 0, 2, 4, 12, 13, 14, 15, 27, 28, 29, 30, 31, 33, 34, 35, 36, 37 和 38。
下面将以此电容式引脚为例来编写一个简单的中断函数
其主要功能为:

*/


#include <Arduino.h>

// 定义电容式传感器引脚
#define CAP_SENSOR_PIN 2
#define test_pin 3


/*
# brief 中断函数程序
# param 无
# retval 无
*/
void cap_sensor_isr() {
  int cap_value = analogRead(CAP_SENSOR_PIN);
  Serial.print("Capacitive sensor value: ");
  Serial.println(cap_value);
}

void setup() {
  Serial.begin(115200);

  //设置引脚
  pinMode(CAP_SENSOR_PIN, INPUT);
  pinMode(test_pin, OUTPUT);
  digitalWrite(test_pin,1);

  //对引脚进行中断设置
  attachInterrupt(digitalPinToInterrupt(test_pin), cap_sensor_isr, CHANGE);
  
}

void loop() {
  digitalWrite(test_pin,!digitalRead(3));
  delay(1000);
  Serial.println(digitalRead(test_pin));

}

