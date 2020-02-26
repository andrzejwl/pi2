#include "Simulation.h"
#include "Kreuzung.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "SimuClient.h"

extern double dGlobaleZeit;

void Simulation::vSimulieren(double dDauer, double dZeitschritt) {
	dGlobaleZeit = 0.0;
	while (dGlobaleZeit < dDauer) {
		for (auto const& k : mKreuzungen) {
			k.second->vSimulieren();
			vSleep(40);
		}
		dGlobaleZeit += dZeitschritt;
	}
	
}

void Simulation::vEinlesen(istream& i, bool bMitGrafik) {
	int iZeile = 0;
	while (!i.eof()) {
		iZeile++;
		string objekt = "";
		try {
			i >> objekt;
			cout << objekt << endl;
		}
		catch (exception & e) {
			throw string("Ein Problem ist beim Einlesen betreten, Zeile: " + to_string(iZeile));
		}

		if (objekt == "KREUZUNG") {
			shared_ptr<Kreuzung> pKreuzung = make_shared<Kreuzung>();

			i >> *pKreuzung;
			if (bMitGrafik) {
				int posX, posY;
				try {
					i >> posX >> posY;
				}
				catch (exception & e) {
					throw string("Ein Fehler ist beim Einlesen der Kreuzungkoordinaten betreten, Zeile: " + to_string(iZeile));
				}

				bZeichneKreuzung(posX, posY);
			}
			
			if (mKreuzungen.find(pKreuzung->sGetName()) != mKreuzungen.end())
				throw string("Kreuzung mit solchem Name wurde schon erstellt, Zeile: " + to_string(iZeile));

			mKreuzungen.insert(pair<string, shared_ptr<Kreuzung>>(pKreuzung->sGetName(), move(pKreuzung))); //move für schnellere Durchführung der Operation
		}
		else if (objekt == "STRASSE") {
			string NameQ, NameZ, NameW1, NameW2;
			double Laenge;
			int iTL;
			Tempolimit TL;
			int iUeberholverbot;
			bool bUeberholverbot;
			
			try {
				i >> NameQ >> NameZ >> NameW1 >> NameW2 >> Laenge >> iTL >> iUeberholverbot;
			}
			catch (exception& e){
				throw string("Ein Fehler ist beim Einlesen von STRASSE betreten, Zeile: " + to_string(iZeile));
			}

			switch (iTL) {
			case 1 :
				TL = Tempolimit::Fuenfzig;
				break;
			case 2 :
				TL = Tempolimit::Hundert;
				break;
			case 3 :
				TL = Tempolimit::Unbegrenzt;
				break;
			default:
				throw string("Unbekanntes Wert beim Einlesen von Tempolimit, Zeile: " + to_string(iZeile));
				break;
			}

			switch (iUeberholverbot) {
			case 0:
				bUeberholverbot = false;
				break;
			case 1:
				bUeberholverbot = true;
				break;
			default:
				throw string("Unbekanntes Wert beim Einlesen von Ueberholverbot, Zeile: " + to_string(iZeile));
				break;
			}

			if (mKreuzungen.find(NameQ) == mKreuzungen.end() or mKreuzungen.find(NameZ) == mKreuzungen.end())
				throw string("Kreuzungen nicht gefunden, Zeile: " + to_string(iZeile));
			else {
				auto pQuelle = mKreuzungen.find(NameQ)->second;
				auto pZiel = mKreuzungen.find(NameZ)->second;

				pQuelle->vVerbinde(NameW1, NameW2, Laenge, pQuelle, pZiel, TL, bUeberholverbot);

				if (bMitGrafik) {
					try {
						int iAnzahl;
						i >> iAnzahl;
						int* iKoordinaten = new int[2 * iAnzahl];

						for (int k = 0; k < iAnzahl; k++) {
							i >> iKoordinaten[2 * k] >> iKoordinaten[2 * k + 1];
						}

						bZeichneStrasse(NameW1, NameW2, int(Laenge), iAnzahl, iKoordinaten);
						delete iKoordinaten;
					}
					catch (exception e) {
						throw string("Ein Problem ist beim Einlesen der Strassenkoordinaten betreten, Zeile: " + to_string(iZeile));
					}
				}
			}
		}
		else if (objekt == "PKW") {
			unique_ptr<PKW> pAuto = make_unique<PKW>();
			string sKrName;
			double dStartzeit;

			try {
				i >> *pAuto >> sKrName >> dStartzeit;
			}
			catch (exception & e) {
				throw("Ein Fehler ist beim Einlesen von PKW betreten, Zeile: " + to_string(iZeile));
			}

			auto pKreuzung = mKreuzungen.find(sKrName);
			
			if (pKreuzung == mKreuzungen.end())
				throw string("PKW: Startkreuzung nicht gefunden, Zeile: " + to_string(iZeile));
			else {
				pKreuzung->second->vAnnahme(move(pAuto), dStartzeit);
			}
		}
		else if (objekt == "FAHRRAD") {
			unique_ptr<Fahrrad> pFahrrad = make_unique<Fahrrad>();
			string sKrName;
			double dStartzeit;

			try {
				i >> *pFahrrad >> sKrName >> dStartzeit;
			}
			catch (exception & e) {
				throw("Ein Fehler ist beim Einlesen von Fahrrad betreten, Zeile: " + to_string(iZeile));
			}

			auto pKreuzung = mKreuzungen.find(sKrName);

			if (pKreuzung == mKreuzungen.end())
				throw string("FAHRRAD: Startkreuzung nicht gefunden, Zeile: " + to_string(iZeile));
			else {
				pKreuzung->second->vAnnahme(move(pFahrrad), dStartzeit);
			}
		}
		else 
			throw string("Unbekanntes Simulationsobjekt "+ objekt + ", Zeile: " + to_string(iZeile));
	}


}