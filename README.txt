Foi implementado a esteganografia dos formatos BMP e PPM.
Nao foi possivel fazer a steganografia dos formatos que possuem compressao.
Ao final do projeto, refletimos que se fossemos fazer o projeto de novo, fariamos tambem a esteganografia dos formatos com compressao.
Para compilar o projeto, voce deve escrever no terminal(estando na pasta em que os arquivos se encontram):
  c99 BMP.c PPM.c decoder.c encoder.c steg.c mensagem.c -o steg -g -W
Para executar o progama:  
  /steg -e -i <input-file> -f <format> <image>
  /steg -d -o <output-file> -f <format> <image>
O projeto foi desenvolvido por 	Matheus Rangel De Melo e Joao Victor Fernandes Cabral.
