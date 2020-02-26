#include "Streckenende.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Kreuzung.h"
#include <iostream>
using namespace std;

extern double dGlobaleZeit;

Streckenende::Streckenende(Fahrzeug& f, Weg& w) : Fahrausnahme::Fahrausnahme(f, w) {
}

Streckenende::~Streckenende() {
}

void Streckenende::vBearbeiten() {
	auto f_ptr = p_Weg.pAbgabe(p_Fahrzeug);
	Kreuzung& ZielKreuzung = p_Weg.getZielkreuzung();
	ZielKreuzung.vTanken(*f_ptr);
	//p_Weg.getZielkreuzung().vTanken(*f_ptr);
	Weg& NeuerWeg = ZielKreuzung.pZufaelligerWeg(p_Weg);

	f_ptr->vNeueStrecke(NeuerWeg);
	const string FahrzeugName = f_ptr->sGetName();
	const string KreuzungName = p_Weg.getZielkreuzung().sGetName();
	const int FahrzeugID = f_ptr->iGetId();
	NeuerWeg.vAnnahme(move(f_ptr));

	cout << "Art der Ausnahme: Streckenende" << endl << "Fahrzeug ID: " << FahrzeugID << endl;
	cout << "ZEIT       :" << dGlobaleZeit << endl;
	cout << "KREUZUNG   :" << ZielKreuzung.sGetName() << " INHALT:  " << ZielKreuzung.dGetInhalt() << endl;
	cout << "WECHSEL    :" << p_Weg.sGetName() << " -> " << NeuerWeg.sGetName() << endl;
	cout << "FAHRZEUG   :" << FahrzeugID << endl << endl;
}