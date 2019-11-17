#include "../include/utilities.hpp"

std::vector<int> CriarVetorBits(std::string mensagem) {
  std::vector<int> quadro_resultante(mensagem.size()*8, 0);
  
  int bit, pos_letra = 0;
  // Percorrendo cada letra da mensagem
  for(char letra : mensagem) {
	// Percorrendo cada bit de uma letra
	for (bit = 7; bit >= 0; bit--) {
	  // pos_letra -> indica a letra atual
	  // bit       -> indica o bit atual
	  // Estou considerando por exemplo para a primeira letra
	  // MSB em quadro_resultante[0] e LSB em quadro_resultante[7]
	  // Para a segunda letra:
	  // MSB em quadro_resultante[8] e LSB em quadro_resultante[15]
	  quadro_resultante[pos_letra*8 + bit] = (letra >> (7 - bit)) & 1;
	}
	pos_letra++;
  }

  return quadro_resultante;
}

std::string CriarString(std::vector<int> quadro) {
  int size = quadro.size() / 8;
  std::string resultado(size, ' ');

  // Verificar o comentário na função CriarVetorbits() para saber
  // o padrão utilizado para a conversão
  int cont, atual = 0;
  for (cont = 0; cont < (int)resultado.size(); cont++) {
	resultado[atual] = LerCaractere(quadro, atual);
	atual++;
  }

  return resultado;
}

char LerCaractere(std::vector<int> quadro, int letra_atual) {
  int bit;
  char letra = 0;
  for (bit = 0; bit < 8; bit++) {
    letra |= quadro[letra_atual*8 + bit] << (7 - bit);
  }
  return letra;
}

std::vector<int> InserirCaractere(std::vector<int> quadro, char caractere) {
  std::vector<int> result(quadro.size() + 8, 0);
  int i, bit;
  for (i = 0; i < (int)quadro.size(); i++) {
    result[i] = quadro[i];
  }

  for (i = quadro.size(), bit = 0; i < (int)result.size(); i++, bit++) {
    result[i] = caractere >> (7 - bit);
  }

  return result;
}
