#include <SPI.h>
#include <SD.h>
#include <RPLidar.h>
#include <Stepper.h>


RPLidar lidar; // Objet lidar

void WRITE();
const int stepsPerRevolution = 2048;
int stepCount = 0;  

Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

// Fonctions du lidar

// Lance la lecture du lidar, si la lecture échoue elle renvoie false
bool lancerLecture() {
  return IS_OK(lidar.waitPoint());
}
// fonction de la lecture de la distance
float lectureDistance() {
  return lidar.getCurrentPoint().distance;
}
// fonction de la lecture de l'angle du LiDAR
float lectureAngleLidar() {
  return lidar.getCurrentPoint().angle;
}
// fonction de la lecture de l'angle du moteur
float lectureAngleMoteur() {
  return rand();
}
// fonction de la lecture de la qualité des données 
int lectureQualite() {
  return lidar.getCurrentPoint().quality;
}

int timer;

// fonction de lecture de toute les données 
String lectureLidar();
String lectureLidar() {
  return String(lectureDistance()) + " " + String(lectureAngleLidar()) + " " + String(lectureAngleMoteur()) + " " + String(lectureQualite()) + "\n" ;
}

void setup() {
  // Initialise le port série
  myStepper.setSpeed(1);
  Serial.begin(9600);
  while (!Serial) {/*rien*/}

  // Initialise la carte SD
  Serial.println("Initialisation de la carte SD...");
  if (!SD.begin(53)) {
    Serial.println("initialisation ratée!");
  }
  else {
    Serial.println("initilisation finie.");
  }

  // Initialisation du Lidar
  lidar.begin(Serial);
  lidar.startScan();

  // Timer
  timer = millis();
}

// Fonction d'écriture
void WRITE(){
  // on ouvre le fichier POINTS.TXT 
  File myFile = SD.open("POINTS.TXT", FILE_WRITE);
  if (myFile) 
  // on écrit dans le fichier les données
  {
    Serial.print("Writing to ");
    Serial.println("POINTS.TXT");
    myFile.print(lectureLidar());  
    Serial.println("Done");
    myFile.close();
  }
  else
  // Si le fichier ne s'ouvre pas alors on affiche "erreur lors de l'ouverture du fichier"
  {
    Serial.println("erreur lors de l'ouverture du fichier");
  }
}

void loop(){
  //lance l'écriture si les données sont bien prises, sinon affiche "la lecture a échouée"
  if (lancerLecture() == true) {
    WRITE();
    }
  else {
    Serial.println("La lecture a échouée");
    }

  if (timer + 1000 <= millis()) {
    myStepper.step(-100);
    Serial.print("steps:");
    Serial.println(stepCount);
    stepCount -= 100;

    timer = millis();
  }

  if (stepCount == -1000) {
    myStepper.setSpeed(5);
    myStepper.step(-1000);

    myStepper.setSpeed(5);
    stepCount = 0;
  }
  
}
// Made by Gaston, Benoit, and Maël 
