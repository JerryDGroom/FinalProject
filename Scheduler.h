#ifndef Scheduler_H
#define Scheduler_H
/*
Hospital class contains the examination rooms
*/

const int NUMROOM = 25;

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "ExamRoom.h"
#include "Doctor.h"
#include "Patient.h"

using namespace std;

class Scheduler
{
public:
	Scheduler();

	void start();

	// determine if the code is valid
	bool isValidCode(string code);

	// check-in/check-out doctor and patient
	void checkInDoctor(string name, string code, int num);
	void checkOutDoctor(string name);
	void checkInPatient(string name, string code, int age);
	void checkOutPatient(string name, int num);

private:
	// find a doctor with the code, if code is empty, find any doctor
	//   return the room no, or -1 if not found
	int findDoctorRoom(string code);

	// assign patient to a doctor, return the room no, or -1 if not found
	int assignPatient(Patient* p);

	ExamRoom rooms[NUMROOM];
};

#endif
