#include "Analysis.h"
Analysis::Analysis(int patientId, int doctorId, QString date, QString type, QString results) :
	MedRecord(patientId, doctorId, date), type(type), results(results)
{

}
Analysis::~Analysis()
{

}
QString Analysis::getType()const
{
	return type;
}
void Analysis::setType(QString type)
{
	this->type = type;
}
QString Analysis::getResults()const
{
	return results;
}
void Analysis::setResults(QString results)
{
	this->results = results;
}
QTextStream& operator<<(QTextStream& out, const Analysis& obj)
{
	out.setFieldAlignment(QTextStream::AlignLeft);  //выравнивание по левому краю
	out.setFieldWidth(3);
	out << obj.getPatientId();
	out.setFieldWidth(3);
	out << obj.getDoctorId();
	out.setFieldWidth(11);
	out << obj.getDate();
	out.setFieldWidth(21);
	out << obj.getType();
	out << obj.results;
	out.setFieldWidth(0);   //сбросить ширину поля
	return out;
}
QTextStream& operator>>(QTextStream& in, Analysis& obj)
{
	in >> obj.patientId >> obj.doctorId >> obj.date >> obj.type;
	obj.results = in.readLine().trimmed();
	return in;
}
