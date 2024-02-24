//������ � ������ � ��������� �����������
#ifndef LABELS_H
#define LABELS_H
#include <QWidget>
#include <QLabel>
#include "tree.h"
#include "User.h"
#include "iter.h"
#include <QMap>
#include "Doctor.h"
#include "Message.h"
#include "Analysis.h"
#include "Diagnosis.h"
#include "Appointment.h"
#include "Patient.h"
#include "algorithm.h"
//����� ��������� ��������
class ViewDoctorsLabel : public QWidget {
public:
	ViewDoctorsLabel(Tree<User>& users, QMap<int, Doctor>& doctors, QMap<int, QString>& services, QWidget* parent = 0);
	~ViewDoctorsLabel();
private:
	QLabel* label;
};
//����� ��������� �����
class ViewServicesLabel : public QWidget {
public:
	ViewServicesLabel(QMap<int, QString>& services, QWidget* parent = 0);
	~ViewServicesLabel();
private:
	QLabel* label;
};
//����� ��������� �������� ���������
class ViewMessagesLabel : public QWidget {
public:
	ViewMessagesLabel(int id, Tree<User>& users, Tree<Message>& messages, QWidget* parent = 0);
	~ViewMessagesLabel();
private:
	QLabel* label;
	int id;         //ID ��������
};
//����� ��������� ����������� ��������
class ViewMedCardLabel : public QWidget {
public:
	ViewMedCardLabel(int id, Tree<User>& users, Tree<Diagnosis>& diagnoses, Tree<Analysis>& analyses, QMap<int, QString>& services, QWidget* parent = 0);
	~ViewMedCardLabel();
private:
	QLabel* label;
	int id;         //ID ��������
};
//����� ��������� ����������
class ViewScheduleLabel : public QWidget {
public:
	ViewScheduleLabel(int id, Tree<User>& users, QMap<int, QString>& services, Tree<Appointment>& appointments, QWidget* parent = 0);
	~ViewScheduleLabel();
private:
	QLabel* label;
	int id;         //ID �����
};
//����� ��������� ���������
class ViewPatientsLabel : public QWidget {
public:
	ViewPatientsLabel(Tree<User>& users, QMap<int, Patient>& patients, QWidget* parent = 0);
	~ViewPatientsLabel();
private:
	QLabel* label;
};
#endif // LABELS_H
