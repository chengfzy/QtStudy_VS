#ifndef PICTUREEDIT_H
#define PICTUREEDIT_H

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QStandardPaths>
#include <QPainter>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QScreen>

#include "ui_pictureedit.h"

class CutDialog;
class PhotoShotDialog;

class PictureEdit : public QMainWindow
{
	Q_OBJECT

public:
	PictureEdit(QWidget *parent = 0);
	~PictureEdit();
	void loadPicture();

private slots:
	void on_pushButton_clicked();

private:
	Ui::PictureEditClass ui;
	QPixmap pic;
	QPixmap scaledPix;
	CutDialog *dialog;
	PhotoShotDialog *pdialog;
};

#endif // PICTUREEDIT_H
