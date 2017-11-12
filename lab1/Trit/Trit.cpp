#include<iostream>
#include"Trit.h" 

TritSet::TritSet(){
	this->capacity = 0;
	this->data = nullptr;
	this->ptr_last = 0;
	this->Last_changed_trit = 0;
}

TritSet::TritSet(TritSet const & set) {
	this->init_capacity = set.init_capacity;
	this->capacity = set.capacity;
	this->data = new unsigned int[this->capacity];
	for (int i = 0; i < this->capacity; i++)
		this->data[i] = set.data[i];
	this->ptr_last = set.ptr_last;
	this->Last_changed_trit = set.Last_changed_trit;
}

TritSet::TritSet(unsigned int speccapacity) {
	this->init_capacity = speccapacity / trit_size;
	this->capacity = speccapacity / trit_size;
	auto TailTrit = speccapacity % trit_size;
	if (TailTrit > 0) {
		this->capacity++;
		this->init_capacity++;
	}
	this->data = new unsigned int[this->capacity];
	this->ptr_last = TailTrit == 0 ? trit_size * 2 - 1 : TailTrit * 2 - 1;
	this->Last_changed_trit = 0;
}

TritSet::Reference::Reference(TritSet *ptr_, unsigned int ByteShift_, unsigned int BitShift_)
: ptr(ptr_), ByteShift(ByteShift_), BitShift(BitShift_) {}
TritSet::Reference::~Reference() = default;

void TritSet::Reference::set_trit(int bit1, int bit2) {
	set_bit(bit1, index);
	set_bit(bit2, index + 1);
}

void TritSet::Reference::set_bit(int bit, int numb) {
	int mask = 1 << (bit_size - numb);
	if (bit == 0) {
		mask = ~mask;
		*ptr = *ptr & mask;
	}
	else *ptr = *ptr | mask;
}




//ѕрисваивает значение к биту, на который указывает ссылка

TritSet::Reference& TritSet::Reference::operator=(Trit t) { // set[i] = UNKNOWN;
	switch (t) {
	case False:
		set_trit(false, true);
		break;
	case Unknown:
		set_trit(false, false);
		break;
	case True:
		set_trit(true, false);
		break;
	}
	return *this;
}


TritSet::Reference& TritSet::Reference::operator=(const Reference& t){ // set[i] = b[j]
	static_cast<Trit>(t);
	*this = t;
	return *this;
}

TritSet & TritSet::operator=(const TritSet & set) {
	this->capacity = set.capacity;
	delete[] this->data;
	this->data = new unsigned int[set.capacity];
	for (int i = 0; i < this->capacity; i++)
		this->data[i] = set.data[i];
	this->ptr_last = set.ptr_last;
	this->Last_changed_trit = set.Last_changed_trit;
	return *this;
}

TritSet TritSet::operator~() const {
	TritSet set_copy = *this;
	TritSet set = *this;
	for (int i = 0; i < this->get_capacity(); i++)
		set[i] = ~set_copy[i];
	return set;
}

TritSet TritSet::operator&(TritSet &set_) const {
	TritSet set_copy = *this;
	auto capct1 = this->get_capacity();
	auto capct2 = set_.get_capacity();
	TritSet set(capct1 > capct2 ? capct1 : capct2);
	int i = 1;
	while (capct1 != i - 1 && capct2 != i - 1) {
		set[set.get_capacity() - i] = set_copy[capct1 - i] & set_[capct2 - i];
		i++;
	}
	i--; // now i is the capacity of the smaller operand
	int j = 0;
	// until we reach already filled part
	while (j < set.get_capacity() - i) {
		Reference r = capct1 > capct2 ? set_copy[j] : set_[j];
		set[j] = r & Unknown;
		j++;
	}
	return set;
}

