#ifndef MAP_HPP
#define MAP_HPP


#include <avl_tree.hpp>
#include <utility>
#include <vector>
#include <algorithm>


//one key - one val
//unique keys

template<
	class Key,
	class Val,
	class Compare = std::less<Key>
> class map {

public:

	class Tmap_Bidiretional_Iterator
		: public std::iterator<std::bidirectional_iterator_tag, std::pair<Key, Val>> {

		friend class map;

	private:

		Tmap_Bidiretional_Iterator()
			: pos_{ 0 } {

		}

	public:

		Tmap_Bidiretional_Iterator(Tmap_Bidiretional_Iterator const & other)
			: pos_{ other.pos_ } {

			keys_ = other.keys_;
			values_ = other.values_;
		}

		bool operator!=(Tmap_Bidiretional_Iterator const & other) const {

			return pos_ != other.pos_;
		}

		bool operator==(Tmap_Bidiretional_Iterator const & other) const {
	
			return pos_ == other.pos_;
		}

		std::pair<Key, Val> operator*() const {

			return std::pair<Key, Val>(*keys_[pos_], *values_[pos_]);
		}

		Key const & key() const {

			return *keys_[pos_];
		}

		Val const & value() const {

			return *values_[pos_];
		}

		Tmap_Bidiretional_Iterator & operator++() {

			++pos_;
			return *this;
		}

		Tmap_Bidiretional_Iterator & operator--() {

			--pos_;
			return *this;
		}

		Tmap_Bidiretional_Iterator & operator++(int) {

			Tmap_Bidiretional_Iterator tmp(*this);
			++pos_;
			return tmp;
		}

		Tmap_Bidiretional_Iterator & operator--(int) {

			Tmap_Bidiretional_Iterator tmp(*this);
			--pos_;
			return tmp;
		}

		~Tmap_Bidiretional_Iterator() {
		
		}

	private:

		std::vector<Key const *> keys_;
		std::vector<Val const *> values_;
		std::size_t pos_;
	};

	Tmap_Bidiretional_Iterator cbegin() const {

		Tmap_Bidiretional_Iterator it;
		std::size_t count = ordered_keys_.size();
		for(std::size_t i = 0; i < count; ++i){
			auto node = pairs_->search(ordered_keys_[i]);
			it.keys_.push_back(&node->key);
			it.values_.push_back(&node->value);
		}

		return it;
	}

	Tmap_Bidiretional_Iterator cend() const {

		Tmap_Bidiretional_Iterator it;
		std::size_t count = ordered_keys_.size();
		for(std::size_t i = 0; i < count; ++i){
			auto node = pairs_->search(ordered_keys_[i]);
			it.keys_.push_back(&node->key);
			it.values_.push_back(&node->value);
		}
		it.pos_ = count;

		return it;
	}


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
	void clear();
	bool empty() const;
	std::size_t size() const;

	Val operator[](Key const & key) const;

private:

	Compare *comp_;
	avl_tree<Key, Val, Compare> * pairs_;
	std::vector<Key> ordered_keys_;
};

/////////////////////////////////////////REALIZE//////////////////////

template<
	class Key,
	class Val,
	class Compare
>
map<Key, Val, Compare>::
map() {

	pairs_ = new avl_tree<Key, Val, Compare>();
	comp_ = new Compare();
}

template<
	class Key,
	class Val,
	class Compare
>
map<Key, Val, Compare>::
map(map<Key, Val, Compare> const & other) {
	
	pairs_ = new avl_tree<Key, Val, Compare>(*other.pairs_);
	ordered_keys_.assign(other.ordered_keys_.size(), Key());
	std::copy(other.ordered_keys_.begin(), other.ordered_keys_.end(), ordered_keys_.begin());
	comp_ = new Compare(*other.comp_);
}

template<
	class Key,
	class Val,
	class Compare
>
map<Key, Val, Compare>::
map(map<Key, Val, Compare> && other)
	: map() {

	swap(other);
}

template<
	class Key,
	class Val,
	class Compare
>
map<Key, Val, Compare> &
map<Key, Val, Compare>::
operator=(map<Key, Val, Compare> const & other) {

	if (this != &other) {
		map tmp(other);
		tmp.swap(*this);
	}
	return *this;
}

template<
	class Key,
	class Val,
	class Compare
>
map<Key, Val, Compare> &
map<Key, Val, Compare>::
operator=(map<Key, Val, Compare> && other) {

	swap(other);
}

template<
	class Key,
	class Val,
	class Compare
>
map<Key, Val, Compare>::
~map() {

	delete pairs_;
	delete comp_;
}

template<
	class Key,
	class Val,
	class Compare
>
void
map<Key, Val, Compare>::
swap(map<Key, Val, Compare> & other) {

	std::swap(pairs_, other.pairs_);
	ordered_keys_.swap(other.ordered_keys_);
}

template<
	class Key,
	class Val,
	class Compare	
>
void
map<Key, Val, Compare>::
insert(Key const & key, Val const & val) {
	
	if (!find(key)) {
		pairs_->insert(val, key);

		ordered_keys_.push_back(key);
		std::size_t size = this->size();
		std::size_t pos_left = size - 2;
		std::size_t pos_cur = size - 1;			
		while ((pos_cur > 0) && ((*comp_)(ordered_keys_[pos_cur], ordered_keys_[pos_left]))) {
			ordered_keys_[pos_cur] = ordered_keys_[pos_left];
			ordered_keys_[pos_left] = key;
			--pos_left;
			--pos_cur;
		}
	}
}

template<
	class Key,
	class Val,
	class Compare
>
bool
map<Key, Val, Compare>::
find(Key const & key) const {

	return (pairs_->search(key) != nullptr);
}

template<
	class Key,
	class Val,
	class Compare
>
void
map<Key, Val, Compare>::
erase(Key const & key) {

	pairs_->remove(key);

	std::vector<Key> new_keys;
	std::size_t size = ordered_keys_.size();
	for (std::size_t i = 0; i < size; ++i) {
		if ((*comp_)(key, ordered_keys_[i]) || (*comp_)(key, ordered_keys_[i])) {
			new_keys.push_back(ordered_keys_[i]);
		}
	}
	ordered_keys_.swap(new_keys);
}

template<
	class Key,
	class Val,
	class Compare
>
void
map<Key, Val, Compare>::
clear() {

	delete pairs_;
	pairs_ = new avl_tree<Key, Val, Compare>();
	ordered_keys_.clear();
}

template<
	class Key,
	class Val,
	class Compare
>
bool
map<Key, Val, Compare>::
empty() const {

	return pairs_->isEmpty();
}

template<
	class Key,
	class Val,
	class Compare
>
std::size_t
map<Key, Val, Compare>::
size() const {

	return pairs_->size();
}

template<
	class Key,
	class Val,
	class Compare
>
Val
map<Key, Val, Compare>::
get_value(Key const & key) const {

	return pairs_->search(key)->value;
}

template<
	class Key,
	class Val,
	class Compare	
>
Val
map<Key, Val, Compare>::
operator[](Key const & key) const {

	return get_value(key);
}

////private

#endif !MAP_HPP