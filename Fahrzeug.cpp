#pragma once
#include "Fahrzeug.h"
#include "Weg.h"
#include "Parken.h"
#include "Fahren.h"
#include "Losfahren.h"
#include "Streckenende.h"

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <iomanip>
#include <limits>
#include <cmath>
using namespace std;

extern double dGlobaleZeit;

Fahrzeug::Fahrzeug()
	: Simulationsobjekt::Simulationsobjekt(), p_dMaxGeschwindigkeit(40), p_dGeschwindigkeit(p_dMaxGeschwindigkeit), p_dGesamtStrecke(0), p_dGesamtZeit(0), p_dAbschnittStrecke(0), p_bGeparkt(false)
{
}

Fahrzeug::Fahrzeug(string sName)
	: Simulationsobjekt::Simulationsobjekt(sName), p_dMaxGeschwindigkeit(40), p_dGeschwindigkeit(p_dMaxGeschwindigkeit), p_dGesamtStrecke(0), p_dGesamtZeit(0), p_dAbschnittStrecke(0), p_bGeparkt(false)
{
}

Fahrzeug::Fahrzeug(string sName, double dMaxGesch)
	: Simulationsobjekt(sName), p_dMaxGeschwindigkeit(dMaxGesch > 0 ? dMaxGesch : 40), p_dGeschwindigkeit(p_dMaxGeschwindigkeit), p_dGesamtStrecke(0), p_dGesamtZeit(0), p_dAbschnittStrecke(0), p_bGeparkt(false)
{
}

Fahrzeug::~Fahrzeug() {
	cout << "'Fahrzeug' " << p_iID << " wird geloescht" << endl;
}

void Fahrzeug::vZeichnen(const Weg&) const {
};


istream& Fahrzeug::istreamEingabe(istream& i) {
	Simulationsobjekt::istreamEingabe(i) >> p_dMaxGeschwindigkeit;
	return i;
}

void Fahrzeug::vSimulieren() {
	if (p_dZeit == dGlobaleZeit) {
		//cout << "Fahrzeug " << p_iID << " wurde schon in diesem Zeitpunkt simuliert" << endl;
	}
	else {
		double dZeitDelta = dGlobaleZeit - p_dZeit;
		p_dGesamtStrecke += p_pVerhalten->dStrecke(*this, p_dZeit);
		p_dAbschnittStrecke += p_pVerhalten->dStrecke(*this, p_dZeit);//dZeitDelta * p_dGeschwindigkeit
		p_dGesamtZeit += dZeitDelta;
		p_dZeit = dGlobaleZeit;
		
		//cout << "Update: " << p_dGesamtStrecke << "km in " << p_dGesamtZeit << endl;
	}
}

double Fahrzeug::dGeschwindigkeit() {
	if (p_dGeschwindigkeit > p_pVerhalten->dGeschwindigkeitslimit())
		return p_pVerhalten->dGeschwindigkeitslimit();
	else
		return p_dGeschwindigkeit;
}

double Fahrzeug::dGetPos() {
	return p_dAbschnittStrecke;
}

string Fahrzeug::sGetName() {
	return p_sName;
}

int Fahrzeug::iGetId() {
	return p_iID;
}

void Fahrzeug::vKopf() {
	string linie(142, '-');
	cout << setw(7) << "ID" << setw(20) << "Name" << setw(30) << "Geschwindigkeit" << setw(30) << "MaxGeschwindigkeit" << setw(20) << "Gesamtstrecke" << setw(20) << "Gesamtverbrauch"
		<< setw(15) << "Tankinhalt" << endl << linie << endl;

}

void Fahrzeug::vAusgeben(ostream& o) const {
	Simulationsobjekt::vAusgeben(o);
	o << setw(30) << p_dGeschwindigkeit << setw(30) << p_dMaxGeschwindigkeit << setw(20) << p_dGesamtStrecke;
}

double Fahrzeug::dTanken(double dMenge) {
	return 0.0;
}

ostream& operator<<(ostream& o, const Fahrzeug& fz) {
	fz.vAusgeben(o);
	return o;
};

bool operator<(const Fahrzeug& l, const Fahrzeug& r) {
	return l.p_dGesamtStrecke < r.p_dGesamtStrecke;
}

Fahrzeug& Fahrzeug::operator=(const Fahrzeug& f) {
	p_dZeit = dGlobaleZeit;
	p_dGesamtStrecke = 0;
	const_cast<string&> (p_sName) = f.p_sName;
	const_cast<double&> (p_dMaxGeschwindigkeit) = f.p_dMaxGeschwindigkeit;
	p_dGeschwindigkeit = p_dMaxGeschwindigkeit;
	p_dGesamtZeit = 0;
	const_cast<int&>(p_iID) = p_iMaxID;
	p_iMaxID++;

	//Fahrzeug kopierterFahrzeug(f.p_sName, f.p_dMaxGeschwindigkeit);
	//return kopierterFahrzeug;
	return *this;
};

void Fahrzeug::vNeueStrecke(Weg& w) {
	p_dAbschnittStrecke = 0.0;
	p_pVerhalten = make_unique<Fahren>(w);
	p_bGeparkt = false;
}

void Fahrzeug::vNeueStrecke(Weg& w, double dStartZeit) {
	p_dAbschnittStrecke = 0.0;
	p_pVerhalten = make_unique<Parken>(w, dStartZeit);
	p_bGeparkt = true;
}

bool Fahrzeug::bGeparkt() {
	return p_bGeparkt;
}