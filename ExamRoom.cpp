/*
*******************************************************************
Final Project || Jerry Groom                           ExamRoom.cpp
4/29/2015
*******************************************************************
*/

#include "ExamRoom.h"


ExamRoom::ExamRoom()
{
	doctor = NULL;
	patient = NULL;
}


// Return doctor
Doctor* ExamRoom::getDoctor()
{
	return doctor;
}

// Return current patient
Patient* ExamRoom::getPatient()
{
	return patient;
}

// Get the waitng list
int ExamRoom::getWaitingLen()
{
	return waiting.size();
}

// doctor enters this room
bool ExamRoom::doctorEnter(Doctor* doc)
{
	if (doctor != NULL)
		return false;
	doctor = doc;
	return true;
}

// doctor leaves this room
void ExamRoom::doctorLeave()
{
	doctor = NULL;
}

// patient enters this room
void ExamRoom::patientEnter(Patient* p)
{
	if (patient == NULL)
		patient = p;
	else
		waiting.push_back(p);
}

// patient leave, see next
void ExamRoom::patientLeave()
{
	patient = NULL;
	if (waiting.size() != 0)
	{
		patient = waiting[0];
		waiting.erase(waiting.begin());
	}
}
