#include "Aufgaben.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include "PKW.h" // doublevergleich
#include "Fahrrad.h"
#include "SimuClient.h"
#include <iostream>
#include <stdlib.h>
#include "vertagt_liste.h"
#include "Kreuzung.h"
#include "Simulation.h"
#include <fstream>

using namespace std;

extern double dGlobaleZeit;

void vAufgabe_4() {
	Weg weg1("Erster Weg", 100, Tempolimit::Hundert, nullptr, true);
	Weg::vKopf();
	cout << weg1;
}

void vAufgabe_5() {
	Weg Weg1("Erster Weg", 150, Tempolimit::Hundert, nullptr, true);
	unique_ptr<Fahrzeug> f1 = make_unique<Fahrzeug>("BMW", 120);
	unique_ptr<Fahrzeug> f2 = make_unique<Fahrzeug>("Audi", 100);
	unique_ptr<Fahrzeug> f3 = make_unique<Fahrzeug>("Mercedes-Benz", 100);
	
	Weg1.vAnnahme(move(f1), 1);
	Weg1.vAnnahme(move(f2));
	Weg1.vAnnahme(move(f3));

	Weg::vKopf();
	cout << Weg1;

	while (true) {
		Weg1.vSimulieren();
		dGlobaleZeit += 0.2;
		cout << "Zeit:  " << dGlobaleZeit << endl << endl;
		if (bDoubleVergleich(dGlobaleZeit, 1.8))
			break;
	}
	cout << endl << endl;
	Fahrzeug::vKopf();
	Weg1.vFahrzeugAusgeben();
}

void vAufgabe_6() {
	bInitialisiereGrafik(1200, 1000);

	Weg Weg1("W1", 500, Tempolimit::Hundert, nullptr, true);
	Weg Weg2("W2", 500, Tempolimit::Unbegrenzt, nullptr, true);
	int Koord1[] = { 700, 250, 100, 250 };
	bZeichneStrasse(Weg1.sGetName(), Weg2.sGetName(), 500, 2, Koord1);

	unique_ptr<PKW> f1 = make_unique<PKW>("BMW", 120, 12);
	unique_ptr<PKW> f2 = make_unique<PKW>("Audi", 100, 1);
	unique_ptr<PKW> f3 = make_unique<PKW>("Mercedes-Benz", 110, 15);
	unique_ptr<PKW> f4 = make_unique<PKW>("Opel", 90, 8);
	unique_ptr<Fahrrad> f5 = make_unique<Fahrrad>("BMX", 25);

	Weg1.vAnnahme(move(f1), 1); //parkender Fahrzeug
	Weg2.vAnnahme(move(f2));
	Weg2.vAnnahme(move(f3), 3);
	Weg1.vAnnahme(move(f4));
	Weg1.vAnnahme(move(f5));

	dGlobaleZeit = 0;
	while (true) {
		cout << "Zeit:  " << dGlobaleZeit << endl;
		vSetzeZeit(dGlobaleZeit);
		Weg1.vSimulieren();
		Weg2.vSimulieren();
		dGlobaleZeit += 0.2;
		cout << endl;
		vSleep(200);
	}
	vBeendeGrafik();
}

void vAufgabe_6a() {
	vertagt::VListe<int> list;
	for (int i = 0; i < 10; i++) {
		int val = rand() % 10 + 1;
		list.push_back(val); 
	}
	
	list.vAktualisieren();

	auto iter = list.begin();
	//for Schleife funktioniert nicht, weil der Iterator gerade nach list.erase() inkrementiert werden muss
	while (iter != list.end()) {
		if (*iter > 5) {
			list.erase(iter++);
		}
		else {
			++iter;
		}
	}

	list.vAktualisieren();

	cout << "Liste nach der Schleife: " << endl;

	for (int el : list) {
		cout << el << " ";
	}
	cout << endl;
}

