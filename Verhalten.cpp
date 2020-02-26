#include "Verhalten.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include "PKW.h" //bdoublevergleich
#include "Streckenende.h"
#include <string>
using namespace std;

extern double dGlobaleZeit;

Verhalten::Verhalten(Weg& w) : p_pWeg(&w) {
}

Verhalten::~Verhalten() {
}

//wie weit kann noch ein Fahrzeug durch den aktuellen Weg fahren
double Verhalten::dStrecke(Fahrzeug& f, double zeit) {
	if (p_pWeg->p_bUeberholverbot) {

		if (bDoubleVergleich(f.dGetPos(), p_pWeg->dGetLaenge()))
			throw Streckenende(f, *p_pWeg);

		if (bDoubleVergleich(p_pWeg->p_dLaenge, f.p_dAbschnittStrecke) or f.p_dAbschnittStrecke > p_pWeg->p_dLaenge)
			throw Streckenende(f, *p_pWeg);
		

		double dSdelta = (dGlobaleZeit - zeit) * f.dGeschwindigkeit();

		if (dSdelta < p_pWeg->p_dSchranke - f.p_dAbschnittStrecke) {
			return dSdelta;
		}
		return p_pWeg->p_dSchranke - f.p_dAbschnittStrecke;
	}
	else {
		double dSdelta = (dGlobaleZeit - zeit) * f.dGeschwindigkeit();

		if (bDoubleVergleich(p_pWeg->p_dLaenge, f.p_dAbschnittStrecke) or f.p_dAbschnittStrecke > p_pWeg->p_dLaenge)
			throw Streckenende(f, *p_pWeg);

		if (dSdelta < p_pWeg->p_dLaenge - f.p_dAbschnittStrecke) {
			return dSdelta;
		}

		return p_pWeg->p_dLaenge - f.p_dAbschnittStrecke;
	}
}

double Verhalten::dGeschwindigkeitslimit() {
	return p_pWeg->dGetTempoLimit();
}