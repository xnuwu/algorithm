#pragma once
#include <iostream>
#include <stdexcept>

using std::ostream;

class String {
	friend
		ostream& operator<<(ostream& os, const String& str);

private:
	char* ch;
	unsigned __int64 len;
public:

	String(): ch(nullptr), len(0) {
	};

	String(const char* ch) {

		unsigned __int64 sz = 0;
		while (ch[sz] != '\0') {
			sz++;
		}
		sz++;
		this->ch = new char[sz];
		for (int i = 0; i < sz - 1; i++) {
			this->ch[i] = ch[i];
		}
		this->ch[sz - 1] = '\0';
		this->len = sz - 1;
	}

	bool operator!() {
		return this -> len == 0;
	}

	String& operator=(const String& str) {
		if (str.len != 0) {
			unsigned __int64 sz = str.len + 1;
			this->ch = new char[sz];
			for (unsigned __int64 i = 0; i < str.len; i++) {
				this->ch[i] = str.ch[i];
			}
			this->ch[sz - 1] = '\0';
		}
		return *this;
	}

	bool operator==(String& str) {
		if (this == &str) {
			return true;
		}

		if (this->len != str.len) {
			return false;
		}

		for (unsigned __int64 i = 0; i < this->len; i++) {
			if (this->ch[i] != str[i]) {
				return false;
			}
		}

		return true;
	}

	char operator[](unsigned __int64 i) const {
		return this->chatAt(i);
	}

	~String() {
		if (len > 0) {
			delete[] ch;
		}
	}

	unsigned __int64 length() const {
		return len;
	}

	char chatAt(unsigned __int64 i) const {
		if (i >= len || i < 0) {
			throw std::range_error("index incorrect! index:" + i);
		}
		else {
			return ch[i];
		}
	}

	String& substr(unsigned __int64 i, unsigned __int64 k) {
		String* pstr = new String;
		unsigned __int64 sz = k + 1;
		pstr->ch = new char[sz];
		for (unsigned __int64 j = 0; j < sz - 1; j++) {
			pstr->ch[j] = this->ch[i + j];
		}
		pstr->ch[sz - 1] = '\0';
		pstr->len = k;
		return *pstr;
	}

	String& prefix(unsigned __int64 n) {
		String* pstr = new String;
		unsigned __int64 sz = n + 1;
		pstr->ch = new char[sz];
		for (unsigned __int64 i = 0; i < sz - 1; i++) {
			pstr->ch[i] = this -> ch[i];
		}
		pstr->ch[sz - 1] = '\0';
		pstr->len = n;
		return *pstr;
	}

	String& suffix(unsigned __int64 n) {
		unsigned __int64 left = len - n;
		String* pstr = new String;
		unsigned __int64 sz = n + 1;
		pstr->ch = new char[sz];
		for (unsigned __int64 i = 0; i < sz - 1; i++) {
			pstr->ch[i] = this->ch[left + i];
		}
		pstr->ch[sz - 1] = '\0';
		pstr->len = n;
		return *pstr;
	}

	bool equal(String& str) {
		return str == *this;
	}

	String& concat(const String& str) {
		unsigned __int64 sz = len + str.len;
		String* pstr = new String;
		pstr->ch = new char[sz + 1];
		for (int i = 0; i < len; i++) {
			pstr->ch[i] = ch[i];
		}
		for (unsigned __int64 i = len, j = 0; i < sz; i++, j++) {
			pstr->ch[i] = str.ch[j];
		}
		pstr->ch[sz] = '\0';
		pstr->len = sz;
		return *pstr;
	}

	__int64 indexOf(const String& str) {
		__int64 i = -1;
		return i;
	}
};

ostream& operator<<(ostream& os, const String& str)
{
	for (int i = 0; i < str.len; i++) {
		os << str.ch[i];
	}
	return os;
}
