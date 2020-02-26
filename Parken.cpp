#include "Parken.h"
#include "Losfahren.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

extern double dGlobaleZeit;

Parken::Parken(Weg& w, double dStartZeitPunkt) : Verhalten::Verhalten(w), p_dStartZeitPunkt(dStartZeitPunkt) {
}

Parken::~Parken() {
}

double Parken::dStrecke(Fahrzeug& f, double zeit) {
	if (dGlobaleZeit < p_dStartZeitPunkt)
		return 0.0;
	else
		throw Losfahren(f, *p_pWeg);
}