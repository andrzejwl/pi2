#pragma once
#include "Simulationsobjekt.h"
#include <iostream>
#include <string>
#include <list>
#include "vertagt_liste.h"
using namespace std;

class Kreuzung;
class Verhalten;

enum class Tempolimit { Unbegrenzt, Hundert, Fuenfzig };

class Fahrzeug; //deklariert, um #include "Fahrzeug.h" in der Header Datei zu vermeiden (Rekursion)

class Weg : public Simulationsobjekt {
public:
	Weg();
	Weg(string, double, Tempolimit, shared_ptr<Kreuzung>, bool dUeberholverbot = true);
	~Weg();
	double dGetTempoLimit();
	void vSimulieren();
	void vAusgeben(ostream&) const;
	static void vKopf();
	void vAnnahme(unique_ptr<Fahrzeug>);
	void vAnnahme(unique_ptr<Fahrzeug>, double);
	void vFahrzeugAusgeben();
	string sGetName() const;
	void vFahrzeugeZeichnen();
	double dGetLaenge() const;
	unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug&);
	Weg& getRueckweg();
	Kreuzung& getZielkreuzung();
	void setRueckweg(shared_ptr<Weg>);
	void setZielkreuzung(shared_ptr<Kreuzung>);
	int iGetId();

protected:
	double p_dLaenge;
	double p_dSchranke;
	bool p_bUeberholverbot;
	vertagt::VListe<unique_ptr<Fahrzeug>> p_pFahrzeuge;
	Tempolimit p_eTempolimit;
	weak_ptr<Kreuzung> p_pZielKreuzung;
	weak_ptr<Weg> p_pRueckweg;

	friend class Verhalten;
	friend class Parken;
	friend class Fahren;
	friend class Kreuzung;
};

ostream& operator<<(ostream&, const Weg&);