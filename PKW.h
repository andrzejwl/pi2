#pragma once
#include "Fahrzeug.h"
#include <string>
#define TOLERANZ 1e-6
using namespace std;

class Weg;

class PKW : public Fahrzeug {
public:
	PKW();
	PKW(string, double, double, double dTankVolumen = 55);
	double dTanken(double dMenge = numeric_limits<double>::infinity()) override;
	void vSimulieren() override;
	void vAusgeben(ostream&) const override;
	void vZeichnen(const Weg&) const;
	istream& istreamEingabe(istream&);

private:
	double p_dVerbrauch; // liter/100km
	double p_dTankvolumen; //liter
	double p_dTankinhalt; //liter
};

ostream& operator<<(ostream&, const PKW&);

bool bDoubleVergleich(double, double, double dToleranz = TOLERANZ);
