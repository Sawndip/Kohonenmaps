#include "neuron.hpp"
#include "som.hpp"
#include "dataset.hpp"
int main()
{
	image img;
	cv::Mat frameInitial;
	cv::Mat frame;
	cv::Mat colors;
	std::string si = "Initial";
	std::string animation = "Animation";
	std::string s = "Final";
	std::string sc = "Colors";

	int NUM_NEURONIOS=100;
	int DIMENSAO=3;
	int TARGET_RESOLUTION = 1080;


	dataset *cores;

	int numEpocas = 100;
	int numCores = 6;
	double taxaAprendizado = 0.1;
	int sel = 1;

	do {
		std::cout << "Digite o número de cores: "<< std::endl;
		std::cin >> numCores;


		cores = new dataset(DIMENSAO,numCores);
		cores->generateRandomColorsSet();
		//cores->display();
		cores->datasetToFrame(colors,TARGET_RESOLUTION);
		img.display(sc,colors,1,false);

		//std::cout << "Deseja gerar outras cores? (Digite 0 se sim)"<< std::endl;
		//std::cin >> sel;
		if (!sel) {
			delete cores;
		}
	} while (!sel);

	std::cout << "Digite o número de épocas: ";
	std::cin >> numEpocas;

	std::cout << "Digite a taxa de aprendizado inicial: ";
	std::cin >> taxaAprendizado;


	som rede(NUM_NEURONIOS,DIMENSAO,taxaAprendizado);


	rede.mapToFrame(frameInitial,TARGET_RESOLUTION);
	img.display(si,frameInitial,1,false);


	rede.training(cores,numEpocas);

	rede.mapToFrame(frame,TARGET_RESOLUTION);

	img.display(s,frame);
}

