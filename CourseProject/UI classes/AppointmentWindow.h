//����� ���� ������ �� ����� � �����
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
	void exit(Tree<Appointment>& apps);     //������ ������ �� ����
public:
	AppointmentWindow(int id, Tree<User>& users, QMap<int, Doctor>& doctors, Tree<Appointment>& appointments,
		QMap<int, QString>& services, QWidget* parent = nullptr);
	~AppointmentWindow();
	//����� ���������� ������ ������� ������� � ������
	void fillAppList(int id, Tree<User>& users, QMap<int, Doctor>& doctors, Tree<Appointment>& appointments,
		QMap<int, QString>& services);
private slots:
	//������ ������� �� ������
	void on_deleteAppButton_clicked();
	void on_exitButton_clicked();
	void on_cancelButton_clicked();
	void on_choiceButton_clicked();
	void on_appButton_clicked();
private:
	Ui::AppointmentWindow* ui;
	int id;                         //ID ��������
	int flag;                       //���� ��� ������ ���������� ��������
	Tree<User> users;               //��������� � ������� �������������
	QMap<int, Doctor> doctors;      //��������� � ������� ������
	Tree<Appointment> appointments; //��������� � ������� � ������� � ������
	QMap<int, QString> services;    //��������� � ������� � �������������� �������
	QMap<int, Appointment> map;     //��������� � ������� � ������� �������� ��������
};
#endif // APPOINTMENTWINDOW_H
