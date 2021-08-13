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

const char* pth = "POINTS.TXT";

Stepper stepper(stepsPerRevolution, sPin[0], sPin[1], sPin[2], sPin[3]);


void setup()
{
  Serial.begin(115200);
  while (!Serial);

    //Define file
  
  stepper.setSpeed(5);
  
   //Initialise SD
  if (SD.begin(53))
  {
    Serial.println("Init epic");
  }
  else
  {
    Serial.println("Init not epic");
  }
  file = SD.open("points.txt", FILE_WRITE);
  if(!file)
  {
    Serial.println("Big yikes");
    //while(1);
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
      Serial.println("Writing...");
      file.println(String(lidar.getCurrentPoint().distance) + " " + String(lidar.getCurrentPoint().angle) + " " +  String(stepCount) + " " + String(lidar.getCurrentPoint().quality));
      file.flush();
      Serial.println("epicly wrote");
    }
    else
    {
      Serial.println("SD not very epic");
    }
  }
  else
  {    
    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100)))
    {
       lidar.startScan();
       Serial.println("panik");
       delay(1000);
       Serial.println("kalm");
    }
    else
    {
      Serial.println("eek");
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
