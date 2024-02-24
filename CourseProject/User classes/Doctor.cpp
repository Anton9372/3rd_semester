#include "Doctor.h"
Doctor::Doctor(int id, char role, QString login, QString password, QString name, QString contacts, int experience, int serviceId, int cabinet)
	: User(id, role, login, password, name, contacts), experience(experience), serviceId(serviceId), cabinet(cabinet)
{

}
Doctor::~Doctor()
{

}
int Doctor::getExperience()const
{
	return experience;
}
void Doctor::setExperience(int experience)
{
	this->experience = experience;
}
int Doctor::getServiceId()const
{
	return serviceId;
}
int Doctor::getCabinet()const
{
	return cabinet;
}
void Doctor::setCabinet(int cabinet)
{
	this->cabinet = cabinet;
}
void Doctor::setServiceId(int serviceId)
{
	this->serviceId = serviceId;
}
QTextStream& operator<<(QTextStream& out, const Doctor& obj)
{
	out.setFieldAlignment(QTextStream::AlignLeft);
	out.setFieldWidth(3);
	out << obj.experience;
	out.setFieldWidth(3);
	out << obj.serviceId;
	out << obj.cabinet;
	out.setFieldWidth(0);  // Сбросить ширину поля
	return out;
}
QTextStream& operator>>(QTextStream& in, Doctor& obj)
{
	in >> obj.experience >> obj.serviceId >> obj.cabinet;
	return in;
}
int Doctor::changeInfo(QString pass1, QString pass2, QString name, QString contacts, QString cabinet)
{
	if (pass1 != pass2)            //если пароли не совпадают
		return -1;
	//установить новые данные
	this->setPassword(pass1);
	this->setName(name);
	this->setContacts(contacts);
	int cab = cabinet.toInt();
	this->setCabinet(cab);
	return 1;
}
