#pragma once
#include "Verhalten.h"

class Parken : public Verhalten {
public:
	Parken(Weg&, double);
	~Parken();
	double dStrecke(Fahrzeug&, double);
private:
	double p_dStartZeitPunkt;
};