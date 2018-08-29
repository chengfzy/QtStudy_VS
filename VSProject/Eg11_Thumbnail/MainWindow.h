#pragma once

#include <QtWidgets/QWidget>
#include <QTimer>
#include <QImage>

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	
protected:
	void openFiles();
	void deleteThread();
	void showError(const QString filename);
	void addThumbnail(QImage);
private:
	void createThumbnail(const QString& filename);
	QWidget* previewwidget;
	int waitseconds;
};
