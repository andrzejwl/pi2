#include "Fahren.h"
#include "Fahrzeug.h"
#include "Weg.h"
//#include <string>
//#include <iostream>
//using namespace std;

extern double dGlobaleZeit;

Fahren::Fahren(Weg& w) : Verhalten::Verhalten(w) {
}

Fahren::~Fahren() {
}