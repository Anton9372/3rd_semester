//класс окна доктора
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
	void exit(Tree<User>& users);   //сигнал выхожа из окна
public:
	DoctorWindow(User& user, Tree<User>& users, QMap<int, Patient>& patients, QMap<int, Doctor>& doctors, QMap<int, QString>& services, Tree<Message>& messages, Tree<Diagnosis>& diagnoses, Tree<Analysis>& analyses, Tree<Appointment>& appointments, QWidget* parent = nullptr);
	~DoctorWindow();
	void updateDoctor(const Doctor& doctor);    //изменить данные доктора
	void updateApps(Tree<Appointment>& apps);   //добавить расписание врача
	//добавить записи в мед карточку
	void updateConts(Tree<Message>& messages, Tree<Diagnosis>& diagnoses, Tree<Analysis>& analyses);
private slots:
	void on_changeInfoButton_clicked();
	void on_exitButton_clicked();
	void on_addRecordButton_clicked();
	void on_checkSchedButton_clicked();
	void on_changeSchedButton_clicked();
private:
	Doctor doctor;                  //доктор
	//контейнеры с данными
	Tree<User> users;
	QMap<int, Patient> patients;
	QMap<int, Doctor> doctors;
	QMap<int, QString> services;
	Tree<Message> messages;
	Tree<Diagnosis> diagnoses;
	Tree<Analysis> analyses;
	Tree<Appointment> appointments;
	Ui::DoctorWindow* ui;           //окно
	DoctorChangeInfoWindow* ui_changeInfo;  //окно изменения личных данных
	sheduleWindow* ui_shedule;              //окно изменения расписания врача
	MedCardWindow* ui_medCard;              //окно записи в карточку пациента
	ViewScheduleLabel* label;               //расписание приемов
};
#endif // DOCTORWINDOW_H
