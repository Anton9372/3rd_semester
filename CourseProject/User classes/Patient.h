//класс пацинта
#ifndef PATIENT_H
#define PATIENT_H
#include "User.h"
#include <QMap>
class Patient : public User
{
	QString dateOfBirth;    //дата рождения
	QString adress;         //адрес
public:
	Patient(int id = 0, char role = '\0', QString login = "", QString password = "", QString name = "", QString contacts = "", QString dateOfBirth = "", QString adress = "");
	virtual ~Patient();
	void setDateOfBirth(QString dateOfBirth);
	QString getDateOfBirth()const;
	void setAdress(QString adress);
	QString getAdress()const;
	friend QTextStream& operator<<(QTextStream& out, const Patient& obj);
	friend QTextStream& operator>>(QTextStream& in, Patient& obj);
	Patient& operator=(const Patient& other);
	//метод регистрации пациента
	int registration(Tree<User>& tree, QString login, QString password1, QString password2, QString name, QString contacts, QString dateOfBirth, QString adress);
	//метод изменения личной информации
	int changeInfo(QString pass1, QString pass2, QString name, QString contacts, QString adress);
};
