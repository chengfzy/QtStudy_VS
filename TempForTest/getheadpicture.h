#ifndef GETHEADPICTURE_H
#define GETHEADPICTURE_H

#include <QWidget>

namespace Ui {
class GetHeadPicture;
}

class GetHeadPicture : public QWidget
{
    Q_OBJECT

public:
    explicit GetHeadPicture(QWidget *parent,QString path);
    ~GetHeadPicture();

private slots:
	void on_pushButton_clicked();
	void on_pushButtton_2_clicked();

private:
    Ui::GetHeadPicture *ui;
	QString m_path;
};

#endif // GETHEADPICTURE_H
