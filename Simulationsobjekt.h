#pragma once
#include <string>
#include <iostream>
using namespace std;

class Simulationsobjekt {
protected:
	const int p_iID;
	static int p_iMaxID;
	string p_sName; //könnte const sein, aber istreamEingabe wurde hinzugefügt
	double p_dZeit;
public:
	Simulationsobjekt();
	Simulationsobjekt(string);
	~Simulationsobjekt();
	virtual void vAusgeben(ostream&) const;
	virtual void vSimulieren() = 0;
	virtual istream& istreamEingabe(istream&);
};

istream& operator >> (istream&, Simulationsobjekt&);