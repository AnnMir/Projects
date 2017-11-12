#include<iostream>
#include<unordered_map>

enum Trit{ False, Unknown, True };

const unsigned int trit_size = sizeof(unsigned int)* 8 / 2;//����������� � ������
const unsigned int bit_size = sizeof(unsigned int)* 8;//����������� � �����

class TritSet {
private:
	unsigned int *data;//������
	unsigned int init_capacity;//
	unsigned int ptr_last;//��������� ������� � ptr
	unsigned int capacity; // ����������� � uint'��
	unsigned int Last_changed_trit;//��������� ���������� ����
	class Reference {//������-�����, ������� ������������ ������ �� ���� (�����)
	private:
		friend class TritSet;
		TritSet *ptr;
		unsigned int index;//������ �������� ��������
		unsigned int BitShift;
		unsigned int ByteShift;
		void set_trit(int, int);//���������� ����
		void set_bit(int, int);//���������� ���
	public:
		Reference(TritSet *, unsigned int, unsigned int);//�����������
		~Reference();//����������
		Reference& operator=(Trit);//����������� �������� � ����, �� ������� ��������� ������
		Reference& operator=(const Reference&);//����������� �������� � ����, �� ������� ��������� ������
		Trit operator&(Trit);//and
		Trit operator|(Trit);//or
		Trit operator~() const;//���������� ��������������� �������� �����, �� ������� ��������� ������
		operator Trit() const;//���������� �������� �� �����, �� ������� ��������� ������
		friend std::ostream& operator<<(std::ostream &, const TritSet::Reference&);
	};
public:
	TritSet();//����������� �� ��������� 
	TritSet(TritSet const &);
	explicit TritSet(unsigned int);
	~TritSet();//����������
	Reference operator[](unsigned int);//������ � ����������� �����
	TritSet operator~() const;
	TritSet operator&(TritSet &) const;//and
	TritSet operator|(TritSet &) const;//or
	bool operator==(TritSet &set_) const;
	bool TritSet::operator!=(TritSet &set_) const;
	friend std::ostream& operator<<(std::ostream &, const TritSet &);
	Trit Shrink();//�������� ��������� ������ �� ���������� �������� ��� �� ��������, ��������� ��������� ����
	void Trim(size_t);//�������� ����� �� ���������� ������� � �����
	size_t length();
	size_t cardinality(Trit value);
	void reallocate(unsigned int);//������������ ������ ��� �������� ���������� ���������� ������
	std::unordered_map< Trit, int, std::hash<int> > cardinality();
	int Any(const Trit);
	int None(Trit);
	int Unkn(Trit);
	unsigned int * get_set() const;
	unsigned int get_capacity() const;
	unsigned int get_uint_capacity() const;
};
