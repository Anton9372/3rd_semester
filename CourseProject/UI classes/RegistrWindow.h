//окно регистрации пользователя
#ifndef REGISTRWINDOW_H
#define REGISTRWINDOW_H
#include <QDialog>
#include <QMessageBox>
#include "tree.h"
#include "User.h"
#include "Patient.h"
#include "FUNCTIONS.h"
namespace Ui {
	class RegistrWindow;
}
class RegistrWindow : public QDialog
{
	Q_OBJECT
signals:
	void isRegistr(Patient& patient);   //сигнал успешной регистрации
	void exit();
public:
	RegistrWindow(Tree<User>& users, QMap<int, Patient>& patients, QWidget* parent = nullptr);
	~RegistrWindow();
private slots:
	void on_registrButton_clicked();
	void on_cancelButton_clicked();
private:
	Ui::RegistrWindow* ui;  //окно
	//контейнеры с данными
	Tree<User> users;
	QMap<int, Patient> patients;
};
#endif // REGISTRWINDOW_H
