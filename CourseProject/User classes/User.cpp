#include "User.h"
User::User(int id, char role, QString login, QString password, QString name, QString contacts) : id(id), role(role), login(login), password(password), name(name), contacts(contacts)
{

}
User::~User()
{

}
int User::getId()const
{
	return id;
}
char User::getRole()const
{
	return role;
}
QString User::getLogin()const
{
	return login;
}
void User::setPassword(QString password)
{
	this->password = password;
}
QString User::getPassword()const
{
	return password;
}
void User::setContacts(QString contacts)
{
	this->contacts = contacts;
}
QString User::getContacts()const
{
	return contacts;
}
void User::setName(QString name)
{
	this->name = name;
}
QString User::getName()const
{
	return name;
}
QTextStream& operator<<(QTextStream& out, const User& obj)
{
	out.setFieldAlignment(QTextStream::AlignLeft);
	out.setFieldWidth(3);
	out << obj.id;
	out.setFieldWidth(2);
	out << obj.role;
	out.setFieldWidth(11);
	out << obj.login;
	out.setFieldWidth(5);
	out << obj.password;
	out.setFieldWidth(36);
	out << obj.name;
	out.setFieldWidth(3);
	out << obj.contacts;
	out.setFieldWidth(0);   //cбросить ширину поля
	return out;
}
QTextStream& operator>>(QTextStream& in, User& obj)
{
	QString login, password, name1, name2, name3, contacts;
	in >> obj.id;
	in.skipWhiteSpace();
	in >> obj.role >> login >> password >> name1 >> name2 >> name3 >> contacts;
	obj.login = login;
	obj.password = password;
	obj.name = name1 + " " + name2 + " " + name3;
	obj.contacts = contacts;
	return in;
}
bool User::operator==(User& other)
{
	return id == other.id && role == other.role && login == other.login && password == other.password && contacts == other.contacts && name == other.name;
}
User& User::operator=(const User& other)
{
	if (this == &other)
		return *this;
	id = other.id;
	role = other.role;
	login = other.login;
	password = other.password;
	contacts = other.contacts;
	name = other.name;
	return *this;
}
bool User::compare(const User& obj, int mode)const
{
	if (mode < 1 || mode > 4)
		throw AlgException(1, "Invalid mode parameter", __func__);  //выброс исключения
	else if (mode == 1)
		return getId() < obj.getId();
	else if (mode == 2)
		return getLogin() < obj.getLogin();
	else if (mode == 3)
		return getPassword() < obj.getPassword();
	else if (mode == 4)
		return getName() < obj.getName();
}
bool User::isEqual(const User& obj, int mode)const
{
	if (mode < 1 || mode > 4)
		throw AlgException(1, "Invalid mode parameter", __func__);  //выброс исключения
	else if (mode == 1)
		return getId() == obj.getId();
	else if (mode == 2)
		return getLogin() == obj.getLogin();
	else if (mode == 3)
		return getPassword() == obj.getPassword();
	else if (mode == 4)
		return getName() == obj.getName();
}
int User::authorisation(Tree<User>& tree, QString login, QString password)
{
	Algorithm<User>::restructing(tree, 2);  //перестройка дерева по параметру логин
	//установить логин и пароль
	this->login = login;
	this->password = password;
	//найти в дереве пользователя с текущим логином
	auto result = Algorithm<User>::search(tree, *this);
	if (result.has_value())                          //если пользователь существует
	{
		if (result->getPassword() == password)        //если пароль совпадает
		{
			//установить остальные параметры
			this->id = result->getId();
			this->role = result->getRole();
			this->login = result->getLogin();
			this->password = result->getPassword();
			this->name = result->getName();
			this->contacts = result->getContacts();
			return 1;
		}
		else
			return 0;
	}
	else
		return -1;
}