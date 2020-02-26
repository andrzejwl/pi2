#pragma once
#include "Verhalten.h"

class Fahren : public Verhalten {
public:
	Fahren(Weg&);
	~Fahren();
};