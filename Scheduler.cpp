

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Scheduler.h"

Scheduler::Scheduler()
{
}


void Scheduler::start()
{
	string person;
	string type;
	string name, code;
	int num, age;
	do
	{
		cout << "Type D for Doctor or P for Patient: ";
		cin >> person;

		cout << "Type I for check-in or O for checkout: ";
		cin >> type;
		cin.ignore(20, '\n');

		if (person == "D" || person == "d")
		{
			if (type == "I" || type == "i")
			{
				// Prompt for name, code and room
				cout << "Enter doctor name to check in: ";
				getline(cin, name);
				cout << "Enter specialty code: ";
				cin >> code;
				cout << "Enter room number(1-" << NUMROOM << "): ";
				cin >> num;
				checkInDoctor(name, code, num);
			}
			else if (type == "O" || type == "o")
			{
				cout << "Enter doctor name to check out: ";
				getline(cin, name);
				checkOutDoctor(name);
			}
		}
		else if (person == "P" || person == "p")
		{
			if (type == "I" || type == "i")
			{
				cout << "Enter patient name to check in: ";
				getline(cin, name);
				cout << "Enter specialty code: ";
				cin >> code;
				cout << "Enter age: ";
				cin >> age;
				checkInPatient(name, code, age);
			}
			else if (type == "O" || type == "o")
			{
				cout << "Enter patient name to check out: ";
				getline(cin, name);
				cout << "Enter room number(1-" << NUMROOM << "): ";
				cin >> num;
				checkOutPatient(name, num);
			}
		}
		cin.clear();

	} while (person != "Q");
}

bool Scheduler::isValidCode(string code)
{
	int i;
	string all[] = {
		"PED", "ped", "FAM", "fam", "INT", "int",
		"CAR", "car", "SUR", "sur", "OBS", "obs",
		"PSY", "psy", "NEU", "neu", "ORT", "ort",
		"DET", "det", "OPT", "opt", "ENT", "ent"
	};
	for (i = 0; i < 24; i++)
	{
		if (all[i] == code)
			return true;
	}

	cout << "Error: Invalid specialty." << endl;
	cout << "Valid code: ";
	for (i = 0; i < 24; i++)
		cout << all[i] << " ";
	cout << endl << endl;

	return false;
}

void Scheduler::checkInDoctor(string name, string code, int num)
{
	ofstream file("messages.out", ios::out | ios::app);
	time_t t = time(0);
	file << ctime(&t) << "Doctor Check-In Request -- Name: "
		<< name << " Specialty: " << code << " Room: " << num << endl;

	if (!isValidCode(code))
	{
		file << "Error: Invalid specialty." << endl << endl;
		return;
	}

	if (num < 1 || num > NUMROOM)
	{
		cout << "Error: Invalid room." << endl << endl;
		file << "Error: Invalid room." << endl << endl;
		return;
	}

	if (rooms[num - 1].getDoctor() != NULL)
	{
		cout << "Error: Room is used." << endl << endl;
		file << "Error: Room is used." << endl << endl;
		return;
	}

	rooms[num - 1].doctorEnter(new Doctor(name, code, num));
	cout << "Doctor " << name << "(" << code << ") Check-In to Room "
		<< num << endl << endl;
	file << "Doctor " << name << "(" << code << ") Check-In to Room "
		<< num << endl << endl;

	file.close();
}

