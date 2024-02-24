//класс окна пациента
#ifndef PATIENTWINDOW_H
#define PATIENTWINDOW_H
#include "Patient.h"
#include <QMap>
#include "tree.h"
#include "patientchangeinfowindow.h"
#include "Doctor.h"
#include "Message.h"
#include "Analysis.h"
#include "Diagnosis.h"
#include "Appointment.h"
#include "labels.h"
#include "filestream.h"
#include "FUNCTIONS.h"
#include "algorithm.h"
#include "appointmentwindow.h"
#include "exception.h"
#include <QDialog>
namespace Ui {
	class PatientWindow;
}
class PatientWindow : public QDialog
{
	Q_OBJECT
signals:
	void exit(Tree<User>& tree);    //выход из окна
public:
	PatientWindow(User& user, Tree<User>& users, QMap<int, Patient>& patients, QMap<int, Doctor>& doctors, QMap<int, QString>& services, Tree<Message>& messages, Tree<Diagnosis>& diagnoses, Tree<Analysis>& analyses, Tree<Appointment>& appointments, QWidget* parent = nullptr);
	~PatientWindow();
	void updatePatient(const Patient& patient); //обновить данные пациента
	void updateApps(Tree<Appointment>& apps);   //обновить расписание приемов к врачам
private slots:
	void on_viewMedCardButton_clicked();
	void on_appointmentButton_clicked();
	void on_viewDoctorsButton_clicked();
	void on_viewServicesButton_clicked();
	void on_changeInfoButton_clicked();
	void on_viewMessagesButton_clicked();
	void on_exitButton_clicked();
private:
	Patient patient;                //пациент
	//контейнеры с данными
	Tree<User> users;
	QMap<int, Patient> patients;
	QMap<int, Doctor> doctors;
	QMap<int, QString> services;
	Tree<Message> messages;
	Tree<Diagnosis> diagnoses;
	Tree<Analysis> analyses;
	Tree<Appointment> appointments;
	Ui::PatientWindow* ui;
	PatientChangeInfoWindow* ui_changeInfo; //окно изменения личной информации
	AppointmentWindow* ui_appointment;      //окно записи к врачу
	ViewDoctorsLabel* label1;       //список докторов
	ViewServicesLabel* label2;      //список услуг
	ViewMessagesLabel* label3;      //список входящих сообщений
	ViewMedCardLabel* label4;       //медицинская карточка
};
#endif // PATIENTWINDOW_H
