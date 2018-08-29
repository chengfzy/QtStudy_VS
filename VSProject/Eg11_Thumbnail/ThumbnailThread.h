#pragma once

#include <QThread>
#include <QImage>
#include <QString>

class ThumbnailThread: public QThread
{
Q_OBJECT
public:
	ThumbnailThread(const QString filename, int n = 1);
	int waitseconds(){return number;};

private:
	void run();
	QImage bigpm, smallpm;
	QString pmfilename;
	int number;

signals:
	void thumbnailFinished(QImage) const;
	void thumbnailFailed(const QString filename) const;
};

