#pragma once
template<typename K, typename V>
class Entry {
public:
	K key;
	V data;
	
	Entry(K& key, V& data) : key(key), data(data) {}

	Entry(Entry<K, V> const& entry): key(entry.key), data(entry.data) {}

	bool operator<(Entry<K, V> const& entry) { return key < entry.key };
	bool operator>(Entry<K, V> const& entry) { return key > entry.key };
	bool operator==(Entry<K, V> const& entry) { return key == entry.key };
	bool operator!=(Entry<K, V> const& entry) { return key != entry.key };
};