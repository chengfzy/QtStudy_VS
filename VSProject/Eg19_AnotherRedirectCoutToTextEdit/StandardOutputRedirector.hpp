#pragma once
#include <iostream>

template <typename Elem = char, typename Tr = std::char_traits<Elem>>
class StandardOutputRedirector : public std::basic_streambuf<Elem, Tr> {
public:
	typedef void(*FuncPtr)(const Elem*, std::streamsize count, void* data);

	StandardOutputRedirector(std::ostream& stream, FuncPtr func, void* data)
		: stream_(stream), func_(func), data_(data) {
		buf_ = stream_.rdbuf(this);
	}

	~StandardOutputRedirector() {
		stream_.rdbuf(buf_);
	}

protected:
	std::streamsize xsputn(const Elem* ptr, std::streamsize count) {
		func_(ptr, count, data_);
		return count;
	}

	typename Tr::int_type overflow(typename Tr::int_type v) {
		Elem ch = Tr::to_char_type(v);
		func_(&ch, 1, data_);
		return Tr::not_eof(v);
	}

private:
	std::basic_ostream<Elem, Tr>& stream_;
	std::streambuf* buf_;
	FuncPtr func_;
	void* data_;
};