TritSet TritSet::operator|(TritSet &set_) const {
	TritSet set_copy = *this;
	auto capct1 = this->get_capacity();
	auto capct2 = set_.get_capacity();
	TritSet set(capct1 > capct2 ? capct1 : capct2);
	int i = 1;
	while (capct1 != i - 1 && capct2 != i - 1) {
		set[set.get_capacity() - i] = set_copy[capct1 - i] | set_[capct2 - i];
		i++;
	}
	i--; // now i is the capacity of the smaller operand
	int j = 0;
	// until we reach already filled part
	while (j < set.get_capacity() - i) {
		Reference r = capct1 > capct2 ? set_copy[j] : set_[j];
		set[j] = r | Unknown;
		j++;
	}
	return set;
}

bool TritSet::operator==(TritSet &set_) const {
	// Method operator[] allows the object to be modified,
	// so we need to create copy
	TritSet set_copy = *this;
	if (this->get_capacity() != set_.get_capacity()) return false;
	for (int i = 0; i < this->get_capacity(); i++)
	if (set_copy[i] != set_[i]) return false;
	return true;
}

bool TritSet::operator!=(TritSet &set_) const {
	return !(this->operator==(set_));
}

std::ostream& operator<<(std::ostream &o, const TritSet &set) {
	TritSet set_copy = set;
	auto capacity = set.get_capacity();
	for (int i = 0; i < capacity; i++)
		o << i << " ";
	o << std::endl;
	for (int i = 0; i < capacity; i++)
		o << set_copy[i] << " ";
	return o;
}


//¬озвращает инвертированное значение трита, на который указывает ссылка.

Trit TritSet::Reference::operator~() const {
	if ((Trit)(*this) == True) return False;
	if ((Trit)(*this) == False) return True;
	return Unknown;
}

//ѕриведение типа к триту

TritSet::Reference::operator Trit() const {
	int bit1 = 1 & ((*ptr) >> bit_size - index);
	int bit2 = 1 & ((*ptr) >> bit_size - index + 1);
	if (bit1 == 1) return True;
	if (bit2 == 1) return False;
	return Unknown;
}

//конструктор TritSet

TritSet::TritSet() {
	this->capacity = 0;
	this->data = nullptr;
	this->ptr_last = 0;
}

//деструктор TritSet

TritSet::~TritSet() {
	delete[] data;
	data = nullptr;
}

////ƒоступ к конкретному триту

TritSet::Reference TritSet::operator[](unsigned int i) {
	i++;
	auto index_ = i % trit_size;
	auto byte_shift = i / trit_size;
	if (index_ == 0) {
		index_ = trit_size;
		byte_shift--;
	}
	return Reference(this, byte_shift, index_ * 2 - 1);
}

int TritSet::Any(const Trit t){
	Trit tmp = t;
	int count = 0;
	if (tmp){
		if (t == True){
			count++;
		}
	}
	return count;
}

int TritSet::None(const Trit t){
	Trit tmp = t;
	int count = 0;
	if (tmp){
		if (t == False){
			count++;
		}
	}
	return count;
}

int TritSet::Unkn(const Trit t){
	Trit tmp = t;
	int count = 0;
	if (tmp){
		if (t == Unknown){
			count++;
		}
	}
	return count;
}

//ѕеревыдел€ет пам€ть дл€ хранени€ указанного количества тритов

void TritSet::reallocate(unsigned int new_capacity){
	this->capacity = new_capacity / trit_size;
	auto TailTrit = new_capacity % trit_size;
	if (TailTrit > 0) this->capacity++;
	this->ptr_last = TailTrit == 0 ? trit_size * 2 - 1 : TailTrit * 2 - 1;
	auto *new_data = new unsigned int[this->capacity];
	for (int i = 0; i < this->capacity; i++)
		new_data[i] = this->data[i];
	delete[] this->data;
	this->data = new_data;
}

//«абывает триты от последнего индекса и далее

void TritSet::Trim(size_t last_index) {
	reallocate(last_index);
}

