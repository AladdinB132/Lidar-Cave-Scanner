# Lidar-Cave-Scanner
Code Arduino d'un capteur scanner de grottes en 3D.

Ce projet a été créé dans le cadre d'un séjour de recherche participative dans le but de développer un capteur pour scanner des grottes en 3D.
Il a été commissioné par le CNRS et organisé par Objectif Science International.

## Branchements

Composants utilisés :
- RPLidar A1
- Stepper Motor 2PH64011A
- Adafruit 5v ready Micro-SD breakout board
- Arduino Mega

### SD

- 5v → 5v
- GND → GND
- CLK → 52
- DO → 50
- DI → 51
- CS → 53

### Stepper

- \+ → 5v
- \- → GND
- IN1 → 8
- IN2 → 9
- IN3 → 10
- IN4 → 11

### Lidar

- GND → GND
- RX → TX2 (16)
- TX → RX2 (17)
- V5.0 → 5v
- GND → GND
- MOTOCTL → 5v
- VMOTO → 5v

## Crédits
- Arurikku
- tweqx
- Gaston
- Maël

## License
[GNUv3](https://www.gnu.org/licenses/gpl-3.0.en.html)
