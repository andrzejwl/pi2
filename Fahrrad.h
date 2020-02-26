#pragma once
#include <string>
#include "Fahrzeug.h"

class Fahrrad : public Fahrzeug {
public:
	//void vGeschwindigkeit();
	Fahrrad();
	Fahrrad(string, double);
	void vSimulieren() override;
	void vZeichnen(const Weg& w) const;
	//istream& istreamEingabe(istream& i);
private:
	double p_dUebrigeZeit; //letzter Wert der Gesamtstrecke, wann die p_dGeschwindigkeit dekrementiert wurde
};