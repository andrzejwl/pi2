#pragma once
#include <map>
#include <iostream>
#include <string>
#include <fstream>
using namespace std; 

class Kreuzung;

class Simulation {
public:
	void vSimulieren(double, double);
	void vEinlesen(istream&, bool bMitGrafik = false);
	map<string, shared_ptr<Kreuzung>> mKreuzungen;
};