#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets>
#include <QThread>
#include "HandleData.h"
#include <thread>
#include <mutex>
#include <condition_variable>

class Eg14_QtThread : public QMainWindow
{
	Q_OBJECT

public:
	Eg14_QtThread(QWidget *parent = Q_NULLPTR);


	void changeValue(int value);
	void updateData(int result);


private:
	int m_nValue;
	bool m_bValueChanged;

	HandleData* m_pHandleData;
	QThread* m_pThread;
	QMutex m_mutex;
	QWaitCondition m_dataChangedCondition;

	//std::thread* m_pThread;

	//std::thread myThread;
	//std::mutex m_mutex;
	//std::condition_variable m_conditionVar;

	QTextEdit* m_pTextEdit;
	QLabel* m_pLabel;
	QSlider* m_pSlider;
};
