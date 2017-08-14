#include "header.h"

IMAGEM bmp;

IMAGEM startBMP(){
	bmp.headerSize=54;//tamnho do cabecario, no caso de bmp sempre 54.
	bmp.size = filesize(imagemOriginal);//calcula o tamnho da imagem em bytes
	bmp.header = malloc(bmp.headerSize);//aloca o cabecario.
	bmp.pixels = malloc(bmp.size - bmp.headerSize);//aloca a area de dados da imagem.
	leituraBMP();
	return bmp;
}

void leituraBMP(){
	fread(bmp.header, sizeof(unsigned char), bmp.headerSize, imagemOriginal);//ler o cabecario.
	fread(bmp.pixels, sizeof(unsigned char), bmp.size - bmp.headerSize, imagemOriginal);//ler os pixels.
}

