#pragma once
#include "Fahrrad.h"
#include "Fahrzeug.h"
#include "SimuClient.h"
#include "Losfahren.h"
#include "Streckenende.h"
#include "Verhalten.h"
#include "Weg.h"
#include <string>
using namespace std;

extern double dGlobaleZeit;

Fahrrad::Fahrrad() : Fahrzeug::Fahrzeug(), p_dUebrigeZeit(dGlobaleZeit) {
}

Fahrrad::Fahrrad(string sName, double dMaxGesch) : Fahrzeug(sName, dMaxGesch) {
	p_dUebrigeZeit = 0;  //diese Variable wird zum 3. Punkt von 7.3.3 benutzt
	cout << "Fahrrad erstellt\n";
}

void Fahrrad::vZeichnen(const Weg& w) const {
	double dPos = p_dAbschnittStrecke / w.dGetLaenge();

	if (dPos < 0) dPos = 0;
	if (dPos > 1) dPos = 1;
	
	bZeichneFahrrad(p_sName, w.sGetName(), dPos, p_dGeschwindigkeit);
}

void Fahrrad::vSimulieren() {
	if (p_dZeit == dGlobaleZeit) {
		//cout << "Fahrzeug " << p_iID << " wurde schon in diesem Zeitpunkt simuliert" << endl;
	}
	else {
		double dDeltaZeit = dGlobaleZeit - p_dZeit + p_dUebrigeZeit;
		p_dGesamtStrecke -= p_dGeschwindigkeit * p_dUebrigeZeit; //dekrementieren, um die gleiche Zeit nicht zweimal einzurechnen| wird später erklärt
		p_dAbschnittStrecke -= p_dGeschwindigkeit * p_dUebrigeZeit; //dekrementieren, um die gleiche Zeit nicht zweimal einzurechnen| wird später erklärt

		p_dGesamtZeit += dDeltaZeit - p_dUebrigeZeit; // übrige Zeit wurde schon in der vorigen Iteration eingerechnet

		double dZeitPro20 = 20 / p_dGeschwindigkeit; //wie lange dauert es, mit gegenwärtiger Geschwindigkeit 20km zu erreichen

		while (dZeitPro20 <= dDeltaZeit) {
			if (0.9 * p_dGeschwindigkeit < 12) {
				break;
			}
			else {
				p_dGeschwindigkeit *= 0.9;
				dDeltaZeit -= dZeitPro20;
				p_dGesamtStrecke += 20;
				p_dAbschnittStrecke += 20;

				dZeitPro20 = 20 / p_dGeschwindigkeit;
			}
		}
		if (dDeltaZeit > 0) {
			p_dUebrigeZeit = dDeltaZeit; //die übrige Zeit wird im nächsten möglichen Geschwindigkeitupdate verwendet 
											//(wenn der Rad schon für eine Weile mit der aktualisierten Geschwindigkeit gefahren ist, aber es fehlt noch bis der nächsten Dekrementierung 
											//d.h. er ist mit der neuen Geschwindigkeit noch nicht 20km gefahren)
			p_dGesamtStrecke += p_dGeschwindigkeit * p_dUebrigeZeit; // wird eingerechnet, sodass vAusgeben aktuelle Werten zeigt
			p_dAbschnittStrecke += p_dGeschwindigkeit * p_dUebrigeZeit; // wird eingerechnet, sodass vAusgeben aktuelle Werten zeigt
			p_dZeit += dDeltaZeit;
		}
		p_dZeit = dGlobaleZeit;
		p_pVerhalten->dStrecke(*this, p_dZeit);
	}
	
}

//istream& Fahrrad::istreamEingabe(istream& i) {
//	Fahrzeug::istreamEingabe(i);
//	return i;
//}
