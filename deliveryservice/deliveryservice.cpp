// deliveryservice.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <cmath>
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
	char cargoType[101];
	int pickupPlanet;
	int deliveryPlanet;
	long speed;
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

bool continueRunning = true;

const int INPUT_SIZE = 101;
char input[INPUT_SIZE];
char answer[INPUT_SIZE];


void getPlanetData();
shuttle getUserInput();
void formatInput();
void outputToFile();




int _tmain(int argc, _TCHAR* argv[])
{


	getPlanetData();

	while(continueRunning){
		myShuttle = getUserInput();
		formatInput();
		outputToFile();

		answer[0] = ' ';
		while(toupper(answer[0]) != 'Y' && toupper(answer[0]) != 'N'){
			cout<<"Would you like to continue entering shipping records? ";
			cin.getline(input, INPUT_SIZE);
			answer[0] = input[0];
			

			if(toupper(answer[0]) == 'N'){
				continueRunning = false;
			}
			else if(toupper(answer[0]) == 'Y'){
				continueRunning = true;
			}
		}
	}


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
	shipdata.pickupPlanet = 0;
	shipdata.deliveryPlanet = 0;
	shipdata.speed = 0;
	shipdata.pickupWeight = 0;


	cout<<"What is the Cargo Type? "<<endl;
	cin.getline(shipdata.cargoType, INPUT_SIZE);

	while(shipdata.pickupPlanet <= 0 || shipdata.pickupPlanet > 8){
		cout<<"What is the pick-up planet? "<<endl;
		cout<<"Enter the number of the desired planet:"<<endl;
		cout<<"1 - Mercury"<<endl;
		cout<<"2 - Venus"<<endl;
		cout<<"3 - Earth"<<endl;
		cout<<"4 - Mars"<<endl;
		cout<<"5 - Jupiter"<<endl;
		cout<<"6 - Saturn"<<endl;
		cout<<"7 - Uranus"<<endl;
		cout<<"8 - Neptune"<<endl;
		cin.getline(input, INPUT_SIZE);
		shipdata.pickupPlanet = atoi(input);
	}
	while(shipdata.deliveryPlanet <= 0 || shipdata.deliveryPlanet > 8){
		cout<<"What is the delivery planet? "<<endl;
		cout<<"Enter the number of the desired planet:"<<endl;
		cout<<"1 - Mercury"<<endl;
		cout<<"2 - Venus"<<endl;
		cout<<"3 - Earth"<<endl;
		cout<<"4 - Mars"<<endl;
		cout<<"5 - Jupiter"<<endl;
		cout<<"6 - Saturn"<<endl;
		cout<<"7 - Uranus"<<endl;
		cout<<"8 - Neptune"<<endl;
		cin.getline(input, INPUT_SIZE);
		shipdata.deliveryPlanet = atoi(input);
		if(shipdata.deliveryPlanet == shipdata.pickupPlanet){
			shipdata.deliveryPlanet = 0;
			cout<<endl<<"**You cannot deliver to the same planet you picked up from.**"<<endl<<endl;
		}
	}


	while(shipdata.pickupWeight<=0){
		cout<<"What is the weight of the cargo in pick-up planet pounds? "<<endl;
		cin.getline(input, INPUT_SIZE);
		shipdata.pickupWeight = atof(input);
		if(shipdata.pickupWeight > 20000){
			shipdata.pickupWeight = 0;
			cout<<endl<<"**Your ship cannot carry more than 20,000 pounds in Earth weight**!"<<endl<<endl;
		}
	}


	while(shipdata.speed<=0){
		cout<<"At what speed will your shuttle travel in miles per hour? "<<endl;
		cin.getline(input, INPUT_SIZE);
		shipdata.speed = atol(input);
		if(shipdata.speed > 670616629){
			shipdata.speed = 0;
			cout<<endl<<"**No ship can travel faster than light! (670616629 mph)**"<<endl<<endl;
		}
	}

	return shipdata;
}


void formatInput(){
	myShuttle.earthWeight = myShuttle.pickupWeight * (1 / planetArray[myShuttle.pickupPlanet - 1].surfaceGravity);
	myShuttle.deliveryWeight = myShuttle.earthWeight * planetArray[myShuttle.deliveryPlanet - 1].surfaceGravity;
	myShuttle.totalTravelDistance = abs(planetArray[myShuttle.pickupPlanet - 1].distance - planetArray[myShuttle.deliveryPlanet - 1].distance);
	myShuttle.travelHours =  (myShuttle.totalTravelDistance * 1000000) / myShuttle.speed;
	myShuttle.travelDays = myShuttle.travelHours / 24;
	myShuttle.travelYears = myShuttle.travelDays / 365;
}


void outputToFile(){
	cout<<endl<<"Now outputting shipment data to Delivery_Report.txt..."<<endl<<endl;
	ofstream outputFile;
	outputFile.open("Delivery_Report.txt", ios::app);

	if(outputFile.fail()){
		outputFile.open("Delivery_Report.txt");
	}

	outputFile.seekp(0L, ios::end);

	outputFile << endl << endl;

	outputFile<<"You delivered "<<myShuttle.cargoType<<"."<<endl;

	outputFile<<fixed<<setprecision(3)<<"The weight on the pick-up planet is "<<myShuttle.pickupWeight<<" pounds."<<endl;
	outputFile<<"The earth weight is "<<myShuttle.earthWeight<<" pounds."<<endl;
	outputFile<<"The weight on the delivery planet is "<<myShuttle.deliveryWeight<<" pounds."<<endl;

	outputFile<<"The total travel distance is "<<myShuttle.totalTravelDistance<<" million miles."<<endl;

	outputFile<<"The total travel time in hours is "<<myShuttle.travelHours<<"."<<endl;
	outputFile<<"The total travel time in days is "<<myShuttle.travelDays<<"."<<endl;
	outputFile<<"The total travel time in years is "<<myShuttle.travelYears<<"."<<endl;

	outputFile.close();
}