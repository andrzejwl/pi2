#pragma once
#include <string>
#include "Simulationsobjekt.h"
using namespace std;

class Weg;
class Verhalten;

class Fahrzeug : public Simulationsobjekt {
public:
	Fahrzeug();
	Fahrzeug(string);
	Fahrzeug(string, double);
	virtual ~Fahrzeug();
	int iGetId();
	static void vKopf();
	virtual void vSimulieren();
	virtual double dTanken(double dMenge = numeric_limits<double>::infinity());
	virtual void vAusgeben(ostream&) const;
	friend bool operator<(const Fahrzeug&, const Fahrzeug&);
	istream& istreamEingabe(istream&);

	Fahrzeug(const Fahrzeug&) = delete;
	//auf diese Weise hat der kopierte Fahrzeug ein anderes p_iID
	Fahrzeug& operator=(const Fahrzeug&);

	void vNeueStrecke(Weg&);
	void vNeueStrecke(Weg&, double);
	string sGetName(); //sodass Weg Zugriff zu den FahrzeugsNamen hat
	virtual void vZeichnen(const Weg&) const;
	double dGetPos();
	double dGeschwindigkeit();
	bool bGeparkt();

protected:
	double p_dMaxGeschwindigkeit;
	double p_dGesamtStrecke;
	double p_dGesamtZeit;
	double p_dGeschwindigkeit;
	double p_dAbschnittStrecke;
	bool p_bGeparkt;
	unique_ptr<Verhalten> p_pVerhalten;
	friend class Verhalten;
	friend class Parken;
	friend class Fahren;
	friend class Streckenende;
};

ostream& operator<<(ostream&, const Fahrzeug&);