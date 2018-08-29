#include "pictureedit.h"
#include "cutdialog.h"
#include <QDebug>

#include "PhotoShotDialog.h"

PictureEdit::PictureEdit(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.pushButton->setText("Cut");

	//导入图片
	loadPicture();

	//该类为剪切框
	pdialog = new PhotoShotDialog(ui.label);
	pdialog->show();

}

PictureEdit::~PictureEdit()
{

}

//这里导入原图
void PictureEdit::loadPicture()
{
	//这里是原图的地址
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



//点击Cut按钮后会截取相应区域		
void PictureEdit::on_pushButton_clicked()
{
	QScreen *screen = QGuiApplication::primaryScreen();
	//getShotGeometry（）方法取出剪切后的图像
	QPixmap pix = scaledPix.copy(pdialog->getShotGeometry());
	//剪切出的图片的保存地址
	pix.save("C:/Users/dana/Desktop/1.png","png");
}

