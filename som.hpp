#ifndef SOM_HPP_
#define SOM_HPP_
#include "neuron.hpp"
#include "dataset.hpp"
#include <cmath>
#include "image.hpp"
typedef neuron * member;
class som
{
	private:
		member ** map;
		int dimensions;
		int neuronDimensions;
		double learningRate;

	public:
					som(int mapDimensions,
							int neuronDimensions,
							double initialLearningRate = 0.1);
		void		setDimensions(int d);
		int			getDimensions(void);
		void		setNeuronDimensions(int d);
		int			getNeuronDimensions(void);
		void		display(void);
		void		training(dataset* trainingData,int maxIterations);
		int			findBMU(double*);
		int			getNeighbourhoodRadius(int k,int maxIterations);
		double		getLearnigRate(int k,int maxIterations);
		double		learningRateRadiusInfluence(int dist,int neighbourhoodRadius);
		bool		isInNeighbourhoodRadius(int BMUl,int BMUc,int neighbourhoodRadius,int l,int c);
		void 		mapToFrame(cv::Mat& out,int ratio);
};




#endif /* SOM_HPP_ */
