#include "PhotoShotDialog.h"
#include "cutdialog.h"

PhotoShotDialog::PhotoShotDialog(QWidget *parent)
	:QWidget(parent)
{
	setWindowFlags(Qt::FramelessWindowHint);
	dialog = new CutDialog(this);
	dialog->show();
	setGeometry(0,0,parentWidget()->width(),parentWidget()->height());
}


PhotoShotDialog::~PhotoShotDialog(void)
{

}

void PhotoShotDialog::paintEvent(QPaintEvent *e)
{
	QPainterPath painterPath;
	QPainterPath p;
	p.addRect(x(),y(),rect().width(),rect().height());
	painterPath.addRect(dialog->geometry());
    QPainterPath drawPath =p.subtracted(painterPath);

	QPainter paint(this);
	paint.setOpacity(0.7);
	paint.fillPath(drawPath,QBrush(Qt::black));
}