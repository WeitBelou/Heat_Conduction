#ifndef MATERIAL_H
#define MATERIAL_H
#include <QTextStream>

class Material
{
public:
	Material();
	Material(double rho, double lambda, double c);
	Material(Material const& other);

	const Material operator =(const Material & other);

	double rho() const;
	void setRho(double rho);

	double lambda() const;
	void setLambda(double lambda);

	double c() const;
	void setC(double c);

	friend QTextStream & operator <<(QTextStream & os, const Material & m);
	friend QTextStream & operator >>(QTextStream & is, Material & m);
private:
	double m_rho;
	double m_lambda;
	double m_c;
};

Q_DECLARE_METATYPE(Material)

#endif // MATERIAL_H
