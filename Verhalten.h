#pragma once
class Weg;
class Fahrzeug;

class Verhalten {
public:
	Verhalten(Weg&);
	~Verhalten();
	double dGeschwindigkeitslimit();
	virtual double dStrecke(Fahrzeug&, double);
	friend class Fahrzeug;
	friend class PKW;
	friend class Fahrrad;
	friend class Streckenende;
protected:
	Weg* p_pWeg;
};