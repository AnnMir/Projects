#include "Tritset.h"

Tritset::Iterator::Iterator(Tritset::Reference ref1) : ref(ref1){}

Tritset::Iterator::Iterator(const Tritset::Iterator &iter) : ref(iter.ref) {}

bool Tritset::Iterator::operator!=(Iterator const &iter) const {
	return !(this->ref.getTritset() == iter.ref.getTritset() && this->ref.getArrayPos() == iter.ref.getArrayPos() && this->ref.getIntPos() == iter.ref.getIntPos());
}

bool Tritset::Iterator::operator==(Iterator const &iter) const {
	return (this->ref.getTritset() == iter.ref.getTritset() && this->ref.getArrayPos() == iter.ref.getArrayPos() && this->ref.getIntPos() == iter.ref.getIntPos());
}

Trit_num Tritset::Iterator::operator*()const {
	Trit_num trit = ref.getTritset()->getTrit(ref.getArrayPos() * BYTE_SIZE * TRIT_SIZE + ref.getIntPos());
	return trit;
}

Tritset::Iterator& Tritset::Iterator::operator++() {
	ref.setIntPos(ref.getIntPos() + 1);
	if (ref.getIntPos() == (sizeof(uint)* BYTE_SIZE / TRIT_SIZE)){
		ref.setIntPos(0);
		ref.setArrayPos(ref.getArrayPos() + 1);
	}
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Tritset::Iterator a){
	os << a.ref << " ";
	return os;
}