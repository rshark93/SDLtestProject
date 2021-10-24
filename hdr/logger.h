#pragma once

#include <iostream>
#include <ios>
#include <sstream>

typedef void(*log_s)(int, const char*);

bool set_logger(int32_t warn_level, log_s input_function);

class logger {
private:
	int loglevel;

	struct log_buf {
		std::stringstream m_Stream;
		int ref;
		log_buf() : ref(1) {}
	} *lbuffer;

public:
	enum level { log_trace, log_debug, log_information, log_warning, log_error, log_fatal };

	logger() : loglevel(log_warning), lbuffer(new log_buf) { }

	explicit logger(const int log_level) : loglevel(log_level), lbuffer(new log_buf()) { }

	logger(const logger& logStream) : loglevel(0), lbuffer(logStream.lbuffer) { ++lbuffer->ref; }

	static int global_log_level;
	static log_s func;

	static bool set_logger(const int32_t input_level, log_s input_func) {
    	global_log_level = input_level;
		func = input_func;
		return true;
	}

	~logger() {
		if (!--lbuffer->ref) {
			func(loglevel, lbuffer->m_Stream.str().c_str());
			delete lbuffer;
		}
	}

	template<class T>
	logger& operator << (const T& s) {
		lbuffer->m_Stream << s;
		return *this;
	}

	logger& operator<<(int s) {
		lbuffer->m_Stream << s;
		return *this;
	}

	logger& operator<<(long s) {
		lbuffer->m_Stream << s;
		return *this;
	}

	logger& operator<<(long long s) {
		lbuffer->m_Stream << s;
		return *this;
	}

	logger& operator<<(double s) {
		lbuffer->m_Stream << s;
		return *this;
	}

	logger& operator<<(std::ostream& (*funct)(std::ostream&)) {
		lbuffer->m_Stream << funct;
		return *this;
	}
};

#define INITIALIZE_LOGGER int logger::global_log_level = 5; \
log_s logger::func = nullptr; 

#define _log(level) if ( level>=logger::global_log_level && logger::func != nullptr) message(level) 

inline logger message(const int log_level) {
	return logger(log_level);
}

bool set_logger(int32_t warn_level, log_s input_function) {
	try {
		if (logger::set_logger(warn_level, input_function)) {
			_log(logger::log_trace) << "logger started";
			return true;
		}
	}
	catch (const std::exception e){
		// do nothing :( 
	}
	return false;
}