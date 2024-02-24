#include "doctorwindow.h"
#include "ui_doctorwindow.h"
DoctorWindow::DoctorWindow(User& user, Tree<User>& users, QMap<int, Patient>& patients, QMap<int, Doctor>& doctors, QMap<int, QString>& services,
	Tree<Message>& messages, Tree<Diagnosis>& diagnoses, Tree<Analysis>& analyses, Tree<Appointment>& appointments, QWidget* parent) :
	users(users), patients(patients), doctors(doctors), services(services), messages(messages), diagnoses(diagnoses), analyses(analyses),
	appointments(appointments), QDialog(parent), ui(new Ui::DoctorWindow),
	doctor(user.getId(), user.getRole(), user.getLogin(), user.getPassword(), user.getName(), user.getContacts())
{
	ui->setupUi(this);
	setWindowTitle("������� ����");
	resize(850, 650);
	//�������� � ������� ������ Doctor ������
	Doctor obj = doctors.value(user.getId());
	doctor.setExperience(obj.getExperience());
	doctor.setCabinet(obj.getCabinet());
	doctor.setServiceId(obj.getServiceId());
}
DoctorWindow::~DoctorWindow()
{
	delete ui;
}
void DoctorWindow::updateApps(Tree<Appointment>& apps)
{
	appointments.copyTree(apps);    //�������� ��������� � ������� � ����������
}

void DoctorWindow::updateConts(Tree<Message>& messages, Tree<Diagnosis>& diagnoses, Tree<Analysis>& analyses)
{
	//�������� ���������� � ������� � ����������� ��������
	this->messages.copyTree(messages);
	this->diagnoses.copyTree(diagnoses);
	this->analyses.copyTree(analyses);
}
void DoctorWindow::updateDoctor(const Doctor& doctor)
{
	//������� �� �������� ������� ������
	users.pop(this->doctor);
	doctors.remove(this->doctor.getId());
	//�������� ������� ������ Doctor
	this->doctor = doctor;
	//�������� ����� ������ � ����������
	users.push(doctor);
	doctors.insert(doctor.getId(), doctor);
}
void DoctorWindow::on_changeInfoButton_clicked()
{
	ui_changeInfo = new DoctorChangeInfoWindow(doctor); //������� ���� ��������� ������ ������
	//�������� ����� �� ���� ��������� � ������� �������� ���� � ���������� ������
	connect(ui_changeInfo, &DoctorChangeInfoWindow::save, this, &DoctorWindow::updateDoctor);
	connect(ui_changeInfo, &DoctorChangeInfoWindow::save, this, &DoctorWindow::show);
	this->close();
	ui_changeInfo->show();
}
void DoctorWindow::on_exitButton_clicked()
{
	FileStream fs;      //������� �������� �����
	Algorithm<User>::restructing(users, 1);     //����������� ������ �� ID ������������
	//�������� ������ �� ����������� � �����
	try
	{
		fs.open("C:\\Qt\\projects\\textFiles\\user_demo.txt", 2);
		fs.write(users.getRoot());
		fs.deleteLastNewLine();
		fs.close();
		fs.open("C:\\Qt\\projects\\textFiles\\message_demo.txt", 2);
		fs.write(messages.getRoot());
		fs.deleteLastNewLine();
		fs.close();
		fs.open("C:\\Qt\\projects\\textFiles\\analysis_demo.txt", 2);
		fs.write(analyses.getRoot());
		fs.deleteLastNewLine();
		fs.close();
		fs.open("C:\\Qt\\projects\\textFiles\\diagnosis_demo.txt", 2);
		fs.write(diagnoses.getRoot());
		fs.deleteLastNewLine();
		fs.close();
		fs.open("C:\\Qt\\projects\\textFiles\\appointment_demo.txt", 2);
		fs.write(appointments.getRoot());
		fs.deleteLastNewLine();
		fs.close();
		write_file_map_cont(patients, "C:\\Qt\\projects\\textFiles\\patient_demo.txt");
		write_file_map_cont(doctors, "C:\\Qt\\projects\\textFiles\\doctor_demo.txt");
	}
	catch (FileException& e)
	{
		QMessageBox::critical(this, "�������������� ������", "������ �� �����������");
		e.whatFile();
		QCoreApplication::exit(1);
	}
	this->close();
	emit exit(users);
}
void DoctorWindow::on_addRecordButton_clicked()
{
	//������� ���� ������ � �������� ��������
	ui_medCard = new MedCardWindow(this->doctor, users, doctors, patients, messages, diagnoses, analyses, services);
	//������� ����� �� ���� ������ � ������� �������� ���� � ����������� ����������� � �������
	connect(ui_medCard, &MedCardWindow::exit, this, &DoctorWindow::show);
	connect(ui_medCard, &MedCardWindow::exit, this, &DoctorWindow::updateConts);
	this->close();
	ui_medCard->show();
}
void DoctorWindow::on_checkSchedButton_clicked()
{
	//������� ������ � ����������� �����
	label = new ViewScheduleLabel(doctor.getId(), users, services, appointments);
	label->show();
}
void DoctorWindow::on_changeSchedButton_clicked()
{
	ui_shedule = new sheduleWindow(this->doctor, appointments); //������� ���� � ����������� ����������
	//������� ����� �� ���� ���������� � ������� �������� ���� � ����������� ����������� � �������
	connect(ui_shedule, &sheduleWindow::exit, this, &DoctorWindow::show);
	connect(ui_shedule, &sheduleWindow::exit, this, &DoctorWindow::updateApps);
	this->close();
	ui_shedule->show();
}
