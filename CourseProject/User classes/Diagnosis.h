//класс записи результатов приема у врача в карточку пациента
#ifndef DIAGNOSIS_H
#define DIAGNOSIS_H
#include "MedRecord.h"
class Diagnosis : public MedRecord
{
	int serviceId;      //ID услуги
	QString diagnosis;  //диагноз
public:
	Diagnosis(int patientId = 0, int doctorId = 0, QString date = "", int serviceId = 0, QString diagnosis = "");
	~Diagnosis();
	int getServiceId()const;
	void setServiceId(int serviceId);
	QString getDiagnosis()const;
	void setDiagnosis(QString diagnosis);
	friend QTextStream& operator<<(QTextStream& out, const Diagnosis& obj);
	friend QTextStream& operator>>(QTextStream& in, Diagnosis& obj);
};
#endif // DIAGNOSIS_H
