#include "header.h"

MENSAGEM lermensagem(char *msgLocation){
	FILE* mensagemtxt;
	MENSAGEM mensagem;
	mensagemtxt = fopen(msgLocation, "r");
	mensagem.size = (int)filesize(mensagemtxt);
	mensagem.texto=malloc(mensagem.size);
	fread(mensagem.texto, 1, mensagem.size, mensagemtxt);
	return mensagem;
}