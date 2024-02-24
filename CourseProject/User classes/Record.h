//класс записи врача пациенту
#ifndef RECORD_H
#define RECORD_H
#include <QTextStream>
#include "exception.h"
class Record
{
protected:
	int patientId;  //ID пациента
	int doctorId;   //ID доктора
public:
	Record(int patientId = 0, int doctorId = 0);
	virtual ~Record();
	int getPatientId()const;
	void setPatientId(int id);
	int getDoctorId()const;
	void setDoctorId(int id);
	//компараторы
	//mode = 1: patientID
	//mode = 2: doctorID
	virtual bool compare(const Record& obj, int mode)const;
	virtual bool isEqual(const Record& obj, int mode)const;
};
#endif // RECORD_H
