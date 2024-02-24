//класс доктора
#ifndef DOCTOR_H
#define DOCTOR_H
#include "User.h"
class Doctor : public User
{
	int experience;     //опыт работы(лет)
	int cabinet;        //рабочий кабинет
	int serviceId;      //ID предоставляемой услуги
public:
	Doctor(int id = 0, char role = '\0', QString login = "", QString password = "", QString name = "", QString contacts = "", int experience = 0, int cabinet = 0, int serviceId = 0);
	virtual ~Doctor();
	int getExperience()const;
	void setExperience(int experience);
	int getCabinet()const;
	void setCabinet(int cabinet);
	int getServiceId()const;
	void setServiceId(int serviceId);
	friend QTextStream& operator<<(QTextStream& out, const Doctor& obj);
	friend QTextStream& operator>>(QTextStream& in, Doctor& obj);
	//метод изменения личной информации
	int changeInfo(QString pass1, QString pass2, QString name, QString contacts, QString cabinet);
};
#endif // DOCTOR_H
