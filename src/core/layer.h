#ifndef LAYER_H
#define LAYER_H
#include <iostream>
#include <stdexcept>
#include <QTextStream>
template <typename T>
class TemplateLayer
{
public:
	TemplateLayer();
	TemplateLayer(int iMax, int jMax);
	TemplateLayer(const TemplateLayer & previousLayer);
	~TemplateLayer();
	T operator()(int i, int j)const;
	T & operator()(int i, int j);
	TemplateLayer operator =(const TemplateLayer & anotherLayer);
	bool operator ==(const TemplateLayer & anotherLayer)const;
	void print() const;
	int iMax() const;
	int jMax() const;
private:
	int m_iMax, m_jMax;
	T ** m_matrix;
};

typedef TemplateLayer<bool> BoolGrid;
typedef TemplateLayer<double> TemperatureField;

template <typename T>
TemplateLayer<T>::TemplateLayer()
{
	// во избежание некоторых ошибок
		this->m_iMax = 1;
		this->m_jMax = 1;
		m_matrix = new T * [m_iMax];
			for (int i = 0; i < m_iMax; i++)
				m_matrix[i] = new T [m_jMax];

}

template <typename T>
TemplateLayer<T>::TemplateLayer(int iMax, int jMax)
{
	this->m_iMax = iMax;
	this->m_jMax = jMax;
	m_matrix = new T* [m_iMax];
		for (int i = 0; i < m_iMax; i++)
			m_matrix[i] = new T [m_jMax];

}

template <typename T >
TemplateLayer<T>::~TemplateLayer()
{
		for (int i = 0; i < m_iMax; i++)
			delete [] m_matrix[i];
		delete [] m_matrix;
}

template <typename T>
TemplateLayer<T>::TemplateLayer(const TemplateLayer & previousLayer)
{
	this->m_iMax = previousLayer.m_iMax;
	this->m_jMax = previousLayer.m_jMax;
	m_matrix = new T* [m_iMax];
		for (int i = 0; i < m_iMax; i++)
			m_matrix[i] = new T [m_jMax];
		for (int i = 0; i < m_iMax; i++)
		{
			for (int j = 0; j < m_jMax; j++)
			{
				m_matrix[i][j] = previousLayer(i, j);
			}
		}
}

template <typename T>
TemplateLayer<T> TemplateLayer<T>::operator =(const TemplateLayer & anotherLayer)
{
	if (*this == anotherLayer)
		{ }
	else
	{
		for (int i = 0; i < m_iMax; i++)
			delete [] m_matrix[i];
		delete [] m_matrix;

		this->m_iMax = anotherLayer.m_iMax;
		this->m_jMax = anotherLayer.m_jMax;
		m_matrix = new T* [m_iMax];
			for (int i = 0; i < m_iMax; i++)
				m_matrix[i] = new T [m_jMax];
			for (int i = 0; i < m_iMax; i++)
			{
				for (int j = 0; j < m_jMax; j++)
				{
					m_matrix[i][j] = anotherLayer(i, j);
				}
			}
	}
	return *this;
}

template <typename T>
bool TemplateLayer<T>::operator ==(const TemplateLayer & anotherLayer) const
{
	if (this->iMax() != anotherLayer.iMax() || (this->jMax() != anotherLayer.jMax()))
	return false;
	for (int i = 0; i < m_iMax; i++)
	{
		for (int j = 0; j < m_jMax; j++)
		{
			if (m_matrix[i][j] != anotherLayer(i, j))
				return false;
		}

	}
	return true;
}

template <typename T >
T TemplateLayer<T>::operator()(int i, int j) const
{
	if ((i > m_iMax-1) || (j > m_jMax-1) || (i < 0) || (j < 0))
		throw std::range_error("Попытка получить температуру несуществующей точки ");

	return m_matrix[i][j];
}

template <typename T>
T & TemplateLayer<T>::operator()(int i, int j)
{
	if ((i > m_iMax-1) || (j > m_jMax-1) || (i < 0) || (j < 0))
		throw std::range_error("Попытка получить температуру несуществующей точки");

	return m_matrix[i][j];
}


template <typename T>
void TemplateLayer<T>::print() const
{
	for (int i = 0; i<m_iMax; i++)
	{
		for (int j = 0; j<m_jMax; j++)
		{std::cout << "[" << m_matrix[i][j] << "]";}
		std::cout << std::endl;
	}

}


template <typename T>
int TemplateLayer<T>::iMax() const
{
	return m_iMax;
}


template <typename T>
int TemplateLayer<T>::jMax() const
{
	return m_jMax;
}

inline QTextStream & operator <<(QTextStream & os, const BoolGrid & b)
{
	int iMax = b.iMax();
	int jMax = b.jMax();
	for (int i = 0; i < iMax; ++i){
		for (int j = 0; j < jMax; ++j) {
			if (b(i, j)) {
				os << QChar(0x25A0);
			}
			else {
				os << QChar(0x25A1);
			}
		}
		os << endl;
	}

	return os;
}

#endif // LAYER_H
