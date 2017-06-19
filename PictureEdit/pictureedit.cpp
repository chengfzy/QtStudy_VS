#include "pictureedit.h"
#include "cutdialog.h"
#include <QDebug>

#include "PhotoShotDialog.h"

PictureEdit::PictureEdit(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.pushButton->setText("Cut");

	//����ͼƬ
	loadPicture();

	//����Ϊ���п�
	pdialog = new PhotoShotDialog(ui.label);
	pdialog->show();

}

PictureEdit::~PictureEdit()
{

}

//���ﵼ��ԭͼ
void PictureEdit::loadPicture()
{
	//������ԭͼ�ĵ�ַ
	pic.load("F:\\Code\\Qt Study\\QtStudy\\TempForTest\\1.png");
	pic.scaledToWidth(100);
	pic.scaledToHeight(200);
	if(!pic.isNull())
	{	
		ui.label->setText("hahaha");
		scaledPix = pic.scaled(ui.label->width(),ui.label->height());
		ui.label->setPixmap(scaledPix);
	}

}



//���Cut��ť����ȡ��Ӧ����		
void PictureEdit::on_pushButton_clicked()
{
	QScreen *screen = QGuiApplication::primaryScreen();
	//getShotGeometry��������ȡ�����к��ͼ��
	QPixmap pix = scaledPix.copy(pdialog->getShotGeometry());
	//���г���ͼƬ�ı����ַ
	pix.save("C:/Users/dana/Desktop/1.png","png");
}

