#include "material.h"

Material::Material()
{
	m_rho = 7800;
	m_lambda = 46;
	m_c = 460;
}

Material::Material(double ro, double lambda, double c)
{
	m_rho = ro;
	m_lambda = lambda;
	m_c = c;
}

Material::Material(const Material & other)
{
	m_rho = other.rho();
	m_lambda = other.lambda();
	m_c = other.c();
}

Material & Material::operator =(const Material& other)
{
	setRho(other.rho());
	setLambda(other.lambda());
	setC(other.c());
	return *this;
}

double Material::rho() const
{
	return m_rho;
}

void Material::setRho(double rho)
{
	m_rho = rho;
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

QTextStream & operator <<(QTextStream & os, const Material & m)
{
	//Rho = DOUBLE
	//Lambda = DOUBLE
	//C = DOUBLE

	os << "Rho = " << m.rho() << endl;
	os << "Lambda = " << m.lambda() << endl;
	os << "C = " << m.c() << endl;

	return os;
}

QTextStream & operator >>(QTextStream & is, Material & m)
{
	//DOUBLE DOUBLE DOUBLE

	double tmp;

	is >> tmp;
	m.setRho(tmp);

	is >> tmp;
	m.setLambda(tmp);

	is >> tmp;
	m.setC(tmp);

	return is;
}
