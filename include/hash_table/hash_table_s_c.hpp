#ifndef HASH_TABLE_S_C_HPP
#define HASH_TABLE_S_C_HPP

#include <utility>
#include <functional>
#include <vector>

#define CAPACITY 100
#define LOAD_FACTOR 0.5

//hash_table_using_separate_chaining
//for map
//not unique elemnts

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
> class Hash_Table_S_C {

	struct Element {
		std::pair<Key, Val> data_;
		bool is_empty_ = true;
	};

	Hash_Table_S_C();
	Hash_Table_S_C(Hash_Table_S_C const & other);
	Hash_Table_S_C(Hash_Table_S_C && other);
	Hash_Table_S_C & operator=(Hash_Table_S_C const & other);
	Hash_Table_S_C & operator=(Hash_Table_S_C && other);
	~Hash_Table_S_C();
	void swap(Hash_Table_S_C & other);

	void insert(Key const & key, Val const & val);
	bool find(Key const & key) const;
	void erase(Key const & key);
	void clear();
	bool empty() const;
	std::size_t size() const;

private:

	Hash Hasher_;
	KeyEqual Equal_;
	float const load_factor_ = LOAD_FACTOR;

	std::size_t count_ = 0;
	std::size_t capacity_ = CAPACITY;
	std::vector<std::vector<Element>> HashArr_;

	void rehash();
	bool need_rehash();
	bool ins(Key const & key, Val const & val, std::vector<Element> & v);
	Element * fnd(Key const & key, Val const & val);
};

#endif // !HASH_TABLE_S_C_HPP