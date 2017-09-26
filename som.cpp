#include "som.hpp"
som::som(int mapDimensions,int neuronDimensions, double initialLearningRate)
{
	setDimensions(mapDimensions);
	setNeuronDimensions(neuronDimensions);
	learningRate = initialLearningRate;
	map = (member**)malloc(sizeof(member*)*mapDimensions);

	for(int c=0;c<getDimensions();c++)
	{
		map[c] = (member*)malloc(sizeof(member)*mapDimensions);
	}

	for(int l=0;l<getDimensions();l++)
		for(int c=0;c<getDimensions();c++)
		{
			map[l][c] = new neuron(neuronDimensions);
		}
}
void	som::setDimensions(int d)
{
	if(d>0)
	{
		dimensions = d;
	}
	else
	{
		std::cout<<"Dimensionality must be above zero"<<std::endl;
	}
}
int		som::getDimensions(void)
{
	return dimensions;
}
void	som::setNeuronDimensions(int d)
{
	if(d>0)
		{
			neuronDimensions = d;
		}
		else
		{
			std::cout<<"Dimensionality must be above zero"<<std::endl;
		}
}
int		som::getNeuronDimensions(void)
{
	return neuronDimensions;
}
void	som::display(void)
{
	for(int l=0;l<getDimensions();l++)
		for(int c=0;c<getDimensions();c++)
		{	std::cout<<"Map["<<l<<","<<c<<"]:"<<std::endl;
			(map[l][c])->display();
		}
}
void	som::training(dataset* trainingData,int maxIterations)
{
	double *Avet = new double[trainingData->getDimensionality()];
	cv::Mat anima;
	std::string animation = "Animation";
	int p,pl,pc,nr;
	double lr;
	image img;

	for(int k=0;k<maxIterations;k++)
	{
		//std::cout<<"Generation"<<(k+1)<<std::endl;

		for(int i=0;i<trainingData->getSize();i++)
		{
			for(int j=0;j<trainingData->getDimensionality();j++)
				Avet[j]=trainingData->getDataset(i,j,true);

			p = findBMU(Avet);

			pl = p/getDimensions();
			pc = p%getDimensions();
			nr = getNeighbourhoodRadius(k,maxIterations);
			lr = getLearnigRate(k,maxIterations);

			/*
			std::cout<<"BMU: "<<p<<" pl: "<<pl<<"pc: "<<pc<<
					" nr: "<<nr <<" lr: "<< lr <<std::endl;
			//*/
			for(int l=0;l<getDimensions();l++)
				for(int c=0;c<getDimensions();c++)
				{
					if(isInNeighbourhoodRadius(pl,pc,nr,l,c))
					{
						for(int c1=0;c1<getNeuronDimensions();c1++)
						{
							double dist = sqrt(pow(pc-c,2)+pow(pl-l,2));
							double wt = (map[l][c])->getWeight(c1);
							double alr = lr*learningRateRadiusInfluence((int)dist,nr);
							double wt1 = wt;
							wt1+=alr*(Avet[c1]-wt);

							(map[l][c])->setWeight(c1,wt1);
							/*
							if( (k == 1 || k == 100 || k == 300 || k ==500 || k == 800 || k == 999)) {
								std::cout<<"Generation"<<(k+1)<< " - l = " << l <<
									 "  c = " << c << " peso = " << c1 <<
									 " wt1 = " << wt1 << " lr = " << lr
									<<std::endl;
							}
							//*/
						}
					}
				}
		}

		//mapToFrame(anima,10);
		//img.display(animation,anima,50,true);
	}
}
int		som::findBMU(double* in)
{
	double Daux,Dmin,PosMin;
	for(int l=0;l<getDimensions();l++)
	{
		for(int c=0;c<getDimensions();c++)
		{	Daux=0;
			for(int k=0;k<getNeuronDimensions();k++)
			{
				Daux+=(in[k] - map[l][c]->getWeight(k))*(in[k] - map[l][c]->getWeight(k));
			}
			if((l==0 && c==0) || Daux < Dmin )
			{
				Dmin=Daux;
				PosMin = l*getDimensions()+c;
			}
		}
	}

	return PosMin;
}
int		som::getNeighbourhoodRadius(int k,int maxIterations)
{
	double raio = getDimensions()/2;
	double tConst = maxIterations/log(raio);
	double raioV = raio*exp(-k/tConst);
	return ((int)ceil(raioV));
}
double	som::getLearnigRate(int k,int maxIterations)
{

	return learningRate*exp(-(double)k/maxIterations);
}
double  som::learningRateRadiusInfluence(int dist,int neighbourhoodRadius)
{
  return exp(-(double)((dist*dist)/(2*neighbourhoodRadius)));
}
bool	som::isInNeighbourhoodRadius(int BMUl,int BMUc,int neighbourhoodRadius,int l,int c)
{
	bool alcanceL,alcanceC;

	alcanceL =  ((BMUl-neighbourhoodRadius) < l && l < (BMUl+neighbourhoodRadius));
	alcanceC =  ((BMUc-neighbourhoodRadius) < c && c < (BMUc+neighbourhoodRadius));

	return (alcanceC&alcanceL);
}
void	som::mapToFrame(cv::Mat& out,int target_resolution)
{
	int ratio = ceil(target_resolution/getDimensions());

	cv::Mat aux(getDimensions()*ratio,getDimensions()*ratio,CV_32FC3);

	for(int l=0;l<getDimensions()*ratio;l++)
		for(int c=0;c<getDimensions()*ratio;c++)
		{
				cv::Vec3f intensidade;
				intensidade.val[0] = (map[l/ratio][c/ratio])->getWeight(0);
				intensidade.val[1] = (map[l/ratio][c/ratio])->getWeight(1);
				intensidade.val[2] = (map[l/ratio][c/ratio])->getWeight(2);
				aux.at<cv::Vec3f>(cv::Point(l,c)) = intensidade;
		}
	aux.copyTo(out);

}
