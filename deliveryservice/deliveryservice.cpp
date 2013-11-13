// deliveryservice.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
using std::ifstream;
using namespace std;

enum planetOrder{MERCURY, VENUS, EARTH, MARS, JUPITER, SATURN, URANUS, NEPTUNE};

struct planet
{
	char name[8];
	float distance;
	float surfaceGravity;
};

struct shuttle
{
	char cargoType[51];
	char pickupPlanet[51];
	char deliveryPlanet[51];
	float speed;
	float pickupWeight;
	float deliveryWeight;
	float earthWeight;
	float totalTravelDistance;
	float travelHours;
	float travelDays;
	float travelYears;
};

planet planetArray[8];
shuttle myShuttle;

int menuChoice;

//function prototypes;
void getPlanetData();
shuttle getUserInput();
void formatInput();
void checkDeliveryPossibility();
void outputToFile();




int _tmain(int argc, _TCHAR* argv[])
{
	

	getPlanetData();
	myShuttle = getUserInput();
	//formatInput();
	//checkDeliveryPossibility();
	//outputToFile();


	system("pause");
	return 0;
}

void getPlanetData(){
	ifstream inputFile("planets.txt");
	for(int i = MERCURY; i <= NEPTUNE; i++){ 
	inputFile>>planetArray[i].name;
	inputFile>>planetArray[i].distance;
	inputFile>>planetArray[i].surfaceGravity;
	}
}

shuttle getUserInput(){
	
	shuttle shipdata;
	
	const int INPUT_SIZE = 50;
	char input[INPUT_SIZE];

	cout<<"What is the Cargo Type? "<<endl;
	cin.getline(shipdata.cargoType, INPUT_SIZE);
	cout<<"What is the pick-up planet? "<<endl;
	getline(cin, inputValidator);
	cout<<"What is the delivery planet? "<<endl;
	getline(cin, shipdata.deliveryPlanet);
	cout<<"What is the weight of the cargo in pick-up planet pounds? "<<endl;
	cin>>shipdata.pickupWeight;
	cout<<"At what speed will your shuttle travel? "<<endl;
	cin>>shipdata.speed;
	return shipdata;
}


/*example output of planet file after successful input

for(int i = MERCURY; i <= NEPTUNE; i++){
	cout<<planetArray[i].name<<" ";
	cout<<planetArray[i].distance<<" ";
	cout<<planetArray[i].surfaceGravity<<" "<<endl;
	}

*/

void outputToFile(){
	ofstream outputFile("Delivery_Report.txt");
}