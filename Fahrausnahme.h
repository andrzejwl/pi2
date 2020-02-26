#pragma once
#include <exception>
#include <string>
using namespace std;

class Fahrzeug;
class Weg;

class Fahrausnahme : public exception {
public:
	Fahrausnahme(Fahrzeug&, Weg&);
	virtual ~Fahrausnahme();
	virtual void vBearbeiten() = 0;
protected:
	Fahrzeug& p_Fahrzeug;
	Weg& p_Weg;
};