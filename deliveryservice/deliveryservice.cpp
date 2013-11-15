// deliveryservice.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <cmath>
using std::ifstream;  //prevents unnecessary errors from occurring when using various file input syntaxes
using namespace std;

enum planetOrder{MERCURY, VENUS, EARTH, MARS, JUPITER, SATURN, URANUS, NEPTUNE}; //enumerated data type used in file input loop as user convenience in case planets are added or removed from our solar system

struct planet  //the declaration of the planet structure. an array of these objects is read from the planets.txt file when the program is booted up
{
	char name[8]; //the size of the longest planet name plus one for the null terminator. should be changed if planets with longer names are added to the solar system
	float distance; //the average distance from this planet to the sun
	float surfaceGravity;
};

struct shuttle
{
	char cargoType[101]; //the name of whatever you are delivering. some deliverys could have long descriptions, so space for 100 characters is allotted.
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

bool continueRunning = true; //this is the boolean for whether the user wants to record more deliveries

const int INPUT_SIZE = 101;  //these three variables are declared globally so that multiple functions can use them
char input[INPUT_SIZE]; 
char answer[INPUT_SIZE];


void getPlanetData(); //this function gets the information about each planet from an external file, planets.txt
shuttle getUserInput(); //this function requests input from the user, and returns it as a shuttle object
void formatInput(); //this function handles the conversions of time and weight
void outputToFile(); //this function outputs the shipment to the file log, preserving past shipments




int _tmain(int argc, _TCHAR* argv[])
{


	getPlanetData();

	while(continueRunning){
		myShuttle = getUserInput();
		formatInput();
		outputToFile();

		answer[0] = ' ';
		while(toupper(answer[0]) != 'Y' && toupper(answer[0]) != 'N'){ //checks to see if the user wants to enter more shipments
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

void getPlanetData(){ //takes in all of the data from the file and stores it in an array of planet structures
	ifstream inputFile("planets.txt");
	for(int i = MERCURY; i <= NEPTUNE; i++){ //runs the loop once for each planet
		inputFile>>planetArray[i].name;
		inputFile>>planetArray[i].distance;
		inputFile>>planetArray[i].surfaceGravity;
	}
}

shuttle getUserInput(){

	shuttle shipdata; //this is the local version of the shuttle structure that gets returned to the global version after user input is received
	shipdata.pickupPlanet = 0; //these 4 lines clear the input variables so that they can be revalidated if multiple shipments are entered during a single run of the program
	shipdata.deliveryPlanet = 0;
	shipdata.speed = 0;
	shipdata.pickupWeight = 0;


	cout<<"What type of cargo are you delivering? "<<endl; 
	cin.getline(shipdata.cargoType, INPUT_SIZE); //the cargo input can be any 100 characters.

	while(shipdata.pickupPlanet <= 0 || shipdata.pickupPlanet > 8){
		cout<<"Which planet will you pick-up from? "<<endl;
		cout<<"Enter the number of the desired planet:"<<endl; //the menu system was implemented, in order to enhance user experience and prevent errors.
		cout<<"1 - Mercury"<<endl;
		cout<<"2 - Venus"<<endl;
		cout<<"3 - Earth"<<endl;
		cout<<"4 - Mars"<<endl;
		cout<<"5 - Jupiter"<<endl;
		cout<<"6 - Saturn"<<endl;
		cout<<"7 - Uranus"<<endl;
		cout<<"8 - Neptune"<<endl;
		cin.getline(input, INPUT_SIZE);
		shipdata.pickupPlanet = atoi(input); //converts the user entered string to an integer.
	}
	while(shipdata.deliveryPlanet <= 0 || shipdata.deliveryPlanet > 8){
		cout<<"Where will the shipment be delivered to? "<<endl;
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
			cout<<endl<<"**You cannot deliver to the same planet you picked up from.**"<<endl<<endl; //confirms that the two selected planets are not the same
		}
	}


	while(shipdata.pickupWeight<=0){
		cout<<"What is the weight of the cargo in pick-up planet pounds? "<<endl;
		cin.getline(input, INPUT_SIZE);
		shipdata.pickupWeight = atof(input);
		if((shipdata.pickupWeight * (1 / planetArray[shipdata.pickupPlanet - 1].surfaceGravity))> 20000){ //the ship cannot hold more than 10 earth tons. if the input weight exceeds this limit, the input will be reprompted
			shipdata.pickupWeight = 0;
			cout<<endl<<"**Your ship cannot carry more than 20,000 pounds in Earth weight**!"<<endl<<endl;
		}
	}


	while(shipdata.speed<=0){
		cout<<"At what speed will your shuttle travel in miles per hour? "<<endl;
		cin.getline(input, INPUT_SIZE);
		shipdata.speed = atol(input); //converts string input to a long
		if(shipdata.speed > 670616629){ //the limit for ship speed is the speed of light
			shipdata.speed = 0;
			cout<<endl<<"**No ship can travel faster than light! (670616629 mph)**"<<endl<<endl;
		}
	}

	return shipdata; //returns all input as a shuttle structure
}


void formatInput(){
	myShuttle.earthWeight = myShuttle.pickupWeight * (1 / planetArray[myShuttle.pickupPlanet - 1].surfaceGravity);
	myShuttle.deliveryWeight = myShuttle.earthWeight * planetArray[myShuttle.deliveryPlanet - 1].surfaceGravity;
	myShuttle.totalTravelDistance = abs(planetArray[myShuttle.pickupPlanet - 1].distance - planetArray[myShuttle.deliveryPlanet - 1].distance);
	myShuttle.travelHours =  (myShuttle.totalTravelDistance * 1000000) / myShuttle.speed; //travel distance is multiplied by 1 million, because the file input for distance is in millions of miles
	myShuttle.travelDays = myShuttle.travelHours / 24;
	myShuttle.travelYears = myShuttle.travelDays / 365;
}


void outputToFile(){
	cout<<endl<<"Now outputting shipment data to Delivery_Report.txt..."<<endl<<endl; //a message so the user knows the program is attempting to output the data to the file
	ofstream outputFile;
	outputFile.open("Delivery_Report.txt", ios::app);

	if(outputFile.fail()){
		outputFile.open("Delivery_Report.txt");
	}

	outputFile.seekp(0L, ios::end); //moves the write position of the file stream operator the end of the file

	outputFile << endl << endl;

	outputFile<<"You delivered "<<myShuttle.cargoType<<"."<<endl; //these next 8 lines write the data to the file

	outputFile<<fixed<<setprecision(3)<<"The weight on the pick-up planet ("<<planetArray[myShuttle.pickupPlanet-1].name<<") is "<<myShuttle.pickupWeight<<" pounds."<<endl;
	outputFile<<"The earth weight is "<<myShuttle.earthWeight<<" pounds."<<endl;
	outputFile<<"The weight on the delivery planet("<<planetArray[myShuttle.deliveryPlanet-1].name<<") is "<<myShuttle.deliveryWeight<<" pounds."<<endl;

	outputFile<<"The total travel distance is "<<myShuttle.totalTravelDistance<<" million miles."<<endl;

	outputFile<<"The total travel time in hours is "<<myShuttle.travelHours<<"."<<endl;
	outputFile<<"The total travel time in days is "<<myShuttle.travelDays<<"."<<endl;
	outputFile<<"The total travel time in years is "<<myShuttle.travelYears<<"."<<endl;

	outputFile.close(); //closes the file. the file will open, write, and close each time the shipment cycle is run
}