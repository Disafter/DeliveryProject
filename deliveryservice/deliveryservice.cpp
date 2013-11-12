// deliveryservice.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;
using std::ifstream;

enum planetOrder{MERCURY, VENUS, EARTH, MARS, JUPITER, SATURN, URANUS, NEPTUNE};

struct planet
{
	string name;
	float distance;
	float surfaceGravity;
};

struct shuttle
{
	string cargoType;
	planetOrder pickupPlanet;
	planetOrder deliveryPlanet;
	float speed;
	float totalTravelDistance;
	float pickupWeight;
	float deliveryWeight;
	float earthWeight;
	float travelHours;
	float travelDays;
	float travelYears;
};

planet planetArray[8];



int _tmain(int argc, _TCHAR* argv[])
{
	ifstream inputFile("planets.txt");
	for(int i = MERCURY; i <= NEPTUNE; i++){ 
	inputFile>>planetArray[i].name;
	inputFile>>planetArray[i].distance;
	inputFile>>planetArray[i].surfaceGravity;
	}

	for(int i = MERCURY; i <= NEPTUNE; i++){
	cout<<planetArray[i].name<<" ";
	cout<<planetArray[i].distance<<" ";
	cout<<planetArray[i].surfaceGravity<<" "<<endl;
	}


	ofstream outputFile("Delivery_Report.txt");

	system("pause");
	return 0;
}

