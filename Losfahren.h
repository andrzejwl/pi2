#pragma once
#include "Fahrausnahme.h"

class Losfahren : public Fahrausnahme {
public:
	Losfahren(Fahrzeug& f, Weg& w);
	~Losfahren();
	void vBearbeiten();
};