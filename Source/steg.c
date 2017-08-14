#include "header.h"
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[]){
	int eflag=0;
	int dflag=0;
	int sflag=0;
	char optc = 0;
	char *format = NULL;
	char *mensagem = NULL;//especifica qual arquivo abrir de texto
	char *image =NULL; //imagem a ser usada
	int c;
	if(argc!=7){
		fprintf(stderr, "Quantidade de argumentos incorreta.\n");
		return 1;
	}
	while((c= getopt(argc, argv, "edsi:o:f:"))!=-1){
		switch(c){
			case 'e':
				eflag=1;
				break; 
			case 'd':
				dflag=1;
				break;
			case 'i':
				if(eflag)
					mensagem=optarg;
				break;
			case 'o':
				if(sflag)
					break;
				if(dflag)
					mensagem=optarg;
				break;
			case 's':
				sflag=1;
				break;
			case 'f':
				format=optarg;
				break;
			case '?':
        		if (optopt == 'i'||optopt=='o'||optopt=='f')
          			fprintf (stderr, "Option -%c requires an argument.\n", optopt);
          		else
          			fprintf (stderr,"Unknown option character `\\x%x'.\n",optopt);
        			return 1;
			default:
				abort();
		}
		image=argv[optind];
	}
	abrirImagem(image);
	if(eflag)
		encoder(format, mensagem);
	if(dflag)
		decoder(format, mensagem, sflag);
	return 0;
	fclose(imagemOriginal);
}
void abrirImagem(char *image){
	imagemOriginal = fopen( image,"r");
	if( imagemOriginal == NULL ) {
		fprintf(stderr, "Erro na abertura da imagem!");
		_Exit (EXIT_FAILURE);
	}
}
long int filesize(FILE* arquivo){
	long int size;
	fseek(arquivo, 0l, SEEK_END);//calcula o tamanho total da imagem, colocando o indicador no final do arquivo.
	size=ftell(arquivo);
	fseek(arquivo, 0l, SEEK_SET);//coloca o indicador de volta  para o comeco.
	return size;//tamanho do arquivo em bytes
}
