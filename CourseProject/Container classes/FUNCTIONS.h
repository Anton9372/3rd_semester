#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <QMap>
#include <QTextStream>
#include <QFile>
#include <QTextCodec>
#include "tree.h"
#include "exception.h"
//функция считывания данных из файла в контейнер
template <typename T>
void fill_map_cont(QMap<int, T>& map, const QString& filename)
{
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		throw FileException(11, "Ошибка при открытии файла", filename); //выбросить иключение
	QTextStream in(&file);
	in.setCodec(QTextCodec::codecForName("UTF-8"));
	while (!in.atEnd())     //пока не конец файла
	{
		int id;
		T obj;
		in >> id >> obj;    //считать ID пользователя и данные
		if (in.status() != QTextStream::Ok)
			throw InputException(2, "Ошибка чтения из файла", "Ошибка ввода");
		map.insert(id, obj);//добавить в контейнер
	}
	file.close();
}
//функция считывания данных из файла в контейнер
void fill_map_cont(QMap<int, QString>& map, const QString& filename);

//функция записи данных из контейнера в файл
template <typename T>
void write_file_map_cont(QMap<int, T>& map, const QString& filename)
{
	QFile file(filename);
	if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
		throw FileException(11, "Ошибка при открытии файла", filename); //выбросить иключение
	QTextStream out(&file);
	out.setCodec(QTextCodec::codecForName("UTF-8"));
	for (auto it = map.begin(), ite = map.end(); it != ite; ++it)       //пройти по контейнеру
	{
		out.setFieldAlignment(QTextStream::AlignLeft);
		out.setFieldWidth(3);
		//запись данных
		out << it.key();
		out << it.value() << '\n';
		if (out.status() != QTextStream::Ok)
			throw FileException(3, "Ошибка записи в файл", file.fileName());
	}
	out.flush();
	file.resize(file.size() - 2); //удалить последний перенос строки
	file.close();
}
void checkLogin(QString login); //функция проверки логина
void checkPassword(QString password); //функция проверки пароля
void checkName(QString name); //функция проверки имени
void checkDate(QString date); //функция проверки даты
void checkTime(QString time); //функция проверки времени
void checkContacts(QString contacts); //функция проверки номера телефона
void checkAdress(QString adress);  //функция проверки адреса
#endif // FUNCTIONS_H
