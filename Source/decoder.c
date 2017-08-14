#include "header.h"

MENSAGEM mensagemToDecode;
IMAGEM imageToDecode;
int COUNT;

void decoder(char *format, char *mensagem, int sflag){
	if(strcmp(format, "ppm")==0||strcmp(format, "PPM")==0)
		imageToDecode = startPPM(0);
	else if(strcmp(format, "bmp")==0||strcmp(format, "BMP")==0)
		imageToDecode = startBMP();
	else{
		fprintf(stderr, "Formato nao suportado, apenas ppm e bmp.\n");
		return;
	}
	imageToDecode.imagem=NULL;
	mensagemToDecode.size=91;
	mensagemToDecode.texto=(char*)calloc(mensagemToDecode.size,sizeof(char));
	DecodificarMensagem();
	escreverMensagem(sflag,mensagem);
}
void DecodificarTamanho(){
	mensagemToDecode.size=0;
	unsigned char temp;
	for(COUNT=0; COUNT < 31; COUNT++){
		mensagemToDecode.size = mensagemToDecode.size << 1;
		temp=imageToDecode.pixels[COUNT];
		if((temp & 1)==1)
			mensagemToDecode.size++;
	}
	mensagemToDecode.texto=(char*)calloc(mensagemToDecode.size,sizeof(char));
	return;
}
void DecodificarMensagem(){
	COUNT=31;
	int numCoppied = 0;
	int idx = 0;
  	for(int i = 0; i < mensagemToDecode.size*8; i++) {
	    COUNT++;
	    numCoppied++;
	    if((imageToDecode.pixels[COUNT]&1)==1)
	    	mensagemToDecode.texto[idx]++;
	   	if(numCoppied==8){
	   		idx++;
	   		numCoppied=0;
	   	}else
			mensagemToDecode.texto[idx]<<=1;
	}
  	return;
}
void escreverMensagem(int sflag, char *mensagem){
	if(sflag==0){
		FILE* segredo = fopen(mensagem, "w");
		fwrite(mensagemToDecode.texto, sizeof(char), mensagemToDecode.size, segredo);
		fclose(segredo);
	}
	else
		fprintf(stdout, "%s\n", mensagemToDecode.texto);
}
