#pragma once
#include "Simulationsobjekt.h"
#include "Weg.h"
#include <list>
#include <memory>
using namespace std;

class Kreuzung : public Simulationsobjekt {
private:

	list<shared_ptr<Weg>> p_pWege; //wegführende Wege
	double p_dTankstelle;
public:
	Kreuzung();
	Kreuzung(string);
	~Kreuzung();
	void vSimulieren();
	void vTanken(Fahrzeug&);
	void vVerbinde(string, string, double, shared_ptr<Kreuzung>, shared_ptr<Kreuzung>, Tempolimit, bool);
	void vAnnahme(unique_ptr<Fahrzeug>, double);
	Weg& pZufaelligerWeg(Weg&);
	string sGetName();
	double dGetInhalt();
	virtual void vAusgeben(ostream&) const;
	istream& istreamEingabe(istream&);
};

ostream& operator<<(ostream&, const Kreuzung&);