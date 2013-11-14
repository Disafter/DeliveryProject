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
	char cargoType[51];
	int pickupPlanet;
	int deliveryPlanet;
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
	formatInput();
	//checkDeliveryPossibility();
	outputToFile();


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

	const int INPUT_SIZE = 50;
	char input[INPUT_SIZE];

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
	}


	while(shipdata.pickupWeight<=0){
		cout<<"What is the weight of the cargo in pick-up planet pounds? "<<endl;
		cin.getline(input, INPUT_SIZE);
		shipdata.pickupWeight = atof(input);
	}
	while(shipdata.speed<=0){
		cout<<"At what speed will your shuttle travel? "<<endl;
		cin.getline(input, INPUT_SIZE);
		shipdata.speed = atof(input);
	}

	cout<<setprecision(3)<<fixed<<showpoint<<"Here is your input."<<endl; //take this out when finished
	cout<<shipdata.cargoType<<endl;
	cout<<shipdata.pickupPlanet<<endl;
	cout<<shipdata.deliveryPlanet<<endl;
	cout<<shipdata.pickupWeight<<endl;
	cout<<shipdata.speed<<endl;



	return shipdata;
}


/*example output of planet file after successful input

for(int i = MERCURY; i <= NEPTUNE; i++){
cout<<planetArray[i].name<<" ";
cout<<planetArray[i].distance<<" ";
cout<<planetArray[i].surfaceGravity<<" "<<endl;
}

*/

void formatInput(){
	myShuttle.earthWeight = myShuttle.pickupWeight * (1 / planetArray[myShuttle.pickupPlanet - 1].surfaceGravity);
	myShuttle.deliveryWeight = myShuttle.earthWeight * planetArray[myShuttle.deliveryPlanet - 1].surfaceGravity;

	cout<<"The earth weight is "<<myShuttle.earthWeight<<" pounds."<<endl;
	if(myShuttle.earthWeight >= 20000){
		cout<<"The cargo load is too heavy!"<<endl; 
		//RETURN TO BEGINNING OF DATA ENTRY OR REPROMPT WEIGHT ENTRY, COULD DO THIS CHECK AFTER ALL INPUT, AND THEN REPROMPT THE WEIGHT ENTRY IF NECESSARY
	}
	cout<<"The weight on the delivery planet will be "<<myShuttle.deliveryWeight<<" pounds."<<endl;



	myShuttle.totalTravelDistance = abs(planetArray[myShuttle.pickupPlanet - 1].distance - planetArray[myShuttle.deliveryPlanet - 1].distance);
	cout<<"The total travel distance is "<<myShuttle.totalTravelDistance<<" million miles."<<endl;

	myShuttle.travelHours =  (myShuttle.totalTravelDistance * 1000000) / myShuttle.speed;
	cout<<"The total travel time in hours is "<<myShuttle.travelHours<<"."<<endl;
	myShuttle.travelDays = myShuttle.travelHours / 24;
	cout<<"The total travel time in days is "<<myShuttle.travelDays<<"."<<endl;
	myShuttle.travelYears = myShuttle.travelDays / 365;
	cout<<"The total travel time in years is "<<myShuttle.travelYears<<"."<<endl;
}


void outputToFile(){
	ofstream outputFile;
	outputFile.open("Delivery_Report.txt"
		, ios::app);
	
	if(outputFile.fail()){
		outputFile.open("Delivery_Report.txt");
	}

	outputFile.seekp(0L, ios::end);

	outputFile << endl << endl;

	outputFile<<"You are transporting "<<myShuttle.cargoType<<"."<<endl;

	outputFile<<fixed<<setprecision(3)<<"The earth weight is "<<myShuttle.earthWeight<<" pounds."<<endl;
	
	outputFile<<"The weight on the delivery planet will be "<<myShuttle.deliveryWeight<<" pounds."<<endl;

	outputFile<<"The total travel distance is "<<myShuttle.totalTravelDistance<<" million miles."<<endl;

	outputFile<<"The total travel time in hours is "<<myShuttle.travelHours<<"."<<endl;

	outputFile<<"The total travel time in days is "<<myShuttle.travelDays<<"."<<endl;

	outputFile<<"The total travel time in years is "<<myShuttle.travelYears<<"."<<endl;

	outputFile.close();
}