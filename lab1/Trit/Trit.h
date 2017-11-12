#include<iostream>
#include<unordered_map>

enum Trit{ False, Unknown, True };

const unsigned int trit_size = sizeof(unsigned int)* 8 / 2;//вместимость в тритах
const unsigned int bit_size = sizeof(unsigned int)* 8;//вместимость в битах

class TritSet {
private:
	unsigned int *data;//данные
	unsigned int init_capacity;//
	unsigned int ptr_last;//последний элемент в ptr
	unsigned int capacity; // вместимость в uint'ах
	unsigned int Last_changed_trit;//последний измененный трит
	class Reference {//ѕрокси-класс, который представл€ет ссылку на трит (класс)
	private:
		friend class TritSet;
		TritSet *ptr;
		unsigned int index;//индекс текущего элемента
		unsigned int BitShift;
		unsigned int ByteShift;
		void set_trit(int, int);//установить трит
		void set_bit(int, int);//установить бит
	public:
		Reference(TritSet *, unsigned int, unsigned int);//конструктор
		~Reference();//деструктор
		Reference& operator=(Trit);//ѕрисваивает значение к биту, на который указывает ссылка
		Reference& operator=(const Reference&);//ѕрисваивает значение к биту, на который указывает ссылка
		Trit operator&(Trit);//and
		Trit operator|(Trit);//or
		Trit operator~() const;//¬озвращает инвертированное значение трита, на который указывает ссылка
		operator Trit() const;//¬озвращает значение из трита, на который указывает ссылка
		friend std::ostream& operator<<(std::ostream &, const TritSet::Reference&);
	};
public:
	TritSet();//конструктор по умолчанию 
	TritSet(TritSet const &);
	explicit TritSet(unsigned int);
	~TritSet();//деструктор
	Reference operator[](unsigned int);//ƒоступ к конкретному триту
	TritSet operator~() const;
	TritSet operator&(TritSet &) const;//and
	TritSet operator|(TritSet &) const;//or
	bool operator==(TritSet &set_) const;
	bool TritSet::operator!=(TritSet &set_) const;
	friend std::ostream& operator<<(std::ostream &, const TritSet &);
	Trit Shrink();//ѕолучает свободную пам€ть до начального значени€ или до значени€, хран€щего последний трит
	void Trim(size_t);//«абывает триты от последнего индекса и далее
	size_t length();
	size_t cardinality(Trit value);
	void reallocate(unsigned int);//ѕеревыдел€ет пам€ть дл€ хранени€ указанного количества тритов
	std::unordered_map< Trit, int, std::hash<int> > cardinality();
	int Any(const Trit);
	int None(Trit);
	int Unkn(Trit);
	unsigned int * get_set() const;
	unsigned int get_capacity() const;
	unsigned int get_uint_capacity() const;
};
