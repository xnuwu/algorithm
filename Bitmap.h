#pragma once
#include <fstream>

typedef unsigned long long size_bt;

class Bitmap {
private:
	char* _basePtr;
	size_bt bitSize;

public:
	Bitmap(size_bt bitSize = 8) {
		init(bitSize);
	}

	Bitmap(const std::string filename, size_bt bs) {
		init(bs);
		std::ifstream is(filename, std::ifstream::binary);
		if (is) {
			is.read(_basePtr, (bs + 7) / 8);
			is.close();
		}
		else {
			throw std::runtime_error("read file " + std::string(filename) + " failed!");
		}
	}

	Bitmap& operator=(const Bitmap& bitmap) {
		init(bitmap.bitSize);
		size_bt byteSize = (bitSize + 7) / 8;
		for (size_bt i = 0; i < byteSize; i++) {
			_basePtr[i] = bitmap.getByte(i);
		}
		return *this;
	}

	void init(size_bt bs) {
		size_bt sz = (bs + 7) / 8;
		_basePtr = new char[sz];
		bitSize = bs;
		memset(_basePtr, 0, sz);
	}

	char getByte(size_bt i) const {
		return _basePtr[i];
	}

	void expand(size_bt bs) {
		size_bt newByteSize = (bs + 7) / 8;
		size_bt byteSize = (bitSize + 7) / 8;
		if (byteSize >= newByteSize) return;
		char* tmp = new char[newByteSize];
		for (size_bt i = 0; i < byteSize; i++) {
			tmp[i] = _basePtr[i];
		}
		for (size_bt i = byteSize; i < newByteSize; i++) {
			tmp[i] = 0;
		}
		delete[] _basePtr;
		_basePtr = tmp;
		bitSize = bs;
	}

	void dump(const std::string filename) {
		std::ofstream os(filename, std::ofstream::binary);
		if (os) {
			for (size_bt i = 0; i < (bitSize + 7) / 8; i++) {
				os << _basePtr[i];
			}
			os.flush();
			os.close();
		}
		else {
			throw std::runtime_error("write file " + std::string(filename) + " failed!");
		}
	}

	void set(size_bt i) {
		expand(i + 1);
		size_bt chIndex = i / 8;
		size_bt bitIndex = i % 8;

		size_bt flag = 1ull << bitIndex;
		_basePtr[chIndex] |= flag;
	}

	void clear(size_bt i) {
		expand(i + 1);
		size_bt chIndex = i / 8;
		size_bt bitIndex = i % 8;

		size_bt flag = 1;
		flag <<= bitIndex;
		flag = ~flag;
		_basePtr[chIndex] &= flag;
	}

	bool test(size_bt i) {
		expand(i + 1);
		size_bt chIndex = i / 8;
		size_bt bitIndex = i % 8;

		size_bt flag = 1;
		flag <<= bitIndex;
		return flag & _basePtr[chIndex];
	}

	char* toString(size_bt n) {
		expand(n);
		char* s = new char[n + 1];
		s[n] = '\0';
		for (size_bt i = 0; i < n; i++) {
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
