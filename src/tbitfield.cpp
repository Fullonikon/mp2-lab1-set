// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	BitLen = len;
	MemLen= (len + sizeof(int) * 8 - 1) / (sizeof(int) * 8);
	pMem = new TELEM[MemLen];
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	for (int i = 0; i < MemLen; i++) pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	int nmem;
	nmem = (n + sizeof(int) * 8 - 1) / (sizeof(int) * 8);
	return nmem;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM t = 1 << n%sizeof(int);
	return t;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n >= BitLen) throw - 1; // за границей
	int nm = (n + sizeof(int) * 8 - 1) / (sizeof(int) * 8);
	pMem[nm] = pMem[nm] | (1 << (n % (sizeof(int))));
	return;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= BitLen) throw - 1; // за границей
	int nm = (n + sizeof(int) * 8 - 1) / (sizeof(int) * 8);
	pMem[nm] = pMem[nm] & (~(1 << (n % (sizeof(int)))));
	return;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n >= BitLen) throw - 1; // за границей
	int t = pMem[GetMemIndex(n)];
	t = (t & GetMemMask(n)) >> (n%GetMemIndex(n));
  return t;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int res = 1;
	if ((BitLen != bf.BitLen) || (MemLen != bf.MemLen)) res = 0;
	for (int i = 0; i < bf.BitLen; i++)
	{
		if (pMem[i] != bf.pMem[i])res = 0;
	}
  return res;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int res = 1;
	if ((BitLen == bf.BitLen) && (MemLen == bf.MemLen))
	{
		for (int i = 0; i < bf.BitLen; i++)
		{
			if (pMem[i] != bf.pMem[i])return 1;
		}
		return 0;
	}
	return res;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField a(BitLen);
	if (MemLen > bf.MemLen) for (int i = 0; i < MemLen; i++)
	{
		a.pMem[i] = pMem[i] | bf.pMem[i];
	}
	else for (int i = 0; i < bf.MemLen; i++)
	{
		a.pMem[i] = pMem[i] | bf.pMem[i];
	}
	return a;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField a(BitLen);
	if (MemLen > bf.MemLen) for (int i = 0; i < MemLen; i++)
	{
		a.pMem[i] = pMem[i] & bf.pMem[i];
	}
	else for (int i = 0; i < bf.MemLen; i++)
	{
		a.pMem[i] = pMem[i] & bf.pMem[i];
	}
	return a;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField a(BitLen);
	for (int i = 0; i < MemLen; i++) a.pMem[i] = ~pMem[i];
	return a;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	istr >> bf.BitLen >> bf.MemLen >> *bf.pMem;
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	ostr << "Bitlen = " << bf.BitLen << " MemLen = " << bf.MemLen << " pMem: " << '/n';
	for (int i = 0; i < bf.MemLen; i++) ostr << bf.pMem[i] << " ";
	ostr << '\n';
	return ostr;
}
