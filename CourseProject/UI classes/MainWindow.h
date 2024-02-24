//класс начального окна программы
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMap>
#include "labels.h"
#include "authwindow.h"
#include "tree.h"
#include "User.h"
#include "FUNCTIONS.h"
#include "filestream.h"
#include "exception.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();
	void updateConts(Tree<User>& users);            //метод обновления контейнера с пользователями
private slots:
	void on_loginButton_clicked();
	void on_viewDoctorsButton_clicked();
	void on_viewServicesButton_clicked();
private:
	Tree<User> users;               //контейнер с данными пользователей
	QMap<int, Doctor> doctors;      //контейнер с данными врачей
	QMap<int, QString> services;    //контейнер с данными пациентов
	Ui::MainWindow* ui;             //текущее окно
	AuthWindow* ui_auth;            //окно регистрации
	ViewDoctorsLabel* label1;       //список докторов
	ViewServicesLabel* label2;      //список предоставляемых услуг
};
#endif // MAINWINDOW_H
