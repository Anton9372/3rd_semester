#include "authwindow.h"
#include "ui_authwindow.h"
AuthWindow::AuthWindow(Tree<User>& users, QMap<int, Doctor>& doctors, QMap<int, QString>& services, QWidget* parent) :
	users(users), doctors(doctors), services(services), messages(3), diagnoses(3), analyses(3), appointments(4), QDialog(parent), ui(new Ui::AuthWindow)
{
	ui->setupUi(this);
	setWindowTitle("Вход в систему");
	resize(850, 650);
	//считать данные о пацентах в контейнер
	fill_map_cont<Patient>(patients, "C:\\Qt\\projects\\textFiles\\patient_demo.txt");
}
AuthWindow::~AuthWindow()
{
	delete ui;
}
void AuthWindow::updateUsers(Patient& patient)
{
	users.push(patient);                        //добавить данные пользователя
	patients.insert(patient.getId(), patient);  //добавить данные пациента
}
void AuthWindow::on_loginButton_clicked()
{
	int choice = user.authorisation(users, ui->loginEdit->text(), ui->passEdit->text()); //вызвать метод авторизации
	//если вход выполнен
	if (choice == 1)
	{
		QMessageBox::information(this, "Авторизация пользователя", "Вход выполнен успешно");
		this->close();
		//считать данные в контейнеры
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
			QMessageBox::critical(this, "Непредвиденная ошибка", "Ошибка работы с файлами");
			e.whatFile();
			QCoreApplication::exit(1);
		}
		//если пользователь - пациент
		if (user.getRole() == 'p')
		{
			//создать окно пациента, связать сигнал выхода из окна, показать окно пациента
			ui_patientWindow = new PatientWindow(user, users, patients, doctors, services, messages, diagnoses,
				analyses, appointments);
			connect(ui_patientWindow, &PatientWindow::exit, this, &AuthWindow::exit);
			ui_patientWindow->show();
		}
		//если пользователь - врач
		if (user.getRole() == 'd')
		{
			//создать окно доктора, связать сигнал выхода из окна, показать окно доктора
			ui_doctorWindow = new DoctorWindow(user, users, patients, doctors, services, messages, diagnoses, analyses, appointments);
			connect(ui_doctorWindow, &DoctorWindow::exit, this, &AuthWindow::exit);
			ui_doctorWindow->show();
		}
	}
	else if (choice == 0)    //если пароль неверный
		QMessageBox::warning(this, "Авторизация пользователя", "Пароль не верный");
	else                    //если пользователь не существует
		QMessageBox::critical(this, "Авторизация пользователя", "Пользователь не найден");
}
void AuthWindow::on_regButton_clicked()
{
	//создать окно регистрации
	ui_registr = new RegistrWindow(users, patients);
	//связать выход из окна регистрации с показом окна авторизации и добавления нового пользователя в систему
	connect(ui_registr, &RegistrWindow::exit, this, &AuthWindow::show);
	connect(ui_registr, &RegistrWindow::isRegistr, this, &AuthWindow::show);
	connect(ui_registr, &RegistrWindow::isRegistr, this, &AuthWindow::updateUsers);
	this->close();      //закрыть окно авторизации
	ui_registr->show(); //показать окно регистрации
}
