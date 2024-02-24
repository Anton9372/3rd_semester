//класс пользователя
#ifndef USER_H
#define USER_H
#include "tree.h"
#include "iter.h"
#include <codecvt>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include "exception.h"
#include "algorithm.h"
class User
{
protected:
	int id;             //ID пользователя
	char role;          //роль пользователя (d - doctor, p - patient)
	QString login;      //логин
	QString password;   //пароль
	QString contacts;   //контакт
	QString name;       //ФИО
public:
	User(int = 0, char role = '\0', QString login = "", QString password = "", QString name = "", QString contacts = "");
	virtual  ~User();
	int getId()const;
	char getRole()const;
	QString getLogin()const;
	void setPassword(QString password);
	QString getPassword()const;
	void setContacts(QString contacts);
	QString getContacts()const;
	void setName(QString name);
	QString getName()const;
	friend QTextStream& operator<<(QTextStream& out, const User& obj);
	friend QTextStream& operator>>(QTextStream& in, User& obj);
	bool operator==(User& other);
	User& operator=(const User& other);
	//компараторы
	//mode = 1: ID
	//mode = 2: login
	//mode = 3: password
	//mode = 4: name
	bool compare(const User& obj, int mode)const;
	bool isEqual(const User& obj, int mode)const;
	//метод авторизации пользователя
	int authorisation(Tree<User>& tree, QString login, QString password);
};
#endif // USER_H
