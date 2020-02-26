#pragma once
#include "Fahrausnahme.h"

class Streckenende : public Fahrausnahme {
public:
	Streckenende(Fahrzeug& f, Weg& w);
	~Streckenende();
	void vBearbeiten();
};