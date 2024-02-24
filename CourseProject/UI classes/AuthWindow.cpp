#include "authwindow.h"
#include "ui_authwindow.h"
AuthWindow::AuthWindow(Tree<User>& users, QMap<int, Doctor>& doctors, QMap<int, QString>& services, QWidget* parent) :
	users(users), doctors(doctors), services(services), messages(3), diagnoses(3), analyses(3), appointments(4), QDialog(parent), ui(new Ui::AuthWindow)
{
	ui->setupUi(this);
	setWindowTitle("���� � �������");
	resize(850, 650);
	//������� ������ � �������� � ���������
	fill_map_cont<Patient>(patients, "C:\\Qt\\projects\\textFiles\\patient_demo.txt");
}
AuthWindow::~AuthWindow()
{
	delete ui;
}
void AuthWindow::updateUsers(Patient& patient)
{
	users.push(patient);                        //�������� ������ ������������
	patients.insert(patient.getId(), patient);  //�������� ������ ��������
}
void AuthWindow::on_loginButton_clicked()
{
	int choice = user.authorisation(users, ui->loginEdit->text(), ui->passEdit->text()); //������� ����� �����������
	//���� ���� ��������
	if (choice == 1)
	{
		QMessageBox::information(this, "����������� ������������", "���� �������� �������");
		this->close();
		//������� ������ � ����������
		FileStream fs;
		try
		{
			fs.open("C:\\Qt\\projects\\textFiles\\message_demo.txt", 1);
			fs.read(messages);
			fs.close();
			fs.open("C:\\Qt\\projects\\textFiles\\diagnosis_demo.txt", 1);
			fs.read(diagnoses);
			fs.close();
			fs.open("C:\\Qt\\projects\\textFiles\\analysis_demo.txt", 1);
			fs.read(analyses);
			fs.close();
			fs.open("C:\\Qt\\projects\\textFiles\\appointment_demo.txt", 1);
			fs.read(appointments);
			fs.close();
		}
		catch (FileException& e)
		{
			QMessageBox::critical(this, "�������������� ������", "������ ������ � �������");
			e.whatFile();
			QCoreApplication::exit(1);
		}
		//���� ������������ - �������
		if (user.getRole() == 'p')
		{
			//������� ���� ��������, ������� ������ ������ �� ����, �������� ���� ��������
			ui_patientWindow = new PatientWindow(user, users, patients, doctors, services, messages, diagnoses,
				analyses, appointments);
			connect(ui_patientWindow, &PatientWindow::exit, this, &AuthWindow::exit);
			ui_patientWindow->show();
		}
		//���� ������������ - ����
		if (user.getRole() == 'd')
		{
			//������� ���� �������, ������� ������ ������ �� ����, �������� ���� �������
			ui_doctorWindow = new DoctorWindow(user, users, patients, doctors, services, messages, diagnoses, analyses, appointments);
			connect(ui_doctorWindow, &DoctorWindow::exit, this, &AuthWindow::exit);
			ui_doctorWindow->show();
		}
	}
	else if (choice == 0)    //���� ������ ��������
		QMessageBox::warning(this, "����������� ������������", "������ �� ������");
	else                    //���� ������������ �� ����������
		QMessageBox::critical(this, "����������� ������������", "������������ �� ������");
}
void AuthWindow::on_regButton_clicked()
{
	//������� ���� �����������
	ui_registr = new RegistrWindow(users, patients);
	//������� ����� �� ���� ����������� � ������� ���� ����������� � ���������� ������ ������������ � �������
	connect(ui_registr, &RegistrWindow::exit, this, &AuthWindow::show);
	connect(ui_registr, &RegistrWindow::isRegistr, this, &AuthWindow::show);
	connect(ui_registr, &RegistrWindow::isRegistr, this, &AuthWindow::updateUsers);
	this->close();      //������� ���� �����������
	ui_registr->show(); //�������� ���� �����������
}
