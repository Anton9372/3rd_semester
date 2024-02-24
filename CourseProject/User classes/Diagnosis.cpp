#include "Diagnosis.h"
Diagnosis::Diagnosis(int patientId, int doctorId, QString date, int serviceId, QString diagnosis) :
	MedRecord(patientId, doctorId, date), serviceId(serviceId), diagnosis(diagnosis)
{

}
Diagnosis::~Diagnosis()
{

}
int Diagnosis::getServiceId()const
{
	return serviceId;
}
void Diagnosis::setServiceId(int serviceId)
{
	this->serviceId = serviceId;
}
QString Diagnosis::getDiagnosis()const
{
	return diagnosis;
}
void Diagnosis::setDiagnosis(QString diagnosis)
{
	this->diagnosis = diagnosis;
}
QTextStream& operator<<(QTextStream& out, const Diagnosis& obj)
{
	out.setFieldAlignment(QTextStream::AlignLeft);
	out.setFieldWidth(3);
	out << obj.getPatientId();
	out.setFieldWidth(3);
	out << obj.getDoctorId();
	out.setFieldWidth(11);
	out << obj.getDate();
	out.setFieldWidth(3);
	out << obj.serviceId;
	out << obj.diagnosis;
	out.setFieldWidth(0);  // —бросить ширину пол€
	return out;
}
QTextStream& operator>>(QTextStream& in, Diagnosis& obj)
{
	in >> obj.patientId >> obj.doctorId >> obj.date >> obj.serviceId;
	obj.diagnosis = in.readLine().trimmed();
	return in;
}
