//����� ���� ����������� ������������
#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H
#include <QDialog>
#include <QMap>
#include <QMessageBox>
#include "tree.h"
#include "filestream.h"
#include "FUNCTIONS.h"
#include "User.h"
#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"
#include "Message.h"
#include "Diagnosis.h"
#include "Analysis.h"
#include "exception.h"
#include "registrwindow.h"
#include "patientwindow.h"
#include "doctorwindow.h"
namespace Ui {
	class AuthWindow;
}
class AuthWindow : public QDialog
{
	Q_OBJECT
signals:
	void exit(Tree<User>& users);    //������ ������ �� ����
public:
	AuthWindow(Tree<User>& users, QMap<int, Doctor>& doctors, QMap<int, QString>& services, QWidget* parent = nullptr);
	~AuthWindow();
	void updateUsers(Patient& patient); //����� ���������� ������������
private slots:
	void on_loginButton_clicked();
	void on_regButton_clicked();
private:
	User user;                      //������������
	//���������� � �������
	Tree<User> users;
	QMap<int, Doctor> doctors;
	QMap<int, Patient> patients;
	QMap<int, QString> services;
	Tree<Message> messages;
	Tree<Diagnosis> diagnoses;
	Tree<Analysis> analyses;
	Tree<Appointment> appointments;
	Ui::AuthWindow* ui;             //����
	RegistrWindow* ui_registr;      //���� �����������
	PatientWindow* ui_patientWindow;//���� ��������
	DoctorWindow* ui_doctorWindow;  //���� �������
};
#endif // AUTHWINDOW_H
