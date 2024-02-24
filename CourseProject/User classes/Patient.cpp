#include "Patient.h"
Patient::Patient(int id, char role, QString login, QString password, QString name, QString contacts, QString dateOfBirth, QString adress) : User(id, role, login, password, name, contacts), dateOfBirth(dateOfBirth), adress(adress)
{

}
Patient::~Patient()
{

}
void Patient::setDateOfBirth(QString dateOfBirth)
{
	this->dateOfBirth = dateOfBirth;
}
QString Patient::getDateOfBirth()const
{
	return dateOfBirth;
}
void Patient::setAdress(QString adress)
{
	this->adress = adress;
}
QString Patient::getAdress()const
{
	return adress;
}
Patient& Patient::operator=(const Patient& other)
{
	if (this == &other)
		return *this;
	id = other.id;
	role = other.role;
	login = other.login;
	password = other.password;
	name = other.name;
	contacts = other.contacts;
	dateOfBirth = other.dateOfBirth;
	adress = other.adress;
	return *this;
}
QTextStream& operator<<(QTextStream& out, const Patient& obj)
{
	out.setFieldAlignment(QTextStream::AlignLeft);
	out.setFieldWidth(11);
	out << obj.dateOfBirth;
	out << obj.adress;
	out.setFieldWidth(0);   //сбросить ширину поля
	return out;
}
QTextStream& operator>>(QTextStream& in, Patient& obj)
{
	QString street, flat;
	in >> obj.dateOfBirth >> street >> flat;
	obj.adress = street + " " + flat;
	return in;
}
int Patient::registration(Tree<User>& tree, QString login, QString password1, QString password2, QString name, QString contacts, QString dateOfBirth, QString adress)
{
	if (password1 != password2)    //если пароли не совпадают
		return 0;
	this->login = login;
	this->password = password1;
	if (Algorithm<User>::search(tree, *this).has_value())     //если пользователь с таким логином уже существует
		return -1;
	else
	{
		//установить данные для пользователя
		this->id = tree.getCount(tree.getRoot()) + 1;
		this->role = 'p';
		this->name = name;
		this->contacts = contacts;
		this->dateOfBirth = dateOfBirth;
		this->adress = adress;
		return 1;
	}
}
int Patient::changeInfo(QString pass1, QString pass2, QString name, QString contacts, QString adress)
{
	if (pass1 != pass2)                //если пароли не совпадают
		return -1;
	//установить новые данные пользователя
	this->setPassword(pass1);
	this->setName(name);
	this->setContacts(contacts);
	this->setAdress(adress);
	return 1;
}