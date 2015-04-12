#ifndef Doctor_H
#define Doctor_H

/*
Doctor class stores the name, Specialty code, room no for a doctor
*/

#include <string>
using namespace std;

class Doctor
{
public:
	Doctor(string nm, string sp, int no);

	// get the information
	string getName();
	string getSpecialty();
	int getRoom();

private:
	string name;
	string specialty;
	int room;
};

#endif

