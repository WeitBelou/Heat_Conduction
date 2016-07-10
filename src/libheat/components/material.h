#ifndef MATERIAL_H
#define MATERIAL_H
#include <QTextStream>

class Material
{
public:
	Material();
	Material (float rho, float lambda, float c);
	Material(Material const& other);

	Material & operator =(const Material & other);

	float rho () const;
	void  setRho (float rho);

	float lambda () const;
	void  setLambda (float lambda);

	float c () const;
	void  setC (float c);

	friend QTextStream & operator <<(QTextStream & os, const Material & m);
	friend QTextStream & operator >>(QTextStream & is, Material & m);
private:
	float m_rho;
	float m_lambda;
	float m_c;
};

Q_DECLARE_METATYPE(Material)

#endif // MATERIAL_H
