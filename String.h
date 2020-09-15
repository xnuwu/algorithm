#pragma once
#include <iostream>

using std::ostream;

int strLen(const char* s) {
	int i = 0;
	while (s[i] != '\0') {
		i++;
	}
	return i;
}

class String {
	friend
		ostream& operator<<(ostream& os, const String& str);

private:
	char* ch;
	unsigned __int64 len;
public:

	String(): ch(nullptr), len(0) {
	};

	String(const char* ch, unsigned __int64 size) {
		unsigned __int64 sz = size + 1;
		this->ch = new char[sz];
		for (int i = 0; i < size; i++) {
			this->ch[i] = ch[i];
		}
		this->ch[size] = '\0';
		this->len = size;
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
			this->ch[str.len] = '\0';
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

	int chatAt(unsigned __int64 i) const {
		if (i >= len && i < 0) {
			return -1;
		}
		else {
			return ch[i];
		}
	}

	String& prefix(unsigned __int64 n) {
		String* pstr = new String;
		unsigned __int64 sz = n + 1;
		pstr->ch = new char[sz];
		for (unsigned __int64 i = 0; i < n; i++) {
			pstr->ch[i] = this -> ch[i];
		}
		pstr->ch[n] = '\0';
		pstr->len = n;
		return *pstr;
	}

	String& suffix(unsigned __int64 n) {
		unsigned __int64 left = len - n;
		String* pstr = new String;
		unsigned __int64 sz = n + 1;
		pstr->ch = new char[sz];
		for (unsigned __int64 i = 0; i < n; i++) {
			pstr->ch[i] = this->ch[left + i];
		}
		pstr->ch[n] = '\0';
		pstr->len = n;
		return *pstr;
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

	int match1(const char* p, const char* s) {
		size_t n = strLen(p);
		size_t m = strLen(s);
		int i = 0;
		int j = 0;
		while (i < n && j < m) {
			if (p[i] == s[j]) {
				i++;
				j++;
			}
			else {
				j -= i - 1;
				i = 0;
			}
		}

		return j - i;
	}

	int match2(const char* p, const char* s) {
		size_t n = strLen(p);
		size_t m = strLen(s);
		int i = 0;
		int j;
		for (; i < m - n; i++) {
			for (j = 0; j < n; j++) {
				if (s[i] != p[j]) {
					break;
				}
			}

			if (n <= j) {
				break;
			}
		}
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
