#ifndef UN_MAP_HPP
#define UN_MAP_HPP

#include <utility>
#include <functional>
#include "include\hash_table\hash_table.hpp"

//hash_table_using_open_addressing

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
> class unordered_map {

public:

	using value_type = std::pair<Key, T>;

private:

	Hash_Table<value_type, Hash, KeyEqual>

};

#endif // !UN_MAP_HPP