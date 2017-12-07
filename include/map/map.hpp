#ifndef MAP_HPP
#define MAP_HPP

#include <utility>
#include <vector>
#include <bst_tree>

//one key - one val
//unique keys

//improve info about methods
//TODO :: realise, &&, etc...

template<
	class Key,
	class Val,
	class Compare = std::less<Key>
> class map {

public:

	using Value_Type = std::pair<Key, Val>;

	map();
	map(map const & other);
	map(map && other);
	map & operator=(map const & other);
	map & operator=(map && other);
	~map();
	void swap(map & other);

	void insert(Key const & key, Val const & val);
	bool find(Key const & key) const;
	void erase(Key const & key);
	Val get_value(Key const & key) const;
	std::vector<Key> get_keys() const;
	void clear();
	bool empty() const;
	std::size_t size() const;

	Val operator[](Key const & key);
	Val & operator[](Key const & key);

private:

	bst_tree<Value_Type> pairs_;

};

#endif // !MAP_HPP
