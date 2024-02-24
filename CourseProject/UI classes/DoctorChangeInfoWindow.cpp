#include "doctorchangeinfowindow.h"
#include "ui_doctorchangeinfowindow.h"
DoctorChangeInfoWindow::DoctorChangeInfoWindow(Doctor& doctor, QWidget* parent) :
	doctor(doctor), QDialog(parent), ui(new Ui::DoctorChangeInfoWindow)
{
	ui->setupUi(this);
	setWindowTitle("�������� ������ ����������");
	resize(850, 650);
	//���������� � ���� ������� ����
	ui->pass1LineEdit->setText(doctor.getPassword());
	ui->pass2LineEdit->setText(doctor.getPassword());
	ui->nameLineEdit->setText(doctor.getName());
	ui->contactsLineEdit->setText(doctor.getContacts());
	ui->cabinetLineEdit->setText(QString::number(doctor.getCabinet()));
}
DoctorChangeInfoWindow::~DoctorChangeInfoWindow()
{
	delete ui;
}
void DoctorChangeInfoWindow::on_saveButton_clicked()
{
	//��������� ��������� ������
	try
	{
		checkPassword(ui->pass1LineEdit->text());
		checkName(ui->nameLineEdit->text());
		checkContacts(ui->contactsLineEdit->text());
	}
	catch (InputException& e)
	{
		QMessageBox::critical(this, e.getType(), e.getMessage());
		return;
	}
	//��������� ��������� ������
	int choice = doctor.changeInfo(ui->pass1LineEdit->text(), ui->pass2LineEdit->text(), ui->nameLineEdit->text(),
		ui->contactsLineEdit->text(), ui->cabinetLineEdit->text());
	if (choice == -1)
		QMessageBox::critical(this, "��������� ������", "������ �� ���������");
	if (choice == 1)
	{
		QMessageBox::information(this, "��������� ������", "������ �������� �������");
		this->close();
		emit save(doctor);  //����� �� ����
	}
}
