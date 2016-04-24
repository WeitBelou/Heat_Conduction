#include "material.h"

Material::Material(double ro, double lambda, double c)
{
	m_ro = ro;
	m_lambda = lambda;
	m_c = c;
}

Material::Material(const Material & other)
{
	m_ro = other.ro();
	m_lambda = other.lambda();
	m_c = other.c();
}

const Material Material::operator =(const Material& other)
{
	setRo(other.ro());
	setLambda(other.lambda());
	setC(other.c());
	return *this;
}

double Material::p() const
{
	return m_p;
}

void Material::setP(double p)
{
	m_p = p;
}

double Material::lambda() const
{
	return m_lambda;
}

void Material::setLambda(double lambda)
{
	m_lambda = lambda;
}

double Material::c() const
{
	return m_c;
}

void Material::setC(double c)
{
	m_c = c;
}
