#ifndef ExamRoom_H
#define ExamRoom_H
/*
ExamRoom class contains the information of current doctor and 
  patient waiting list
*/

#include "Doctor.h"
#include "Patient.h"
#include <vector>
using namespace std;

class ExamRoom
{
public:
	ExamRoom();

	// Return doctor
	Doctor* getDoctor();

	// Return current patient
	Patient* getPatient();

	// Get the length waitng list
	int getWaitingLen();

	// doctor enters this room
	bool doctorEnter(Doctor* doc);

	// doctor leaves this room
	void doctorLeave();

	// patient enters this room
	void patientEnter(Patient* p);

	// see next patient
	void patientLeave();


private:
	Doctor* doctor;
	Patient* patient;
	vector<Patient*> waiting;
};

#endif
