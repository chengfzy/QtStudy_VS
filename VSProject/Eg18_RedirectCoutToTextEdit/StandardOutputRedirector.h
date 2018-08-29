#pragma once
#include <iostream>
#include <streambuf>
#include <string>
#include <QTextEdit>

class StandardOutputRedirector : public std::basic_streambuf<char> {
public:
	StandardOutputRedirector(std::ostream& stream, QTextEdit* textEdit)
		: stream_(stream), logEdit_(textEdit) {
		buf_ = stream.rdbuf();
		stream.rdbuf(this);
	}

	~StandardOutputRedirector() {
		if (!str_.empty()) {
			logEdit_->append(str_.c_str());
		}
		stream_.rdbuf(buf_);
	}

protected:
	std::streamsize xsputn(const char* p, std::streamsize count) {
		str_.append(p, p + count);
		int pos{ 0 };
		while (pos != std::string::npos) {
			pos = str_.find('\n');
			if (pos != std::string::npos) {
				std::string tmp(str_.begin(), str_.begin() + pos);
				logEdit_->append(tmp.c_str());
				str_.erase(str_.begin(), str_.begin() + pos + 1);
			}
		}
		return count;
	}

	int_type overflow(int_type v) {
		if (v != '\n') {
			logEdit_->append(str_.c_str());
			str_.erase(str_.begin(), str_.end());
		} else
			str_ += v;

		return v;
	}

private:
	std::ostream& stream_;
	std::streambuf* buf_;
	std::string str_;
	QTextEdit* logEdit_;
};