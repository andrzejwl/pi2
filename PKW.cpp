#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <iomanip>
#include <limits>
#include <cmath>
#include "PKW.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include "Verhalten.h"
#include "Losfahren.h"
#include "Streckenende.h"
#include "SimuClient.h"

using namespace std;

extern double dGlobaleZeit;

PKW::PKW(string sName, double dMaxGesch, double dVerbrauch, double dTankvolumen) : Fahrzeug(sName, dMaxGesch),
p_dVerbrauch(dVerbrauch), p_dTankvolumen(dTankvolumen), p_dTankinhalt(dTankvolumen / 2)
{
	cout << "PKW erstellt\n";
}

PKW::PKW() : Fahrzeug::Fahrzeug(), p_dVerbrauch(10), p_dTankvolumen(50), p_dTankinhalt(25) {
}

double PKW::dTanken(double dMenge) {
	double dVorTanken = p_dTankinhalt;

	if (dMenge < numeric_limits<double>::infinity()) {
		if (dVorTanken + dMenge < p_dTankvolumen)
			p_dTankinhalt += dMenge;
		else 
			p_dTankinhalt = p_dTankvolumen;
	}
	else 
		p_dTankinhalt = p_dTankvolumen;

	double tmp = p_dTankinhalt - dVorTanken;

	return tmp;
}


void PKW::vZeichnen(const Weg& w) const {
	double dPos = p_dAbschnittStrecke / w.dGetLaenge();

	if (dPos < 0) dPos = 0;
	if (dPos > 1) dPos = 1;

	//cout << p_dAbschnittStrecke << " ID: " << p_sName << dPos << endl;

	bZeichnePKW(p_sName, w.sGetName(), dPos, p_dGeschwindigkeit, p_dTankinhalt);
}


void PKW::vSimulieren() {
	if (p_dZeit == dGlobaleZeit) {
		//cout << "Fahrzeug " << p_iID << " wurde schon in diesem Zeitpunkt simuliert" << endl;  //auskommentiert, weil momentan unnötig
	}
	// Funktionsaufruf nur um zu überprüfen, ob es ein Fehler gibt (Streckenende oder Losfahren)\/
	else if (bDoubleVergleich(p_dTankinhalt, 0.0) or p_pVerhalten->dStrecke(*this, p_dZeit) == 0.0)  //wenn Tank leer -> nur die Zeit aktualisiert 
		p_dZeit = dGlobaleZeit;
	else {
		double dStrecke = p_pVerhalten->dStrecke(*this, p_dZeit);

		
		p_dTankinhalt -= (dStrecke / 100) * p_dVerbrauch;
		if (p_dTankinhalt < 0)
			p_dTankinhalt = 0;

		p_dAbschnittStrecke += dStrecke;
		p_dGesamtStrecke += dStrecke;
		p_dGesamtZeit += dStrecke / dGeschwindigkeit();
		p_dZeit = dGlobaleZeit;
	}
}

void PKW::vAusgeben(ostream& o) const {
	Fahrzeug::vAusgeben(o);
	o << setw(20) << p_dGesamtStrecke * p_dVerbrauch / 100 << setw(15) << p_dTankinhalt;
}

istream& PKW::istreamEingabe(istream& i) {
	Fahrzeug::istreamEingabe(i) >> p_dVerbrauch >> p_dTankvolumen;
	p_dTankinhalt = p_dTankvolumen / 2;
	return i;
}


bool bDoubleVergleich(double dWertA, double dWertB, double dToleranz) {
	return fabs(dWertA - dWertB) < dToleranz;
}


ostream& operator<<(ostream& o, const PKW& p) {
	p.vAusgeben(o);
	return o;
};
