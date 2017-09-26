/* Biblioteca destinada a leitura e escrita de imagens utilizando a biblioteca OpenCV
 *
 *
 * Autor: Ricardo Medeiros
 * discente de Engenharia da Computão na Universidade Federal do Vale do São Francisco - UNIVASF
 *
 * Curso: "Visão Computacional: tópicos selecionados e aplicações com a biblioteca OpenCV"
 *
 * */
#ifndef IMAGE_HPP_
#define IMAGE_HPP_
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
class image
{	public:
	void read(std::string& name, cv::Mat& imageOut);
	void display(std::string& name,cv::Mat& image, int delay = 0, bool destroy = true);
	bool store(std::string& name,cv::Mat& image);
};
#endif /* IMAGE_HPP_ */
