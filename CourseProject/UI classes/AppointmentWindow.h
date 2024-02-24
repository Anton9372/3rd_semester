//класс окна записи на прием к врачу
#ifndef APPOINTMENTWINDOW_H
#define APPOINTMENTWINDOW_H
#include "algorithm.h"
#include <QDialog>
#include "tree.h"
#include "Appointment.h"
#include <QMap>
#include "Doctor.h"
#include "Patient.h"
#include "User.h"
#include <QMessageBox>
#include <QFontDatabase>
namespace Ui {
	class AppointmentWindow;
}
class AppointmentWindow : public QDialog
{
	Q_OBJECT
signals:
	void exit(Tree<Appointment>& apps);     //сигнал выхода из окна
public:
	AppointmentWindow(int id, Tree<User>& users, QMap<int, Doctor>& doctors, Tree<Appointment>& appointments,
		QMap<int, QString>& services, QWidget* parent = nullptr);
	~AppointmentWindow();
	//метод заполнения списка текущих записей к врачам
	void fillAppList(int id, Tree<User>& users, QMap<int, Doctor>& doctors, Tree<Appointment>& appointments,
		QMap<int, QString>& services);
private slots:
	//методы нажатия на кнопки
	void on_deleteAppButton_clicked();
	void on_exitButton_clicked();
	void on_cancelButton_clicked();
	void on_choiceButton_clicked();
	void on_appButton_clicked();
private:
	Ui::AppointmentWindow* ui;
	int id;                         //ID пациента
	int flag;                       //флаг для отмены последнего действия
	Tree<User> users;               //контейнер с данными пользователей
	QMap<int, Doctor> doctors;      //контейнер с данными врачей
	Tree<Appointment> appointments; //контейнер с данными о записях к врачам
	QMap<int, QString> services;    //контейнер с данными о предоствляемых услугах
	QMap<int, Appointment> map;     //контейнер с данными о записях текущего пациента
};
#endif // APPOINTMENTWINDOW_H
