#pragma once
#include <fstream>

class Bitmap {
private:
	char* _basePtr;
	int bitSize;

public:
	Bitmap(int bitSize = 8) {
		init(bitSize);
	}

	Bitmap(const std::string filename, int bs) {
		init(bs);
		std::ifstream is(filename, std::ifstream::binary);
		if (is) {
			is.read(_basePtr, bs);
			is.close();
		}
		else {
			throw std::runtime_error("read file " + std::string(filename) + " failed!");
		}
	}

	Bitmap& operator=(Bitmap& bitmap) {
		init(bitmap.bitSize);
		int byteSize = (bitSize + 7) / 8;
		for (int i = 0; i < byteSize; i++) {
			_basePtr[i] = bitmap.getByte(i);
		}
		return *this;
	}

	void init(int bs) {
		int sz = (bs + 7) / 8;
		_basePtr = new char[sz];
		bitSize = bs;
		memset(_basePtr, 0, sz);
	}

	char getByte(int i) {
		return _basePtr[i];
	}

	void expand(int bs) {
		int newByteSize = (bs + 7) / 8;
		int byteSize = (bitSize + 7) / 8;
		if (byteSize >= newByteSize) return;
		char* tmp = new char[newByteSize];
		for (int i = 0; i < byteSize; i++) {
			tmp[i] = _basePtr[i];
		}
		for (int i = byteSize; i < newByteSize; i++) {
			tmp[i] = 0;
		}
		delete[] _basePtr;
		_basePtr = tmp;
		bitSize = bs;
	}

	void dump(const std::string filename) {
		std::ofstream os(filename);
		if (os) {
			for (int i = 0; i < (bitSize + 7) / 8; i++) {
				os << _basePtr[i];
			}
			os.flush();
			os.close();
		}
		else {
			throw std::runtime_error("write file " + std::string(filename) + " failed!");
		}
	}

	void set(int i) {
		expand(i + 1);
		int chIndex = i / 8;
		int bitIndex = i % 8;

		int flag = 1 << bitIndex;
		_basePtr[chIndex] |= flag;
	}

	void clear(int i) {
		expand(i + 1);
		int chIndex = i / 8;
		int bitIndex = i % 8;

		int flag = 1;
		flag <<= bitIndex;
		flag = ~flag;
		_basePtr[chIndex] &= flag;
	}

	bool test(int i) {
		expand(i + 1);
		int chIndex = i / 8;
		int bitIndex = i % 8;

		int flag = 1;
		flag <<= bitIndex;
		return flag & _basePtr[chIndex];
	}

	char* toString(int n) {
		expand(n);
		char* s = new char[n + 1];
		s[n] = '\0';
		for (int i = 0; i < n; i++) {
			s[i] = test(i) ? '1' : '0';
		}
		return s;
	}

	~Bitmap() {
		delete[] _basePtr;
		_basePtr = nullptr;
		bitSize = 0;
	}
};
