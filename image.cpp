/* Biblioteca destinada a leitura e escrita de imagens utilizando a biblioteca OpencCV

 *
 *
 * Autor: Ricardo Medeiros
 * discente de Engenharia da Computão na Universidade Federal do Vale do São Francisco - UNIVASF
 *
 * Curso: "Visão Computacional: tópicos selecionados e aplicações com a biblioteca OpenCV"
 *
 * */
#include "image.hpp"

void image::read(std::string& name, cv::Mat& imageOut)
{
	imageOut = cv::imread(name);
}
void image::display(std::string& name,cv::Mat& image, int delay, bool destroy)
{
	cv::namedWindow(name,cv::WINDOW_AUTOSIZE);
	cv::imshow(name,image);
	cv::waitKey(delay);
	if(destroy)
		cv::destroyWindow(name);
}
bool image::store(std::string& name,cv::Mat& image)
{
	return cv::imwrite(name,image);
}
