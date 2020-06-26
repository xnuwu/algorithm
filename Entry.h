#pragma once
template<typename K, typename V>
class Entry {
public:
	K key;
	V value;
	
	Entry(K k = K(), V v = V()) : key(k), value(v) {};

	Entry(Entry<K, V> const& entry): key(entry.key), value(entry.value) {};

	bool operator<(Entry<K, V> const& entry) { return key < entry.key };
	bool operator>(Entry<K, V> const& entry) { return key > entry.key };
	bool operator==(Entry<K, V> const& entry) { return key == entry.key };
	bool operator!=(Entry<K, V> const& entry) { return key != entry.key };
};