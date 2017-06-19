#include "Eg15_DragAndDrop.h"

Eg15_DragAndDrop::Eg15_DragAndDrop(QWidget *parent)
	: QMainWindow(parent)
{
	m_pTextEdit = new QTextEdit;
	setCentralWidget(m_pTextEdit);
	m_pTextEdit->setAcceptDrops(false);
	setAcceptDrops(true);

	setWindowTitle(tr("Text Editor"));
}

void Eg15_DragAndDrop::dragEnterEvent(QDragEnterEvent * event)
{
	if (event->mimeData()->hasFormat("text/uri-list"))
	{
		event->acceptProposedAction();
	}
}

void Eg15_DragAndDrop::dropEvent(QDropEvent * event)
{
	QList<QUrl> urls = event->mimeData()->urls();
	if (urls.isEmpty())
		return;

	QString fileName = urls.first().toLocalFile();
	if (fileName.isEmpty())
		return;

	if (readFile(fileName))
		setWindowTitle(tr("%1 - %2").arg(fileName, tr("Drag File")));
}

bool Eg15_DragAndDrop::readFile(const QString & fileName)
{
	bool r = false;
	QFile file(fileName);
	QString content;
	if (file.open(QIODevice::ReadOnly))
	{
		content = file.readAll();
		r = true;
	}

	m_pTextEdit->setText(content);
	return r;
}
