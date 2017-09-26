#ifndef NEURON_HPP_
#define NEURON_HPP_
#include <iostream>
#include "random.hpp"
using Random = effolkronium::random_static;
class neuron
{	private:
		int dimensions;
		double *weights;
	public:
		neuron(int dimensionality);
		void	setDimensions(int d);
		int		getDimensions(void);
		void	setWeight(int p,double v);
		double	getWeight(int p);
		void	display(void);
};



#endif /* NEURON_HPP_ */
