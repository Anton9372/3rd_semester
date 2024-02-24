//класс добавления расписания врача
#ifndef SHEDULEWINDOW_H
#define SHEDULEWINDOW_H
#include <QDialog>
#include <QDateTime>
#include <QMessageBox>
#include "Doctor.h"
#include "Appointment.h"
#include "tree.h"
#include "algorithm.h"
#include "FUNCTIONS.h"
#include "exception.h"
namespace Ui {
	class sheduleWindow;
}
class sheduleWindow : public QDialog
{
	Q_OBJECT
signals:
	void exit(Tree<Appointment>& apps);     //выход из окна
public:
	sheduleWindow(Doctor& doctor, Tree<Appointment>& appointments, QWidget* parent = nullptr);
	~sheduleWindow();
private slots:
	void on_saveButton_clicked();
private:
	Ui::sheduleWindow* ui;
	Doctor doctor;                      //доктор
	Tree<Appointment> appointments;     //контейнер с расписанием
};
#endif // SHEDULEWINDOW_H
