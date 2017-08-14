#include "header.h"
IMAGEM ppm;

IMAGEM startPPM(){
	ppm.size = filesize(imagemOriginal);
  lerHeaderPPM();
	lerPixelsPPM();
  return ppm;
}
void lerHeaderPPM(){
  ppm.headerSize=1;
  ppm.header= malloc(ppm.headerSize);
  int count=0;
  while(1){
    fread(&ppm.header[ppm.headerSize-1], sizeof(unsigned char), 1, imagemOriginal);
    if(ppm.header[ppm.headerSize-1]==10){//checa se o caracter eh um \n, na terceira quebra de linha comeca a area de dados.
      count++;
    }
    if(count == 3)//count = 3, fim do cabecario.
      break;
    ppm.headerSize++;
    ppm.header = realloc(ppm.header, ppm.headerSize);//realoca com mais 1 byte.
  }
}

void lerPixelsPPM(){
  ppm.pixels=malloc(ppm.size - ppm.headerSize);//aloca pixeis
  fread(ppm.pixels, sizeof(unsigned char), ppm.size - ppm.headerSize, imagemOriginal);//ler os pixels.
}