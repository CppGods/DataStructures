#ifndef UN_SET_HPP
#define UN_SET_HPP

#include <utility>
#include <functional>
#include <vector>
#include <hash_table\hash_table_o_a.hpp>

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
> class Unordered_Set {

public:

	class TUnordered_Set_Bidiretional_Iterator
		: public std::iterator<std::bidirectional_iterator_tag, Val > {

		friend class Unordered_Set;

	private:

		TUnordered_Set_Bidiretional_Iterator()
			: pos_{ 0 } {

		}

	public:

		TUnordered_Set_Bidiretional_Iterator(TUnordered_Set_Bidiretional_Iterator const & other)
			: pos_{ other.pos_ } {

			values_ = other.values_;
		}

		bool operator!=(TUnordered_Set_Bidiretional_Iterator const & other) const {

			return pos_ != other.pos_;
		}

		bool operator==(TUnordered_Set_Bidiretional_Iterator const & other) const {

			
			return pos_ == other.pos_;
		}

		const Val & operator*() const {

			return *values_[pos_];
		}

		TUnordered_Set_Bidiretional_Iterator & operator++() {

			++pos_;
			return *this;
		}

		TUnordered_Set_Bidiretional_Iterator & operator--() {

			--pos_;
			return *this;
		}

		TUnordered_Set_Bidiretional_Iterator & operator++(int) {

			TUnordered_Set_Bidiretional_Iterator tmp(*this);
			++pos_;
			return tmp;
		}

		TUnordered_Set_Bidiretional_Iterator & operator--(int) {

			TUnordered_Set_Bidiretional_Iterator tmp(*this);
			--pos_;
			return tmp;
		}

		~TUnordered_Set_Bidiretional_Iterator() {
		
		}

	private:

		std::vector<Val const *> values_;
		std::size_t pos_;
	};

	TUnordered_Set_Bidiretional_Iterator cbegin() const {

		TUnordered_Set_Bidiretional_Iterator it;
		it.values_ = std::move(get_vals_refs_vector());

		return it;
	}

	TUnordered_Set_Bidiretional_Iterator cend() const {

		TUnordered_Set_Bidiretional_Iterator it;
		it.values_ = std::move(get_vals_refs_vector());
		it.pos_ = it.values_.size();

		return it;
	}

	Unordered_Set();
	Unordered_Set(Unordered_Set const & other);
	Unordered_Set(Unordered_Set && other);
	Unordered_Set & operator=(Unordered_Set const & other);
	Unordered_Set & operator=(Unordered_Set && other);
	~Unordered_Set();
	void swap(Unordered_Set & other);

	void insert(Val const & val);
	bool find(Val const & val) const;
	void erase(Val const & val);
	void clear();
	bool empty() const;
	std::size_t size() const;

	template <class Args>
	void emplace(Args && args);

	bool operator>(Unordered_Set const & other) const;
	bool operator<(Unordered_Set const & other) const;
	bool operator==(Unordered_Set const & other) const;
	bool operator>=(Unordered_Set const & other) const;
	bool operator<=(Unordered_Set const & other) const;
	bool operator!=(Unordered_Set const & other) const;

private:

	Hash_Table_O_A<Val, Hash, ValEqual> * hash_table_;

	std::vector<Val const *> get_vals_refs_vector() const;

};


////////////////////////////////REALISE/////////////////////////

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
Unordered_Set<Val, Hash, ValEqual>::
Unordered_Set() {

	hash_table_ = new Hash_Table_O_A<Val, Hash, ValEqual>();
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
Unordered_Set<Val, Hash, ValEqual>::
Unordered_Set(Unordered_Set<Val, Hash, ValEqual> const & other) {
	
	hash_table_ = new Hash_Table_O_A<Val, Hash, ValEqual>(*other.hash_table_);
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
Unordered_Set<Val, Hash, ValEqual>::
Unordered_Set(Unordered_Set<Val, Hash, ValEqual> && other)
	: Unordered_Set() {

	swap(other);
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
Unordered_Set<Val, Hash, ValEqual> &
Unordered_Set<Val, Hash, ValEqual>::
operator=(Unordered_Set<Val, Hash, ValEqual> const & other) {

	if (this != &other) {
		Unordered_Set tmp(other);
		tmp.swap(*this);
	}
	return *this;
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
Unordered_Set<Val, Hash, ValEqual> &
Unordered_Set<Val, Hash, ValEqual>::
operator=(Unordered_Set<Val, Hash, ValEqual> && other) {

	swap(other);
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
bool
Unordered_Set<Val, Hash, ValEqual>::
operator>=(Unordered_Set<Val, Hash, ValEqual> const & other) const {

	std::size_t sz_other = other.size();
	std::size_t sz_cur = size();
	if (sz_cur < sz_other) {
		return false;
	}
	if (sz_other == 0) {
		return true;
	}

	TUnordered_Set_Bidiretional_Iterator const_it_other_begin = other.cbegin();
	TUnordered_Set_Bidiretional_Iterator const_it_other_end = other.cend();
	for (TUnordered_Set_Bidiretional_Iterator it = const_it_other_begin; it != const_it_other_end; ++it) {
		if (!find(*it)) {
			return false;
		}
	}
	return true;
}


template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
bool
Unordered_Set<Val, Hash, ValEqual>::
operator<=(Unordered_Set<Val, Hash, ValEqual> const & other) const {

	return (other >= *this);
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
bool
Unordered_Set<Val, Hash, ValEqual>::
operator==(Unordered_Set<Val, Hash, ValEqual> const & other) const {

	return ((*this >= other) && (other >= *this));
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
bool
Unordered_Set<Val, Hash, ValEqual>::
operator>(Unordered_Set<Val, Hash, ValEqual> const & other) const {

	return ((*this >= other) && (!(*this <= other)));
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
bool
Unordered_Set<Val, Hash, ValEqual>::
operator<(Unordered_Set<Val, Hash, ValEqual> const & other) const {

	return (other > *this);
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
bool
Unordered_Set<Val, Hash, ValEqual>::
operator!=(Unordered_Set<Val, Hash, ValEqual> const & other) const {

	return !(*this == other);
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
Unordered_Set<Val, Hash, ValEqual>::
~Unordered_Set() {

	delete hash_table_;
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
void
Unordered_Set<Val, Hash, ValEqual>::
swap(Unordered_Set<Val, Hash, ValEqual> &other) {

	std::swap(hash_table_, other.hash_table_);
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
void
Unordered_Set<Val, Hash, ValEqual>::
insert(Val const & val) {
	
	if (!find(val)) {
		hash_table_->insert(val);
	}
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
bool
Unordered_Set<Val, Hash, ValEqual>::
find(Val const & val) const {

	return hash_table_->find(val);
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
void
Unordered_Set<Val, Hash, ValEqual>::
erase(Val const & val) {

	hash_table_->erase(val);
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
void
Unordered_Set<Val, Hash, ValEqual>::
clear() {

	hash_table_->clear();
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
bool
Unordered_Set<Val, Hash, ValEqual>::
empty() const {

	return hash_table_->empty();
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
std::size_t
Unordered_Set<Val, Hash, ValEqual>::
size() const {

	return hash_table_->size();
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
template <class Args>
void
Unordered_Set<Val, Hash, ValEqual>::
emplace(Args && args) {

	hash_table_->emplace(args);
}



////private

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
std::vector<const Val *>
Unordered_Set<Val, Hash, ValEqual>::
get_vals_refs_vector() const {

	return hash_table_->get_vals_ref_vector();
}


#endif // !UN_SET_HPP