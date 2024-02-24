#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget* parent) : users(2), QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setWindowTitle("Добро пожаловать");
	resize(850, 650);   //установить начальный размер окна
	FileStream fs;      //создать файловый поток
	//считать данные из файлов в контейнеры
	try
	{
		fs.open("C:\\Qt\\projects\\textFiles\\user_demo.txt", 1);
		fs.read(users);
		fs.close();
		fill_map_cont<Doctor>(doctors, "C:\\Qt\\projects\\textFiles\\doctor_demo.txt");
		fill_map_cont(services, "C:\\Qt\\projects\\textFiles\\service.txt");
	}
	catch (FileException& e)
	{
		QMessageBox::critical(this, "Непредвиденная ошибка", "Ошибка работы с файлами");
		e.whatFile();
		QCoreApplication::exit(1);
	}
}
MainWindow::~MainWindow()
{
	delete ui;
}
void MainWindow::updateConts(Tree<User>& users)
{
	this->users.copyTree(users);    //обновить контейнер
}
void MainWindow::on_loginButton_clicked()
{
	ui_auth = new AuthWindow(users, doctors, services);                     //создать окно регистрации
	//связать сигнал выхода из окна регистрации с обновлением контейнера
	connect(ui_auth, &AuthWindow::exit, this, &MainWindow::updateConts);
	//связать сигнал выхода из окна регистрации с показом начального окна
	connect(ui_auth, &AuthWindow::exit, this, &MainWindow::show);
	this->close();                                                          //закрыть начальное окно
	ui_auth->show();                                                        //показать окно регистрации
}
void MainWindow::on_viewDoctorsButton_clicked()
{
	label1 = new ViewDoctorsLabel(users, doctors, services);    //создать список врачей
	label1->show();                                             //показать список врачей
}
void MainWindow::on_viewServicesButton_clicked()
{
	label2 = new ViewServicesLabel(services);                   //создать список услуг
	label2->show();                                             //показать
}
