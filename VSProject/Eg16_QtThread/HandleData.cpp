#include "HandleData.h"
#include <QtWidgets>

HandleData::HandleData(int* pData, bool* pDataChanged, QMutex* pMutex, QWaitCondition* pDataChangedCondition)
	: m_pData(pData), m_pDataChanged(pDataChanged), m_pMutex(pMutex), m_pDataChangedCondition(pDataChangedCondition)
{
}

HandleData::~HandleData()
{
}

int HandleData::getData()
{
	return *m_pData;
}

void HandleData::compute()
{
	while (true)
	{
		m_pMutex->lock();
		if (!*m_pDataChanged)
			m_pDataChangedCondition->wait(m_pMutex);
		*m_pDataChanged = false;
		m_pMutex->unlock();

		Sleep(2000);
		int value = *m_pData;
		int result = value;// *value;
		emit gotResult(result);
	}
}