void Scheduler::checkOutDoctor(string name)
{
	ofstream file("messages.out", ios::out | ios::app);
	time_t t = time(0);
	file << ctime(&t) << "Doctor Check-Out Request -- Name: "
		<< name << endl;
	int num = -1;

	for (int i = 0; i < NUMROOM; i++)
	{
		if (rooms[i].getDoctor() != NULL &&
			rooms[i].getDoctor()->getName() == name)
		{
			num = i + 1;
			break;
		}
	}

	if (num < 0)
	{
		cout << "Error: Doctor not found." << endl << endl;
		file << "Error: Doctor not found." << endl << endl;
		return;
	}

	cout << "Doctor " << name << " Check-Out. Good-bye" << endl;
	file << "Doctor " << name << " Check-Out. Good-bye" << endl;

	rooms[num - 1].doctorLeave();

	// try to assign each patient to other room
	while (rooms[num - 1].getPatient() != NULL)
	{
		Patient* p = rooms[num - 1].getPatient();
		rooms[num - 1].patientLeave();

		cout << "Try to reassign patient " << p->getName() << ": ";
		file << "Try to reassign patient " << p->getName() << ": ";
		int newnum = assignPatient(p);
		if (newnum < 0)
		{
			cout << "Sorry, there is no doctor avaiable" << endl;
			file << "Sorry, there is no doctor avaiable" << endl;
			delete p;
		}
		else
		{
 			cout << "Assigned to Room " << newnum
				<< " Doctor " << rooms[newnum - 1].getDoctor()->getName() << endl;
			file << "Assigned to Room " << num
				<< " Doctor " << rooms[newnum - 1].getDoctor()->getName() << endl;
		}
	}
	cout << endl;
	file << endl;
}

void Scheduler::checkInPatient(string name, string code, int age)
{
	ofstream file("messages.out", ios::out | ios::app);
	time_t t = time(0);
	file << ctime(&t) << "Patient Check-In Request -- Name: "
		<< name << " Specialty: " << code << " Age: " << age << endl;

	Patient* p = new Patient(name, code, age);

	int num = assignPatient(p);

	if (num < 0)
	{
		cout << "Sorry, there is no doctor available" << endl << endl;
		file << "Sorry, there is no doctor available" << endl << endl;
		delete p;
	}
	else
	{
		cout << "Patient Check-In Succeeded, Room " << num
			<< " Doctor " << rooms[num - 1].getDoctor()->getName() << endl << endl;
		file << "Patient Check-In Succeeded, Room " << num
			<< " Doctor " << rooms[num - 1].getDoctor()->getName() << endl << endl;
	}
}

void Scheduler::checkOutPatient(string name, int num)
{
	ofstream file("messages.out", ios::out | ios::app);
	time_t t = time(0);
	file << ctime(&t) << "Patient Check-Out Request -- Name: "
		<< name << " Room: " << num << endl;

	if (num < 1 || num > NUMROOM)
	{
		cout << "Error: Invalid room." << endl << endl;
		file << "Error: Invalid room." << endl << endl;
		return;
	}

	Patient* p = rooms[num - 1].getPatient();
	if (p == NULL || p->getName() != name)
	{
		cout << "Error: Patient " << name << " has not been seen by the doctor."
			<< endl << endl;
		file << "Error: Patient " << name << " has not been seen by the doctor."
			<< endl << endl;
		return;
	}

	rooms[num - 1].patientLeave();
	delete p;

	cout << "Patient " << name << " Check-Out. Good-bye" << endl;
	file << "Patient " << name << " Check-Out. Good-bye" << endl;

	p = rooms[num - 1].getPatient();
	if (p != NULL)
	{
		cout << "Next Patient in the room is " << p->getName() << endl;
		file << "Next Patient in the room is " << p->getName() << endl;
	}

	cout << endl;
	file << endl;
}

int Scheduler::findDoctorRoom(string code)
{
	int result = -1;
	int waitlen = 0;

	for (int i = 0; i < NUMROOM; i++)
	{
		if (rooms[i].getDoctor() == NULL)
			continue;

		// If code is empty find any doctor
		if (code == "" || code == rooms[i].getDoctor()->getSpecialty())
		{
			// find the doctor with shortest waiting list
			if (result == -1 || rooms[i].getWaitingLen() < waitlen)
			{
				result = i + 1;
				waitlen = rooms[i].getWaitingLen();
			}
		}
	}
	return result;
}

int Scheduler::assignPatient(Patient* p)
{
	int num = -1;
	if (p->getAge() < 15)
		num = findDoctorRoom("PED");
	else
		num = findDoctorRoom(p->getSpecialty());

	// find family practitioner
	if (num < 0)
		num = findDoctorRoom("FAM");

	// find any doctor
	if (num < 0)
		num = findDoctorRoom("");

	if (num < 0)
		return -1;

	rooms[num - 1].patientEnter(p);

	return num;
}
