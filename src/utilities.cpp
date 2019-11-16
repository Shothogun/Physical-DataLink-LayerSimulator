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
