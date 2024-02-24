//����� ���� �������
#ifndef DOCTORWINDOW_H
#define DOCTORWINDOW_H
#include <QDialog>
#include "Doctor.h"
#include "Patient.h"
#include <QMap>
#include "tree.h"
#include "Message.h"
#include "Diagnosis.h"
#include "Analysis.h"
#include "Appointment.h"
#include "FUNCTIONS.h"
#include "filestream.h"
#include "labels.h"
#include "doctorchangeinfowindow.h"
#include "shedulewindow.h"
#include "medcardwindow.h"
#include "algorithm.h"
#include "exception.h"
namespace Ui {
	class DoctorWindow;
}
class DoctorWindow : public QDialog
{
	Q_OBJECT
signals:
	void exit(Tree<User>& users);   //������ ������ �� ����
public:
	DoctorWindow(User& user, Tree<User>& users, QMap<int, Patient>& patients, QMap<int, Doctor>& doctors, QMap<int, QString>& services, Tree<Message>& messages, Tree<Diagnosis>& diagnoses, Tree<Analysis>& analyses, Tree<Appointment>& appointments, QWidget* parent = nullptr);
	~DoctorWindow();
	void updateDoctor(const Doctor& doctor);    //�������� ������ �������
	void updateApps(Tree<Appointment>& apps);   //�������� ���������� �����
	//�������� ������ � ��� ��������
	void updateConts(Tree<Message>& messages, Tree<Diagnosis>& diagnoses, Tree<Analysis>& analyses);
private slots:
	void on_changeInfoButton_clicked();
	void on_exitButton_clicked();
	void on_addRecordButton_clicked();
	void on_checkSchedButton_clicked();
	void on_changeSchedButton_clicked();
private:
	Doctor doctor;                  //������
	//���������� � �������
	Tree<User> users;
	QMap<int, Patient> patients;
	QMap<int, Doctor> doctors;
	QMap<int, QString> services;
	Tree<Message> messages;
	Tree<Diagnosis> diagnoses;
	Tree<Analysis> analyses;
	Tree<Appointment> appointments;
	Ui::DoctorWindow* ui;           //����
	DoctorChangeInfoWindow* ui_changeInfo;  //���� ��������� ������ ������
	sheduleWindow* ui_shedule;              //���� ��������� ���������� �����
	MedCardWindow* ui_medCard;              //���� ������ � �������� ��������
	ViewScheduleLabel* label;               //���������� �������
};
#endif // DOCTORWINDOW_H
