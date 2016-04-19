#ifndef LAYER_H
#define LAYER_H
#include <iostream>
#include <stdexcept>
template <typename T>
class TemplateLayer
{
public:
	TemplateLayer();
	TemplateLayer(int _iMax, int _jMax);
	TemplateLayer(const TemplateLayer & previousLayer);
	~TemplateLayer();
	T operator()(int i, int j)const;
	T & operator()(int i, int j);
	void operator =(const TemplateLayer & anotherLayer);
	bool operator ==(const TemplateLayer & anotherLayer)const;
	void print() const;
	int getImax() const
	{return iMax;}
	int getJmax() const
	{return jMax;}
private:
	int iMax, jMax;
	T ** m_matrix;
};

typedef TemplateLayer<bool> BoolNet;
typedef TemplateLayer<double> Layer;

template <typename T>
TemplateLayer<T>::TemplateLayer()
{
	// во избежание некоторых ошибок
		this->iMax = 0;
		this->jMax = 0;
		m_matrix = new T * [iMax];
			for (int i = 0; i < iMax; i++)
				m_matrix[i] = new T [jMax];

}

template <typename T>
TemplateLayer<T>::TemplateLayer(int _iMax, int _jMax)
{
	this->iMax = _iMax;
	this->jMax = _jMax;
	m_matrix = new T* [iMax];
		for (int i = 0; i < iMax; i++)
			m_matrix[i] = new T [jMax];

}

template <typename T >
TemplateLayer<T>::~TemplateLayer()
{
		for (int i = 0; i < iMax; i++)
			delete [] m_matrix[i];
		delete [] m_matrix;
}

template <typename T>
TemplateLayer<T>::TemplateLayer(const TemplateLayer & previousLayer)
{
	this->iMax = previousLayer.iMax;
	this->jMax = previousLayer.jMax;
	m_matrix = new T* [iMax];
		for (int i = 0; i < iMax; i++)
			m_matrix[i] = new T [jMax];
		for (int i = 0; i < iMax; i++)
		{
			for (int j = 0; j < jMax; j++)
			{
				m_matrix[i][j] = previousLayer(i, j);
			}
		}
}

template <typename T>
void TemplateLayer<T>::operator =(const TemplateLayer & anotherLayer)
{
	if (*this == anotherLayer)
		{ }
	else
	{
		for (int i = 0; i < iMax; i++)
			delete [] m_matrix[i];
		delete [] m_matrix;

		this->iMax = anotherLayer.iMax;
		this->jMax = anotherLayer.jMax;
		m_matrix = new T* [iMax];
			for (int i = 0; i < iMax; i++)
				m_matrix[i] = new T [jMax];
			for (int i = 0; i < iMax; i++)
			{
				for (int j = 0; j < jMax; j++)
				{
					m_matrix[i][j] = anotherLayer(i, j);
				}
			}



	}
}

template <typename T>
bool TemplateLayer<T>::operator ==(const TemplateLayer & anotherLayer) const
{
	if (this->getImax() != anotherLayer.getImax() || (this->getImax() != anotherLayer.getImax()))
	return false;
	for (int i = 0; i < iMax; i++)
	{
		for (int j = 0; j < jMax; j++)
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
	if ((i > iMax-1) || (j > jMax-1) || (i < 0) || (j < 0))
		throw std::range_error("Попытка получить температуру несуществующей точки ");

	return m_matrix[i][j];
}

template <typename T>
T & TemplateLayer<T>::operator()(int i, int j)
{
	if ((i > iMax-1) || (j > jMax-1) || (i < 0) || (j < 0))
		throw std::range_error("Попытка получить температуру несуществующей точки");

	return m_matrix[i][j];
}


template <typename T>
void TemplateLayer<T>::print() const
{
	for (int i = 0; i<iMax; i++)
	{
		for (int j = 0; j<jMax; j++)
		{std::cout << "[" << m_matrix[i][j] << "]";}
		std::cout << std::endl;
	}

}
#endif // LAYER_H
