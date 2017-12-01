#pragma once
#include <QtWidgets>
#include "StandardOutputRedirector.hpp"

class LogWidget : public QWidget {
public:
	LogWidget(QWidget* parent = nullptr, const int maxNumBlocks = 100000);
	~LogWidget();

	void Append(const std::string& text);
	void Flush();
	void Clear();

private:
	static void Update(const char* text, std::streamsize count, void* textBoxPtr);

	void SaveLog();

private:
	QMutex mutex_;
	std::string textQueue_;
	QPlainTextEdit* textEdit_;
	StandardOutputRedirector<char, std::char_traits<char>>* coutRedictor_;
	StandardOutputRedirector<char, std::char_traits<char>>* cerrRedictor_;
	StandardOutputRedirector<char, std::char_traits<char>>* clogRedictor_;
};