void vAufgabe_7() {
	bInitialisiereGrafik(1200, 1000);

	//Kreuzungen
	shared_ptr<Kreuzung>kr1p = make_shared<Kreuzung>("Kr1");
	bZeichneKreuzung(680, 40);

	shared_ptr<Kreuzung>kr2p = make_shared<Kreuzung>("Kr2");
	bZeichneKreuzung(680, 300);

	shared_ptr<Kreuzung>kr3p = make_shared<Kreuzung>("Kr3");
	bZeichneKreuzung(680, 570);

	shared_ptr<Kreuzung>kr4p = make_shared<Kreuzung>("Kr4");
	bZeichneKreuzung(320, 300);

 	//Strasse 1
	kr1p->vVerbinde("W12", "W21", 40, kr1p, kr2p, Tempolimit::Fuenfzig, true);
	int Koord1[] = { 680, 40, 680, 300 };
	bZeichneStrasse("W12", "W21", 40, 2, Koord1);

	//Strasse 2
	kr2p->vVerbinde("W23a", "W32a", 115, kr2p, kr3p, Tempolimit::Unbegrenzt, false);
	int Koord2[] = { 680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570 };
	bZeichneStrasse("W23a", "W32a", 40, 6, Koord2);

	//Strasse 3
	kr3p->vVerbinde("W23b", "W32b", 40, kr2p, kr3p, Tempolimit::Fuenfzig, true);
	int Koord3[] = { 680, 300, 680, 570 };
	bZeichneStrasse("W23b", "W32b", 40, 2, Koord3);

	//Strasse 4
	kr4p->vVerbinde("W24", "W42", 40, kr2p, kr4p, Tempolimit::Fuenfzig, true);
	int Koord4[] = { 680, 300, 320, 300 };
	bZeichneStrasse("W24", "W42", 40, 2, Koord4);

	//Strasse 5
	kr3p->vVerbinde("W34", "W43", 85, kr3p, kr4p, Tempolimit::Unbegrenzt, false);
	int Koord5[] = { 680, 570, 500, 570, 350, 510, 320, 420, 320, 300 };
	bZeichneStrasse("W34", "W43", 85, 5, Koord5);

	//Strasse 6
	kr4p->vVerbinde("W44a", "W44b", 130, kr4p, kr4p, Tempolimit::Hundert, false);
	int Koord6[] = { 320, 300, 170, 300, 70, 250, 80, 90, 200, 60, 320, 150, 320, 300 };
	bZeichneStrasse("W44a", "W44b", 85, 7, Koord6);
	

	unique_ptr<PKW> f1 = make_unique<PKW>("BMW", 70, 12);
	unique_ptr<PKW> f2 = make_unique<PKW>("Audi", 40, 10);
	unique_ptr<PKW> f3 = make_unique<PKW>("Mercedes-Benz", 50, 1);
	unique_ptr<PKW> f4 = make_unique<PKW>("Opel", 80, 8);
	unique_ptr<Fahrrad> f5 = make_unique<Fahrrad>("BMX", 25);


	kr4p->vAnnahme(move(f1), 0.2);
	kr2p->vAnnahme(move(f2), 0.4);
	kr1p->vAnnahme(move(f3), 1);
	kr1p->vAnnahme(move(f4), 2);
	kr1p->vAnnahme(move(f5), 3);


	dGlobaleZeit = 0;
	while (true) {
		cout << "Zeit:  " << dGlobaleZeit << endl;
		vSetzeZeit(dGlobaleZeit);
		kr1p->vSimulieren();
		kr2p->vSimulieren();
		kr3p->vSimulieren();
		kr4p->vSimulieren();

		dGlobaleZeit += 0.1;
		cout << endl;
		vSleep(200);
	}
	vBeendeGrafik();
}

void vAufgabe_8() {
	try
	{
		string fileName = "VO.dat";
		ifstream file;
		file.open(fileName);

		if (!file)
			throw string(fileName + " konnte nicht geoeffnet werden");

		Kreuzung k;
		PKW p;
		Fahrrad f;

		file >> p >> f >> k;

		file.close();

		cout << "Erstellte Simulationsobjekte: " << endl << endl;
		Fahrzeug::vKopf();
		cout << p << endl << f << endl << k << endl << endl;
	}
	catch (string & e)
	{
		cerr << "Ausnahme: " << e << endl;
	}
}

void vAufgabe_9() {
	string sFileName = "Simu.dat";
	ifstream fDatei(sFileName);

	if (!fDatei) {
		cerr << "Die Datei " << sFileName << " konnte nicht geoeffnet werden" << endl;
		exit(1);
	}

	Simulation verkehrssystem;

	try {
		verkehrssystem.vEinlesen(fDatei);
	}
	catch (string & error) {
		cerr << "FEHLER: " << endl << error << endl;
		exit(1);
	}

	cout << "einlesen erfolgreich" << endl;

	verkehrssystem.vSimulieren(5, 0.2);

}

void vAufgabe_9a() {
	ifstream fDatei("SimuDisplay.dat");

	if (!fDatei) {
		cerr << "Die Datei SimuDisplay.dat konnte nicht geoeffnet werden" << endl;
		exit(1);
	}

	Simulation verkehrssystem;
	bInitialisiereGrafik(1200, 1000);

	try {
		verkehrssystem.vEinlesen(fDatei, true);
	}
	catch (string & error) {
		cerr << "FEHLER: " << endl << error << endl;
		exit(1);
	}

	cout << "Einlesen erfolgreich" << endl << endl;
	cout << "Simulation faengt an" << endl << endl;

	verkehrssystem.vSimulieren(10, 0.1);

}

