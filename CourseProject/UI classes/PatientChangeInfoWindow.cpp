#include "patientchangeinfowindow.h"
#include "ui_patientchangeinfowindow.h"
PatientChangeInfoWindow::PatientChangeInfoWindow(Patient& patient, QWidget* parent) :
	patient(patient), QDialog(parent), ui(new Ui::PatientChangeInfoWindow)
{
	ui->setupUi(this);
	setWindowTitle("�������� ������ ����������");
	resize(850, 650);
	//��������� ���� �������� �������
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
	//��������� ��������� ������
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
	//��������� ��������� ������
	int choice = patient.changeInfo(ui->pass1LineEdit->text(), ui->pass2LineEdit->text(), ui->nameLineEdit->text(),
		ui->contactsLineEdit->text(), ui->adressLineEdit->text());
	if (choice == -1)
		QMessageBox::critical(this, "��������� ������", "������ �� ���������");
	if (choice == 1)
	{
		QMessageBox::information(this, "��������� ������", "������ �������� �������");
		this->close();
		emit save(patient); //����� �� ����
	}
}
