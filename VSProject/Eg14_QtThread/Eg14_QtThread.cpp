#include "Eg14_QtThread.h"

using namespace std;


Eg14_QtThread::Eg14_QtThread(QWidget *parent)
	: QMainWindow(parent)
	, m_nValue(0), m_bValueChanged(false)
{
	m_pTextEdit = new QTextEdit(this);	
	m_pLabel = new QLabel(this);
	m_pLabel->setText(tr("%1 / %2").arg(0).arg(200));

	m_pSlider = new QSlider(Qt::Horizontal, this);
	m_pSlider->setRange(0, 200);

	//main layout
	QVBoxLayout* pMainLayout = new QVBoxLayout(this);
	pMainLayout->addWidget(m_pTextEdit);
	pMainLayout->addWidget(m_pLabel);
	pMainLayout->addWidget(m_pSlider);

	//main widget
	QWidget* mainWidget = new QWidget(this);
	mainWidget->setLayout(pMainLayout);
	setCentralWidget(mainWidget);

	//actions
	connect(m_pSlider, &QSlider::valueChanged, this, &Eg14_QtThread::changeValue);

	//m_pThread = new std::thread(&Eg14_QtThread::updateData, this);

	//myThread = std::thread(&Eg14_QtThread::updateData, this);
	//myThread.detach();
	

	m_pHandleData = new HandleData(&m_nValue, &m_bValueChanged, &m_mutex, &m_dataChangedCondition);
	m_pThread = new QThread();
	m_pHandleData->moveToThread(m_pThread);
	connect(m_pThread, &QThread::started, m_pHandleData, &HandleData::compute);
	connect(m_pHandleData, &HandleData::gotResult, this, &Eg14_QtThread::updateData);

}


void Eg14_QtThread::changeValue(int value)
{
	m_pLabel->setText(tr("%1 / %2").arg(value).arg(m_pSlider->maximum()));
	
	////std::unique_lock<std::mutex> myLock(m_mutex);
	//m_nValue = value;
	//m_bValueChanged = true;
	////m_conditionVar.notify_all();

	//updateData();
	
	m_mutex.lock();
	m_nValue = value;
	m_dataChangedCondition.notify_all();
	m_bValueChanged = true;
	m_mutex.unlock();

	if (!m_pThread->isRunning())
		m_pThread->start();
}

void Eg14_QtThread::updateData(int result)
{
	m_pTextEdit->setText(tr("Update Data = %1").arg(result));

	////while (true)
	//{
	//	//std::unique_lock<std::mutex> myLock(m_mutex);
	//	//while (!m_bValueChanged)
	//	//	m_conditionVar.wait(myLock);

	//	Sleep(2000);
	//	m_mutex.lock();
	//	m_pTextEdit->setText(tr("Update Data = %1").arg(m_nValue));
	//	m_mutex.unlock();
	//	Sleep(100);
	//}
}
