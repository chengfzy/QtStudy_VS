#include "LogWidget.h"
#include <fstream>

using namespace std;


LogWidget::LogWidget(QWidget * parent, const int maxNumBlocks) {
	setWindowTitle("Log");
	if (parent != nullptr) resize(320, parent->height()); else resize(800, 400);

	// Redictor
	coutRedictor_ = new StandardOutputRedirector<char, char_traits<char>>(cout, LogWidget::Update, this);
	cerrRedictor_ = new StandardOutputRedirector<char, char_traits<char>>(cerr, LogWidget::Update, this);
	clogRedictor_ = new StandardOutputRedirector<char, char_traits<char>>(clog, LogWidget::Update, this);

	// Timer
	QTimer* timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &LogWidget::Flush);
	timer->start(100);

	// QTextEdit
	textEdit_ = new QPlainTextEdit(this);
	textEdit_->setReadOnly(true);
	textEdit_->setMaximumBlockCount(maxNumBlocks);
	textEdit_->setWordWrapMode(QTextOption::NoWrap);
	textEdit_->setFont(QFont("Courier", 10));

	// Save, Clear Button
	QPushButton* saveLogButton = new QPushButton(tr("Save"), this);
	connect(saveLogButton, &QPushButton::clicked, this, &LogWidget::SaveLog);
	QPushButton* clearButton = new QPushButton(tr("Clear"), this);
	connect(clearButton, &QPushButton::clicked, this, &LogWidget::Clear);
	QHBoxLayout* saveClearLayout = new QHBoxLayout();
	saveClearLayout->addWidget(saveLogButton);
	saveClearLayout->addWidget(clearButton);

	// MainLayout
	QGridLayout* mainLayout = new QGridLayout(this);
	mainLayout->setContentsMargins(5, 10, 5, 5);
	mainLayout->addLayout(saveClearLayout, 0, 0, Qt::AlignLeft);
	mainLayout->addWidget(textEdit_);
}

LogWidget::~LogWidget() {
	delete coutRedictor_;
	delete cerrRedictor_;
	delete clogRedictor_;
}

void LogWidget::Append(const std::string & text) {
	QMutexLocker locker(&mutex_);
	textQueue_ += text;
}

void LogWidget::Flush() {
	QMutexLocker locker(&mutex_);

	if (!textQueue_.empty()) {
		// write to log widget
		textEdit_->moveCursor(QTextCursor::End);
		textEdit_->insertPlainText(QString::fromStdString(textQueue_));
		textEdit_->moveCursor(QTextCursor::End);
		textQueue_.clear();
	}
}

void LogWidget::Clear() {
	QMutexLocker locker(&mutex_);
	textQueue_.clear();
	textEdit_->clear();
}

void LogWidget::Update(const char * text, std::streamsize count, void * textBoxPtr) {
	string textStr(text, count);
	//for (streamsize i = 0; i < count; ++i) {
	//	if (text[i] == '\n') textStr += "\n";
	//	else textStr += text[i];
	//}

	LogWidget* logWidget = static_cast<LogWidget*>(textBoxPtr);
	logWidget->Append(textStr);
}

void LogWidget::SaveLog() {
	const string logPath = QFileDialog::getSaveFileName(this, tr("Select path to save log file"), tr(""), tr("Log (*.log)")).toUtf8().toStdString();
	if (logPath.empty()) return;

	ofstream file(logPath, std::ios::app);
	file << textEdit_->toPlainText().toUtf8().constData();
}
