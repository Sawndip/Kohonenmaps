#include "neuron.hpp"

neuron::neuron(int dimensionality)
{
	setDimensions(dimensionality);

	weights = new double[getDimensions()];

	for(int c=0;c<getDimensions();c++)
	{
		weights[c] = Random::get(1.l, 0.l);
	}
}
void	neuron::setDimensions(int d)
{	if(d>0)
	{
		dimensions = d;
	}
	else
	{
		std::cout<<"Dimensionality must be above zero"<<std::endl;
	}

}
int		neuron::getDimensions(void)
{
	return dimensions;
}
void	neuron::setWeight(int p,double v)
{
	if(p>-1 && p < getDimensions())
	{
		weights[p] = v;
	}
	else
	{
			std::cout<<"Invalid input for setWeight = "<<p<<" Dimensions = "<<getDimensions()<<std::endl;
	}
}
double	neuron::getWeight(int p)
{
	if(p>-1 && p < getDimensions())
	{
		return weights[p];
	}
	else
	{
		std::cout<<"Invalid input for getWeight = "<<p<<" Dimensions = "<<getDimensions()<<std::endl;
		return 0;
	}
}
void	neuron::display(void)
{
	std::cout<<"Dimensionality: "<<getDimensions()<<std::endl;
	for(int c=0;c<getDimensions();c++)
		std::cout<<"W["<<c<<"]: "<<weights[c]<<std::endl;
}
