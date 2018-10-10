// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp), MaxPower(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength())
{
}

TSet::operator TBitField()
{
	return this->BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (Elem >= MaxPower)throw - 2; // за границей
	if (BitField.GetBit(Elem) == 1) return 1;
	return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem >= MaxPower)throw - 2; // за границей
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem >= MaxPower)throw - 2; // за границей
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (MaxPower != s.MaxPower)return 0;
	return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (MaxPower == s.MaxPower)return 0;
	return BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet t(*this);
	t.BitField = t.BitField | s.BitField;
	return t;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet t(*this);
	t.InsElem(Elem);
	return t;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet t(*this);
	t.DelElem(Elem);
	return t;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet t(*this);
	t.BitField = t.BitField & s.BitField;
	return t;
}

TSet TSet::operator~(void) // дополнение
{
	TSet t(*this);
	t.BitField = ~t.BitField;
	return t;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	istr >> s.MaxPower >> s.BitField;
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << s.MaxPower << s.BitField;
	return ostr;
}
