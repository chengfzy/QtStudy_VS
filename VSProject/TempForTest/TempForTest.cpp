#include "TempForTest.h"

TempForTest::TempForTest(QWidget *parent)
	: QMainWindow(parent)
{
	label = new QLabel("Range: ", this);
	slider = new QSlider(Qt::Horizontal, this);

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(label);
	mainLayout->addWidget(slider);
	mainLayout->addStretch(1);

	QWidget* mainWidget = new QWidget(this);
	mainWidget->setLayout(mainLayout);

	setCentralWidget(mainWidget);

	//actions
	connect(slider, &QSlider::valueChanged, this, &TempForTest::changeLabel);
}

void TempForTest::changeLabel(int value)
{
	//label->setText(QString("Range(%1 / %2):").arg(value).arg(slider->maximum()));

	QString str;
	str.sprintf("%12s: %d\n"
		"%12s: %d\n"
		"%12s: %d",
		"ABC", 1234, "ABCDEFGH", 12345678, "abcdefljiji", 1234567890);
	label->setText(str);	
}
