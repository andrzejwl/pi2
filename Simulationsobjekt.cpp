#include "Simulationsobjekt.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

double dGlobaleZeit = 0.0;

int Simulationsobjekt::p_iMaxID = 0;

Simulationsobjekt::Simulationsobjekt(): p_iID(p_iMaxID), p_sName(""), p_dZeit(dGlobaleZeit) {
	p_iMaxID++;
	cout << "Neues Simulationsobjekt "<< p_iID << " wurde erstellt" << endl;
}

Simulationsobjekt::Simulationsobjekt(string sName): p_iID(p_iMaxID), p_sName(sName), p_dZeit(dGlobaleZeit) {
	p_iMaxID++;
	cout << "Neues Simulationsobjekt " << p_iID << ", " << p_sName << " wurde erstellt" << endl;
}

Simulationsobjekt::~Simulationsobjekt() {
	cout << "Simulationsobjekt " << p_iID << " wird geloescht" << endl;
}

void Simulationsobjekt::vAusgeben(ostream& o) const{
	o << setiosflags(ios::left) << setw(7) << p_iID << resetiosflags(ios::left) << setw(20) << p_sName;
}

istream& Simulationsobjekt::istreamEingabe(istream& i) {
	if (p_sName != "") {
		throw string("Das Simulationsobjekt wurde schon frueher initialisiert");
	}
	i >> p_sName;
}

istream& operator >> (istream& i, Simulationsobjekt& obj) {
	return obj.istreamEingabe(i);
}