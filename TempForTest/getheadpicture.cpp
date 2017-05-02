#include "getheadpicture.h"
#include "ui_getheadpicture.h"

GetHeadPicture::GetHeadPicture(QWidget *parent, QString path) :
    QWidget(parent),m_path(path),
    ui(new Ui::GetHeadPicture)
{
    ui->setupUi(this);
}

GetHeadPicture::~GetHeadPicture()
{
    delete ui;
}

void GetHeadPicture::on_pushButton_clicked()
{
	
}
void GetHeadPicture::on_pushButtton_2_clicked()
{

}