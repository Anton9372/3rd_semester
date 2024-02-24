//класс медицинской записи в карточку пациента
#ifndef MEDRECORD_H
#define MEDRECORD_H
#include "Record.h"
#include "QString"
class MedRecord : public Record
{
protected:
	QString date;   //дата записи
public:
	MedRecord(int patientId = 0, int doctorId = 0, QString date = "");
	virtual ~MedRecord();
	QString getDate()const;
	void setDate(QString date);
	//компараторы
	//mode = 1: patientId
	//mode = 2: doctorId
	//mode = 3: date
	virtual bool compare(const Record& obj, int mode)const;
	virtual bool isEqual(const Record& obj, int mode)const;
};
#endif // MEDRECORD_H
