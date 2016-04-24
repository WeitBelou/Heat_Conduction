#ifndef MATERIAL_H
#define MATERIAL_H


class Material
{
public:
	Material();
	Material(double ro, double lambda, double c);
	Material(Material const& other);

	const Material operator =(const Material & other);

	double ro() const;
	void setRo(double ro);

	double lambda() const;
	void setLambda(double lambda);

	double c() const;
	void setC(double c);

private:
	double m_ro;
	double m_lambda;
	double m_c;
};

#endif // MATERIAL_H
