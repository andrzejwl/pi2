#include "Kreuzung.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include <random>
#include <iterator>
#include <memory>
#include <iomanip>

using namespace std;
extern double dGlobaleZeit;

Kreuzung::Kreuzung() : Simulationsobjekt::Simulationsobjekt(), p_dTankstelle(1000) {
}

Kreuzung::Kreuzung(string sName) : Simulationsobjekt::Simulationsobjekt(sName), p_dTankstelle(1000) {
}

Kreuzung::~Kreuzung() {
}

void Kreuzung::vTanken(Fahrzeug& f) {
	if (p_dTankstelle > 0.0) {
		double dGetankt = f.dTanken();
		p_dTankstelle -= dGetankt;
		if (p_dTankstelle < 0.0)
			p_dTankstelle = 0.0;
	}
}

void Kreuzung::vSimulieren() {
	for (auto w : p_pWege) {
		w->vSimulieren();
	}
}

void Kreuzung::vAnnahme(unique_ptr<Fahrzeug> f, double dZeit) {
	vTanken(*f);
	auto AbgWeg = p_pWege.front();
	AbgWeg->vAnnahme(move(f), dZeit);
}

string Kreuzung::sGetName() {
	return p_sName;
}

double Kreuzung::dGetInhalt() {
	return p_dTankstelle;
}

Weg& Kreuzung::pZufaelligerWeg(Weg& w) {
	if (p_pWege.size() > 2) {
		auto tmp = find_if(p_pWege.begin(), p_pWege.end(), [&](std::shared_ptr<Weg>& wg) { return wg.get() == &w; });
		auto zfWeg = next(p_pWege.begin(), rand() % p_pWege.size());

		while (tmp == zfWeg)
			zfWeg = next(p_pWege.begin(), rand() % p_pWege.size());

		return **zfWeg;
	}
	else
		return w.getRueckweg();
}

void Kreuzung::vVerbinde(string sHinName, string sWegName, double dLaenge, shared_ptr<Kreuzung> Start, shared_ptr<Kreuzung> Ziel, Tempolimit limit, bool bUeberholverbot) {
	auto hin = make_shared<Weg>(sHinName, dLaenge, limit, Ziel, bUeberholverbot);
	auto rueck = make_shared<Weg>(sWegName, dLaenge, limit, Start, bUeberholverbot);
	rueck->setRueckweg(hin);
	hin->setRueckweg(rueck);
	/*rueck->setZielkreuzung(Start);
	hin->setZielkreuzung(make_shared<Kreuzung>(Ziel));*/
	Ziel->p_pWege.push_back(rueck);
	Start->p_pWege.push_back(hin);
}

void Kreuzung::vAusgeben(ostream& o) const{
	Simulationsobjekt::vAusgeben(o);
	o << setw(30) << "Tankstelle: " << p_dTankstelle << endl;
}


istream& Kreuzung::istreamEingabe(istream& i) {
	Simulationsobjekt::istreamEingabe(i) >> p_dTankstelle;
	return i;
}

ostream& operator<<(ostream& o, const Kreuzung& kz) {
	kz.vAusgeben(o);
	return o;
};



