#pragma once

#include <QObject>
#include <QtWidgets>
#include <QThread>

class HandleData : public QObject
{
	Q_OBJECT

public:
	HandleData(int* pData, bool* pDataChanged, QMutex* pMutex, QWaitCondition* pDataChangedCondition);
	~HandleData();

	int getData();
	void compute();

signals:
	void gotResult(int result) const;

private:
	int* m_pData;
	bool* m_pDataChanged;
	QMutex* m_pMutex;
	QWaitCondition* m_pDataChangedCondition;
};