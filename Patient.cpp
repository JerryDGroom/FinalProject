#include "Patient.h"


Patient::Patient(string nm, string sp, int ag)
{
	name = nm;
	specialty = sp;
	age = ag;
}

// Return the information
string Patient::getName()
{
	return name;
}

string Patient::getSpecialty()
{
	return specialty;
}

int Patient::getAge()
{
	return age;
}