#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <QMap>
#include <QTextStream>
#include <QFile>
#include <QTextCodec>
#include "tree.h"
#include "exception.h"
//������� ���������� ������ �� ����� � ���������
template <typename T>
void fill_map_cont(QMap<int, T>& map, const QString& filename)
{
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		throw FileException(11, "������ ��� �������� �����", filename); //��������� ���������
	QTextStream in(&file);
	in.setCodec(QTextCodec::codecForName("UTF-8"));
	while (!in.atEnd())     //���� �� ����� �����
	{
		int id;
		T obj;
		in >> id >> obj;    //������� ID ������������ � ������
		if (in.status() != QTextStream::Ok)
			throw InputException(2, "������ ������ �� �����", "������ �����");
		map.insert(id, obj);//�������� � ���������
	}
	file.close();
}
//������� ���������� ������ �� ����� � ���������
void fill_map_cont(QMap<int, QString>& map, const QString& filename);

//������� ������ ������ �� ���������� � ����
template <typename T>
void write_file_map_cont(QMap<int, T>& map, const QString& filename)
{
	QFile file(filename);
	if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
		throw FileException(11, "������ ��� �������� �����", filename); //��������� ���������
	QTextStream out(&file);
	out.setCodec(QTextCodec::codecForName("UTF-8"));
	for (auto it = map.begin(), ite = map.end(); it != ite; ++it)       //������ �� ����������
	{
		out.setFieldAlignment(QTextStream::AlignLeft);
		out.setFieldWidth(3);
		//������ ������
		out << it.key();
		out << it.value() << '\n';
		if (out.status() != QTextStream::Ok)
			throw FileException(3, "������ ������ � ����", file.fileName());
	}
	out.flush();
	file.resize(file.size() - 2); //������� ��������� ������� ������
	file.close();
}
void checkLogin(QString login); //������� �������� ������
void checkPassword(QString password); //������� �������� ������
void checkName(QString name); //������� �������� �����
void checkDate(QString date); //������� �������� ����
void checkTime(QString time); //������� �������� �������
void checkContacts(QString contacts); //������� �������� ������ ��������
void checkAdress(QString adress);  //������� �������� ������
#endif // FUNCTIONS_H
