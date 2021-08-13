#include <SPI.h>
#include <SD.h>
#include <RPLidar.h>
#include <Stepper.h>


RPLidar lidar;
int timer;
File file;
const int stepsPerRevolution = 2048;
const byte sPin[] = {8, 9, 10, 11};
int stepCount = 0;

Stepper stepper(stepsPerRevolution, sPin[0], sPin[1], sPin[2], sPin[3]);


void setup()
{
  Serial.begin(115200);
  while (!Serial);

    //Define file
  
  stepper.setSpeed(5);
  
   //Initialise SD
  if (!SD.begin(53))
  {
    Serial.println("SD init failed");
  }
  file = SD.open("points.txt", FILE_WRITE);
  if(!file)
  {
    Serial.println("Failed opening points.txt");
    while(1);
  }
  // Initialise Lidar
  lidar.begin(Serial2);
  lidar.startScan();
  // Timer used for stepper
  timer = millis();
}

void loop() {
  //Main loop
  if (IS_OK(lidar.waitPoint()))
  {
    if (file)
    {
      file.println(String(lidar.getCurrentPoint().distance) + " " + String(lidar.getCurrentPoint().angle) + " " +  String((stepCount % 4096) / 4095.0 * 359.0) + " " + String(lidar.getCurrentPoint().quality));
      file.flush();
    }
    else
    {
      Serial.println("Failed to write to points.txt");
    }
  }
  else
  {
    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100)))
    {
       lidar.startScan();
       delay(1000);
    }
    else
    {
      Serial.println("Lidar has problem");
      delay(100);
    }
  }
  if (timer + 1000 <= millis())
  {
    stepper.step(-100);
    stepCount -= 100;
    timer = millis();
  }

  if (stepCount == -1000)
  {
    stepper.step(-1000);
    stepCount = 0;
  }
}
// Made by Arurikku.
