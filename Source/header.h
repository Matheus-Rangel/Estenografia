#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int headerSize;//tamanho do cabecario em bytes
	unsigned char *header;//armazena o cabecario da imagem
	unsigned char *pixels;//armazena a area de dados da imagem
	long int size;//tamanho total da imagem em bytes (header+pixels)
	FILE* imagem;
}IMAGEM;
typedef struct {
	int size;//tamanho da mensagem em bytes
	char *texto;
}MENSAGEM;

FILE* imagemOriginal;

//steg.c
void abrirImagem();
long int filesize(FILE* arquivo);//retorna o tamanho do arquivo em bytes
//mensagem.c
MENSAGEM lermensagem(char *msgLocation);
//char *escrevermensagem(MENSAGEM mensagem);
//encoder.c
void encoder(char *format, char *messageLocation);
int imagemCabe();
void codificarTamanho();
void codificarMensagem();
void escrever();
//decoder.c
void DecodificarTamanho();
void DecodificarMensagem();
void escreverMensagem(int sflag, char *mensagem);
void decoder(char *format, char *mensagem, int sflag);
//PPM.C
IMAGEM startPPM();
void lerHeaderPPM();
void lerPixelsPPM();
//BMP.C
IMAGEM startBMP();
void leituraBMP();
