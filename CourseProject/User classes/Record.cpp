#include "Record.h"
Record::Record(int patientId, int doctorId) : patientId(patientId), doctorId(doctorId)
{

}
Record::~Record()
{

}
int Record::getPatientId()const
{
	return patientId;
}
void Record::setPatientId(int id)
{
	patientId = id;
}
int Record::getDoctorId()const
{
	return doctorId;
}
void Record::setDoctorId(int id)
{
	doctorId = id;
}
bool Record::compare(const Record& obj, int mode)const
{
	if (mode < 1 || mode > 4)
		throw AlgException(1, "Invalid mode parameter", __func__);  //выброс исключения
	else if (mode == 1)
		return getPatientId() < obj.getPatientId();
	else if (mode == 2)
		return getDoctorId() < obj.getDoctorId();
}
bool Record::isEqual(const Record& obj, int mode)const
{
	if (mode < 1 || mode > 4)
		throw AlgException(1, "Invalid mode parameter", __func__);  //выброс исключения
	else if (mode == 1)
		return getPatientId() == obj.getPatientId();
	else if (mode == 2)
		return getDoctorId() == obj.getDoctorId();
}
