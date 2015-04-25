/*
*******************************************************************
Final Project || Jerry Groom                            Doctor.cpp
4/29/2015
*******************************************************************
*/

#include "Doctor.h"


Doctor::Doctor(string nm, string sp, int no)
{
	name = nm;
	specialty = sp;
	room = no;
}

// get the information
string Doctor::getName()
{
	return name;
}

string Doctor::getSpecialty()
{
	return specialty;
}

int Doctor::getRoom()
{
	return room;
}
