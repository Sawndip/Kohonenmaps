#ifndef DATASET_HPP_
#define DATASET_HPP_
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>
#include "image.hpp"
#include "random.hpp"
using Random = effolkronium::random_static;

class dataset
{	private:
		double **set;
		int dimensionality;
		int size;
		bool normalized;
		double	normalizationRatio;// é o valor que é usado para levar o valor do espaço não normalizado ao espaço normalizado
		double	normalizationBase;// é o valor absoluto do menor valor do dataset não normalizado
	public:
				dataset(int dimensinality,int size);
				dataset(int dimensionality,int size,double maxValue,double minValue,bool normalize=true);
		void	setDimensionality(int d);
		int		getDimensionality(void);
		void	setSize(int s);
		int		getSize(void);
		double	getDataset(int l,int c,bool normalized=true);
		void	read();
		void	readFromFile(std::string file);
		double	normalize(double v);
		double	unnormalize(double v);
		void	generateRandomColorsSet();
		void	display(void);
		void	datasetToFrame(cv::Mat& out,int ratio);
};




#endif /* DATASET_HPP_ */
