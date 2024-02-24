//окно изменения личной информации доктора
#ifndef DOCTORCHANGEINFOWINDOW_H
#define DOCTORCHANGEINFOWINDOW_H
#include <QDialog>
#include <QMap>
#include <QMessageBox>
#include "Doctor.h"
#include "tree.h"
#include "exception.h"
#include "FUNCTIONS.h"
namespace Ui {
	class DoctorChangeInfoWindow;
}
class DoctorChangeInfoWindow : public QDialog
{
	Q_OBJECT
signals:
	void save(const Doctor& doctor);    //выход из окна
public:
	DoctorChangeInfoWindow(Doctor& doctor, QWidget* parent = nullptr);
	~DoctorChangeInfoWindow();
private slots:
	void on_saveButton_clicked();
private:
	Ui::DoctorChangeInfoWindow* ui; //окно
	Doctor doctor;                  //доктор
};
#endif // DOCTORCHANGEINFOWINDOW_H
