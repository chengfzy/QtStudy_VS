#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets>

class Eg15_DragAndDrop : public QMainWindow
{
	Q_OBJECT

public:
	Eg15_DragAndDrop(QWidget *parent = Q_NULLPTR);

protected:
	void dragEnterEvent(QDragEnterEvent* event);
	void dropEvent(QDropEvent* event);

private:
	bool readFile(const QString& fileName);
	QTextEdit* m_pTextEdit;
};
