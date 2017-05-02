#include "Eg05_ImageCrop.h"

Eg05_ImageCrop::Eg05_ImageCrop(QWidget *parent)
	: QWidget(parent)
{
	m_imageCropper = new ImageCropper(this);
	m_imageCropper->resize(600, 600);
	m_imageCropper->setProportion(QSize(4, 3));
	m_imageCropper->setImage(QPixmap(tr(":/image/picture")));
	m_imageCropper->setBackgroundColor(Qt::lightGray);
	m_imageCropper->setCroppingRectBorderColor(Qt::magenta);

	QCheckBox* fixedProportionsCombo = new QCheckBox("Fix proportion to (4x3)", this);
	//connect(fixedProportionsCombo, SIGNAL(toggled(bool)), m_imageCropper, SLOT(setProportionFixed(bool)));
	// §¬§Ñ§Õ§â§Ú§â§à§Ó§Ñ§ä§î §Ó§í§Õ§Ö§Ý§Ö§ß§ß§å§ð §à§Ò§Ý§Ñ§ã§ä§î
	QPushButton* cropButton = new QPushButton("Crop", this);
	//connect(cropButton, SIGNAL(clicked()), this, SLOT(crop()));
	

	m_pImageLabel = new QLabel(this);
	m_pImageLabel->setPixmap(QPixmap(tr(":/image/picture")));

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(m_imageCropper);
	layout->addWidget(m_pImageLabel);
	layout->addWidget(fixedProportionsCombo);
	layout->addWidget(cropButton);
}
