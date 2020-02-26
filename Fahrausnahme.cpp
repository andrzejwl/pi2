#include "Fahrausnahme.h"
#include "Fahrzeug.h"
#include "Weg.h"


Fahrausnahme::Fahrausnahme(Fahrzeug& f, Weg& w) : p_Fahrzeug(f), p_Weg(w) {
}

Fahrausnahme::~Fahrausnahme(){
}