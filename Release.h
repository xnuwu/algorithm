#pragma once

#include <typeinfo>

template <typename T> class Cleaner {
public:
	static void clean(T x) {
#ifdef _DEBUG
		static int n = 0;
		if (7 > strlen(typeid(T).name())) {
			//printf("\t<%s>[%d] purged\n", typeid(T).name(), ++n);
		}
#endif // _DEBUG

	}
};

template <typename T> class Cleaner<T*> {
public:
	static void clean(T* x) {
		if (x) {
			delete x;
			x = nullptr;
		}
#ifdef _DEBUG
		static int n = 0;
		//printf("\t<%s>[%d] release\n", typeid(T*).name(), ++n);
#endif // _DEBUG

	}
};

template <typename T> void release(T x) {
	Cleaner<T>::clean(x);
}