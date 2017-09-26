#include "dataset.hpp"
dataset::dataset(int d,int s)
{
	if(d >0 && s > 0)
	{	setDimensionality(d);
		setSize(s);

		set = (double**)malloc(sizeof(double*)*getSize());
		for(int c=0;c<getSize();c++)
			set[c] = (double*)malloc(sizeof(double)*getDimensionality());
	}
	else
	{
		std::cout<<"Dimensionality or size must be above zero"<<std::endl;
	}

}
dataset::dataset(int dimensionality,int size,double maxValue,double minValue,bool normalize)
{
	if(dimensionality >0 && size > 0 && maxValue > minValue)
	{
		setDimensionality(dimensionality);
		setSize(size);
		normalizationBase = fabs(minValue);
		normalizationRatio = 1/(sqrt(pow((maxValue-minValue),2.0)));
		normalized = normalize;

		set = (double**)malloc(sizeof(double*)*getSize());
				for(int c=0;c<getSize();c++)
					set[c] = (double*)malloc(sizeof(double)*getDimensionality());

	}
	else
	{
		std::cout<<"Dimensionality or size must be above zero, or maxValue < minValue"<<std::endl;
	}
}
void	dataset::setDimensionality(int d)
{
	dimensionality = d;
}
int		dataset::getDimensionality(void)
{
	return dimensionality;
}
void	dataset::setSize(int s)
{
	size = s;
}
int		dataset::getSize(void)
{
	return size;
}
double	dataset::normalize(double v)
{
	return ((v+normalizationBase)*normalizationRatio);
}
double	dataset::unnormalize(double v)
{
	return ((v/normalizationRatio)-normalizationBase);
}
void	dataset::read()
{

}
void	dataset::readFromFile(std::string file)
{	/*int size,dimensionality;

	std::ofstream f;
	f.open(file,std::ios::in);
	f>>size>>dimensionality;

	if(size == getSize() && dimensionality == getDimensionality())
	{
		for(int l=0;l<getSize();l++)
			for(int c=0;c<getDimensionality();c++)
				f>>set[l][c];

	}
	else
	{
		//dimensionalidade ou tamanho inválido.
	}
	*/
}
double	dataset::getDataset(int l,int c,bool normalized)
{
	if(l>-1 && l<getSize() && c>-1 && c<getDimensionality())
	{
		if(normalized && !dataset::normalized)
			return normalize(set[l][c]);
		else
		if(!normalized && dataset::normalized)
			return unnormalize(set[l][c]);
		else
			return set[l][c];

	}
	else
	{
		//posição invalida
		return 0;
	}
}
void	dataset::generateRandomColorsSet()
{
	double R,G,B;

	for(int l=0;l<getSize();l++)
	{
		R = Random::get(255.l, 0.l);
		G = Random::get(255.l, 0.l);
		B = Random::get(255.l, 0.l);
		set[l][0] = R;
		set[l][1] = G;
		set[l][2] = B;
	}
	normalizationBase = 0;
	normalizationRatio = 1.0/255;

}
void	dataset::display(void)
{
	for(int l=0;l<getSize();l++)
	{	std::cout<<"set["<<l<<"]: ";
		for(int c=0;c<getDimensionality();c++)
		{
			std::cout<<set[l][c]<<" ";
		}
		std::cout<<std::endl;
	}
}
void	dataset::datasetToFrame(cv::Mat& out,int target_resolution)
{
	int ratio = ceil(target_resolution/getSize());

	cv::Mat aux(getSize()*ratio,getSize()*ratio,CV_32FC3);
	for(int c=0;c<getSize()*ratio;c++)
	{
		for(int l=0;l<getSize()*ratio;l++)
		{
				cv::Vec3f intensidade;
				intensidade.val[0] = normalize(set[c/ratio][0]);
				intensidade.val[1] = normalize(set[c/ratio][1]);
				intensidade.val[2] = normalize(set[c/ratio][2]);
				aux.at<cv::Vec3f>(cv::Point(l,c)) = intensidade;
		}
	}
	aux.copyTo(out);
}
