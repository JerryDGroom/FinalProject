#ifndef Patient_H
#define Patient_H
/*
Patient class stores the name, age for a patent
*/

#include <string>
using namespace std;

class Patient
{
public:
	Patient(string nm, string sp, int ag);

	// Return the information
	string getName();
	string getSpecialty();
	int getAge();

private:

	string name;
	string specialty;
	int age;
};


#endif
