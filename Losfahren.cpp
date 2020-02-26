#include "Losfahren.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include <iostream>
using namespace std;

Losfahren::Losfahren(Fahrzeug& f, Weg& w) : Fahrausnahme::Fahrausnahme(f, w) {
}

Losfahren::~Losfahren() {
}

void Losfahren::vBearbeiten() {
	cout << "Art der Ausnahme: Losfahren" << endl << "Fahrzeug ID: " << p_Fahrzeug.iGetId() << endl;
}