#pragma once
#include <QWidget>
#include "cutdialog.h"

class CutDialog;

class PhotoShotDialog :public QWidget
{
	Q_OBJECT
private:
	CutDialog *dialog;

public:
	explicit PhotoShotDialog(QWidget *parent = 0);

	~PhotoShotDialog(void);
	QRect getShotGeometry(){return dialog->geometry();}



protected:
	void paintEvent(QPaintEvent *e);
};

