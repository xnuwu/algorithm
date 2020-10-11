#pragma once
#include <iostream>
#include <stdexcept>

using std::ostream;

class String {
	typedef __int64 m_size_t;
	friend
		ostream& operator<<(ostream& os, const String& str);

private:
	char* ch;
	m_size_t len;
public:

	String(): ch(nullptr), len(0) {
	};

	String(const char* ch) {

		m_size_t sz = 0;
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
			m_size_t sz = str.len + 1;
			this->ch = new char[sz];
			for (m_size_t i = 0; i < sz - 1; i++) {
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

		for (m_size_t i = 0; i < this->len; i++) {
			if (this->ch[i] != str[i]) {
				return false;
			}
		}

		return true;
	}

	char operator[](m_size_t i) const {
		return this->chatAt(i);
	}

	~String() {
		if (len > 0) {
			delete[] ch;
		}
	}

	m_size_t length() const {
		return len;
	}

	char chatAt(m_size_t i) const {
		if (i >= len || i < 0) {
			throw std::range_error("index incorrect! index:" + i);
		}
		else {
			return ch[i];
		}
	}

	String& substr(m_size_t i, m_size_t k) {
		String* pstr = new String;
		m_size_t sz = k + 1;
		pstr->ch = new char[sz];
		for (m_size_t j = 0; j < sz - 1; j++) {
			pstr->ch[j] = this->ch[i + j];
		}
		pstr->ch[sz - 1] = '\0';
		pstr->len = k;
		return *pstr;
	}

	String& prefix(m_size_t n) {
		String* pstr = new String;
		m_size_t sz = n + 1;
		pstr->ch = new char[sz];
		for (m_size_t i = 0; i < sz - 1; i++) {
			pstr->ch[i] = this -> ch[i];
		}
		pstr->ch[sz - 1] = '\0';
		pstr->len = n;
		return *pstr;
	}

	String& suffix(m_size_t n) {
		m_size_t left = len - n;
		String* pstr = new String;
		m_size_t sz = n + 1;
		pstr->ch = new char[sz];
		for (m_size_t i = 0; i < sz - 1; i++) {
			pstr->ch[i] = this->ch[left + i];
		}
		pstr->ch[sz - 1] = '\0';
		pstr->len = n;
		return *pstr;
	}

	bool equal(String& str) {
		return str == *this;
	}

	String* concat(const String& str) {

		m_size_t sz = len + str.len;
		char *newCh = new char[sz + 1];
		for (int i = 0; i < len; i++) {
			newCh[i] = ch[i];
		}
		for (m_size_t i = len, j = 0; i < sz; i++, j++) {
			newCh[i] = str.ch[j];
		}
		newCh[sz] = '\0';
		this->len = sz;
		delete this->ch;
		this->ch = newCh;
		return this;
	}

	m_size_t indexOf(const String& str) {
		m_size_t i = -1;
		return i;
	}

	m_size_t match1(const String& str) {

		m_size_t i = 0;;
		m_size_t m = len;

		m_size_t j = 0;
		m_size_t n = str.length();

		if (n > m || n <= 0) {
			return -1;
		}

		while(i < m) {
			if (this ->ch[i] == str[j]) {
				i++;
				j++;
			}
			else {
				i -= j - 1;
				j = 0;
			}
			
			if (j >= n) {
				return i - j;
			}
		}

		return -1;
	}

	m_size_t match2(const String& str) {
		m_size_t i = 0;
		m_size_t m = len;

		m_size_t j = 0;
		m_size_t n = str.length();

		if (n > m || n <= 0) {
			return -1;
		}

		for (; i < m - n + 1; i++) {
			for (j = 0; j < n; j++) {
				if (this->ch[i + j] == str[j]) {
					j++;
				}
				else {
					break;
				}
			}

			if (j >= n) {
				return i;
			}
		}

		return -1;
	}

	int* kmpBuildNext(const String& str) {
		m_size_t m = str.length();
		int* next = new int[m];
		next[0] = -1;
		int j = -1;
		int i = 0;
		while (i < m - 1) {
			if (j < 0 || str[i] == str[j]) {
				i++;
				j++;
				next[i] = (str[i] != str[j] ? j : next[j]);
			}
			else {
				j = next[j];
			}
		}
		return next;
	}
	
	m_size_t kmpMatch(const String& str) {
		int* next = kmpBuildNext(str);
		m_size_t m = len;
		m_size_t n = str.length();
		m_size_t i = 0;
		m_size_t j = 0;
		while (i < m) {
			if (j < 0 || this->ch[i] == str[j]) {
				i++;
				j++;
			}
			else {
				j = next[j];
			}
		}
		delete next;
		return i - j;
	}
};

ostream& operator<<(ostream& os, const String& str)
{
	for (int i = 0; i < str.len; i++) {
		os << str.ch[i];
	}
	return os;
}