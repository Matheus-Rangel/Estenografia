#include "header.h"

MENSAGEM mensagemToEncode;
IMAGEM imageToEncode;
int COUNT=0;

void encoder(char *format, char *messageLocation){
	mensagemToEncode = lermensagem(messageLocation);
	if(strcmp(format, "ppm")==0||strcmp(format, "PPM")==0){
		imageToEncode = startPPM(1);
		imageToEncode.imagem=fopen("segredo.ppm","w");
	}
	else if(strcmp(format, "bmp")==0||strcmp(format, "BMP")==0){
		imageToEncode = startBMP(1);
		imageToEncode.imagem=fopen("segredo.bmp","w");
	}else {
		fprintf(stderr, "Formato nao suportado, apenas ppm e bmp.\n");
		return;
	}
	printf("%d %ld\n", imageToEncode.headerSize, imageToEncode.size);
	if(!imagemCabe())
		return;
	codificarTamanho();
	codificarMensagem();
	escrever();
	return;
}
int imagemCabe(){
	if(mensagemToEncode.size*8 > imageToEncode.size - imageToEncode.headerSize)
		return 0;
	else
		return 1;
}

void codificarTamanho() {//armazena o tamnho da mensagem em BYTES na imagem.
	unsigned char temp;
	int sizetmp;
	for(int i = 1;i <= (int)sizeof(int) * 8; i++){
		sizetmp = mensagemToEncode.size >> (sizeof(int)*8)-i;
		temp=imageToEncode.pixels[COUNT];
		if((temp & 1) == 1 && (sizetmp & 1) == 0)
			temp--;
		if((temp & 1) == 0 && (sizetmp & 1) == 1)									
			temp++;
		COUNT++;
	}
}
void codificarMensagem() {
	int numCoppied = 0;
	unsigned char temp;
	char current;
	int idx = 0;
  	for(int i = 0; i < mensagemToEncode.size*8; i++) {
	    temp = imageToEncode.pixels[COUNT];
	    current = mensagemToEncode.texto[idx];
	    current >>= 7 - numCoppied;
	    numCoppied++;
		if((current & 1) == 1 && (temp & 1) == 0)
	      	temp++;
	    if((current & 1) == 0 && (temp & 1) == 1)
	      	temp--;
	    if(numCoppied == 8) {
	      	idx++;
	      	numCoppied = 0;
	    }
	   	imageToEncode.pixels[COUNT]=temp;
	   	COUNT++;
	}
  	return;
}
void escrever(){
	fwrite(imageToEncode.header, sizeof(unsigned char), imageToEncode.headerSize, imageToEncode.imagem);
	fwrite(imageToEncode.pixels, imageToEncode.size - imageToEncode.headerSize,1 , imageToEncode.imagem);
	fclose(imageToEncode.imagem);
	return;
}