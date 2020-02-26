#include "Weg.h"
#include "Kreuzung.h"
#include "Fahrzeug.h"
#include "Losfahren.h"
#include "Streckenende.h"
#include <string>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <iostream>
using namespace std;

Weg::Weg() : Simulationsobjekt::Simulationsobjekt(), p_dLaenge(10), p_eTempolimit(Tempolimit::Unbegrenzt), p_dSchranke(p_dLaenge), p_bUeberholverbot(true), 
			p_pZielKreuzung(make_shared<Kreuzung>()), p_pRueckweg(make_shared<Weg>()) {
}

Weg::Weg(string sName, double dLaenge, Tempolimit eTL, shared_ptr<Kreuzung> pZiel, bool bUeberholverbot):
	Simulationsobjekt::Simulationsobjekt(sName), p_dLaenge(dLaenge), p_eTempolimit(eTL), p_dSchranke(p_dLaenge), 
	p_bUeberholverbot(bUeberholverbot), p_pZielKreuzung(pZiel) {
}

Weg::~Weg() {
}


Weg& Weg::getRueckweg() {
	return *p_pRueckweg.lock();
}

void Weg::setRueckweg(shared_ptr<Weg> rueckweg) {
	p_pRueckweg = rueckweg;
}


void Weg::setZielkreuzung(shared_ptr<Kreuzung> zielkreuzung) {
	p_pZielKreuzung = zielkreuzung;
}

Kreuzung& Weg::getZielkreuzung() {
	return *(p_pZielKreuzung.lock());
}


ostream& operator<<(ostream& o, const Weg& w) {
	w.vAusgeben(o);
	return o;
};

void Weg::vAnnahme(unique_ptr<Fahrzeug> f) {
	f->vNeueStrecke(*this);
	p_pFahrzeuge.push_back(move(f));
}

void Weg::vAnnahme(unique_ptr<Fahrzeug> f, double dStartZeit) {
	f->vNeueStrecke(*this, dStartZeit);
	p_pFahrzeuge.push_front(move(f));
}

double Weg::dGetTempoLimit() {
	switch (p_eTempolimit) {
	case Tempolimit::Unbegrenzt :
		return numeric_limits<double>::infinity();

	case Tempolimit::Hundert:
		return 100.0;
	
	case Tempolimit::Fuenfzig:
		return 50.0;
	}
	return 0.0;
}

string Weg::sGetName() const {
	return p_sName;
}

void Weg::vFahrzeugeZeichnen() {
	for (auto const& f : p_pFahrzeuge) {
		f->vZeichnen(*this);
	}

}

int Weg::iGetId() {
	return p_iID;
}

unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& fz) {
	list<unique_ptr<Fahrzeug>>::iterator it = p_pFahrzeuge.begin();

	auto tmp = find_if(p_pFahrzeuge.begin(), p_pFahrzeuge.end(), [&](std::unique_ptr<Fahrzeug>& a) { return a.get() == &fz; });
	while (it != p_pFahrzeuge.end()) {
		if (*it == *tmp)
			break;
		++it;
	}
	if (it != p_pFahrzeuge.end()) {
		unique_ptr<Fahrzeug> ptr = move(*tmp);
		p_pFahrzeuge.erase(tmp);
		//p_pFahrzeuge.p_objekte.remove(NULL);
		return ptr;
	}
	else
		return make_unique<Fahrzeug>(nullptr);
}

double Weg::dGetLaenge() const {
	return p_dLaenge;
}

void Weg::vSimulieren() {
	p_dSchranke = p_dLaenge; 

	for_each(p_pFahrzeuge.begin(), p_pFahrzeuge.end(), [&](const unique_ptr<Fahrzeug>& f) {
		try {
			f->vSimulieren();
			if (p_bUeberholverbot)
				if (p_dSchranke > f->dGetPos() and !f->bGeparkt())
					p_dSchranke = f->dGetPos();
		}
		catch (Losfahren & err) 
		{
			cout << "exception caught" << endl;
			err.vBearbeiten();
			auto f_ptr = pAbgabe(*f);
			vAnnahme(move(f_ptr));
		}
		catch (Streckenende & err) {
			cout << "exception caught: Streckenende" << endl;
			err.vBearbeiten();
			//auto f_ptr = pAbgabe(*f);
		}
	});
	p_pFahrzeuge.vAktualisieren();
	vFahrzeugeZeichnen();
}

void Weg::vKopf() {
	cout << setw(7) << "ID" << setw(20) << "Name" << setw(15) << "Laenge" << setw(30) << "Fahrzeuge" << endl;
}

void Weg::vAusgeben(ostream &o) const {
	Simulationsobjekt::vAusgeben(o);
	o << setw(15) << p_dLaenge << setw(30) << "(";

	for (const unique_ptr<Fahrzeug>& f : p_pFahrzeuge) {
		o << f->sGetName() << " ";
	}

	o << ")" << endl;
}

void Weg::vFahrzeugAusgeben() {
	for (const unique_ptr<Fahrzeug>& f : p_pFahrzeuge) {
		cout << *f << endl;
	}
}
