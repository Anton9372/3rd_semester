#include "patientchangeinfowindow.h"
#include "ui_patientchangeinfowindow.h"
PatientChangeInfoWindow::PatientChangeInfoWindow(Patient& patient, QWidget* parent) :
	patient(patient), QDialog(parent), ui(new Ui::PatientChangeInfoWindow)
{
	ui->setupUi(this);
	setWindowTitle("Изменить личную информацию");
	resize(850, 650);
	//заполнить поля текущими данными
	ui->pass1LineEdit->setText(patient.getPassword());
	ui->pass2LineEdit->setText(patient.getPassword());
	ui->nameLineEdit->setText(patient.getName());
	ui->contactsLineEdit->setText(patient.getContacts());
	ui->adressLineEdit->setText(patient.getAdress());
}
PatientChangeInfoWindow::~PatientChangeInfoWindow()
{
	delete ui;
}
void PatientChangeInfoWindow::on_saveButton_clicked()
{
	//проверить введенные данные
	try
	{
		checkPassword(ui->pass1LineEdit->text());
		checkName(ui->nameLineEdit->text());
		checkAdress(ui->adressLineEdit->text());
		checkContacts(ui->contactsLineEdit->text());
	}
	catch (InputException& e)
	{
		QMessageBox::critical(this, e.getType(), e.getMessage());
		return;
	}
	//выполнить изменение данных
	int choice = patient.changeInfo(ui->pass1LineEdit->text(), ui->pass2LineEdit->text(), ui->nameLineEdit->text(),
		ui->contactsLineEdit->text(), ui->adressLineEdit->text());
	if (choice == -1)
		QMessageBox::critical(this, "Изменение данных", "Пароли не совпадают");
	if (choice == 1)
	{
		QMessageBox::information(this, "Изменение данных", "Данные изменены успешно");
		this->close();
		emit save(patient); //выйти из окна
	}
}
