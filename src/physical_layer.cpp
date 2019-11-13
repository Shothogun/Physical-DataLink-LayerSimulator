#include "../include/physical_layer.hpp"

void AplicacaoTransmissora (void) {
  std::string mensagem;
  std::cout << "Digite uma mensagem:" << std::endl;
  std::cin >> mensagem;
  //chama a proxima camada
  CamadaDeAplicacaoTransmissora(mensagem); //em um exemplo mais realistico, aqui seria dado um SEND do SOCKET
}//fim do metodo AplicacaoTransmissora

void CamadaDeAplicacaoTransmissora (std::string mensagem) {
  //int quadro [] = mensagem //trabalhar com bits!!!
  //chama a proxima camada
  int* quadro;
  CamadaFisicaTransmissora(quadro);
}//fim do metodo CamadaDeAplicacaoTransmissora

void CamadaFisicaTransmissora (int quadro[]) {
  int tipoDeCodificacao = 0; //alterar de acordo o teste
  int* fluxoBrutoDeBits; //ATENÇÃO: trabalhar com BITS!!!
  switch (tipoDeCodificacao) {
  case COD_BIN : //codificao binaria
    fluxoBrutoDeBits = 
    CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
    break;
  case COD_MANCH : //codificacao manchester
    fluxoBrutoDeBits = 
    CamadaFisicaTransmissoraCodificacaoManchester(quadro);
    break;
  case COD_MANCH_DIF : //codificacao manchester diferencial
    fluxoBrutoDeBits = 
    CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(quadro);
    break;
  }//fim do switch/case

  MeioDeComunicacao(fluxoBrutoDeBits);
}//fim do metodo CamadaFisicaTransmissora

// Função que realiza a codificação binária para um quadro
// na camada transmissora
int* CamadaFisicaTransmissoraCodificacaoBinaria (int quadro []) {
  return quadro;
}//fim do metodo CamadaFisicaTransmissoraCodificacaoBinaria

int* CamadaFisicaTransmissoraCodificacaoManchester (int quadro []) {
  //implementacao do algoritmo
}//fim do metodo CamadaFisicaTransmissoraCodificacaoManchester

std::vector<int> CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(std::vector<int> quadro){
  // Quadro codificado em mancheste diferencial
  std::vector<int> quadro_manchester_diferencial;

  // Bits from manchester code
  int first_bit = 1;
  int second_bit = 0;

  // Bit de iteração do quadro codificado
  std::vector<int>::iterator bit = quadro_manchester_diferencial.begin()++;

  // Começa com 1 e 0
  quadro_manchester_diferencial.push_back(first_bit);
  quadro_manchester_diferencial.push_back(second_bit);

  // Percorre o Quadro original
  // Começa a codificar a partir do segundo bit, 
  // o primeiro bit por padrão é "0 1"
  for(std::vector<int>::iterator it=quadro.begin()+1;
     it<quadro.end(); ++it) {

    // Se for um, não há transição nos intervalos entre bits
    // Se for zero, deve haver a transição. 
    // Logo, não inverte o padrão do par de bits.
    if(*it == 1) {
      first_bit ^= 0x1;
      second_bit ^= 0x1;
    }

    // Se for diferente de 0 ou 1, reportar erro
    else if(*it != 0) {
     std::cout << "\033[1;31m\ERROR! Bit inválido em Codificação Manchester\033[0m\n";
    }

    // O código Manchester possui o dobro de bits!
    quadro_manchester_diferencial.push_back(first_bit);
    quadro_manchester_diferencial.push_back(second_bit);
	}

  return quadro_manchester_diferencial;
}//fim do CamadaFisicaTransmissoraCodificacaoManchesterDiferencial

/* Este metodo simula a transmissao da informacao no meio de
* comunicacao, passando de um pontoA (transmissor) para um
* ponto B (receptor)
*/
void MeioDeComunicacao (int fluxoBrutoDeBits[]) {
  //OBS IMPORTANTE: trabalhar com BITS e nao com BYTES!!!
  int* fluxoBrutoDeBitsPontoA, *fluxoBrutoDeBitsPontoB;
  fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

  /* Código do Geraldo
  while (fluxoBrutoDeBitsPontoB.lenght!=
  fluxoBrutoDeBitsPontoA) {
    fluxoBrutoBitsPontoB += fluxoBrutoBitsPontoA; //BITS! Sendo transferidos
  }//fim do while
  */

  //chama proxima camada
  CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}//fim do metodo MeioDeTransmissao

void CamadaFisicaReceptora (int quadro[]) {
  int tipoDeDecodificacao = 0; //alterar de acordo o teste
  int* fluxoBrutoDeBits; //ATENÇÃO: trabalhar com BITS!!!
  switch (tipoDeDecodificacao) {
  case COD_BIN : //codificao binaria
    /* Código do Geraldo
    fluxoBrutoDeBits =
    CamadaFisicaReceptoraDecodificacaoBinaria(quadro);
    */
    break;
  case COD_MANCH: //codificacao manchester
    /* Código do Geraldo
    fluxoBrutoDeBits =
    CamadaFisicaReceptoraDecodificacaoManchester(quadro);
    */
    break;
  case COD_MANCH_DIF: //codificacao manchester diferencial
    /* Código do Geraldo
    fluxoBrutoDeBits =
    CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(quadro);
    */
    break;
  }//fim do switch/case
  //chama proxima camada
  CamadaDeAplicacaoReceptora(fluxoBrutoDeBits);
}//fim do metodo CamadaFisicaTransmissora

// Faz a codificação binária do quadro para camada receptora
int* CamadaFisicaReceptoraCodificacaoBinaria (int quadro []) {
  return quadro;
}//fim do metodo CamadaFisicaReceptoraDecodificacaoBinaria

int* CamadaFisicaReceptoraCodificacaoManchester (int quadro []) {
  //implementacao do algoritmo para DECODIFICAR
}//fim do metodo CamadaFisicaReceptoraDecodificacaoManchester

std::vector<int> CamadaFisicaReceptoraCodificacaoManchesterDiferencial(std::vector<int> quadro){
  std::vector<int> quadro_manchester_diferencial_decodificado;

  // Bits from manchester code
  int first_bit = 1;
  int second_bit = 0;
  int previous_first_bit = 1;
  int previous_second_bit = 0;
  int invert_first_bit;
  int invert_second_bit;

  // Primeiro bit por padrão é 1
  quadro_manchester_diferencial_decodificado.push_back(1);

  // Percorre o Quadro Codificado
  // Os dois primeiros bits são sempre 0 e 1,
  // que representa 1 na decodificação
  for(std::vector<int>::iterator it=quadro.begin()+2;
     it<quadro.end(); it += 2) {

    first_bit = *it;
    it++;
    second_bit = *it;
    it--;

    invert_first_bit  = (previous_first_bit)^(0x1);
    invert_second_bit = (previous_second_bit)^(0x1);

    if(first_bit != invert_first_bit && second_bit != invert_second_bit){
      quadro_manchester_diferencial_decodificado.push_back(0);
    }

    else if(first_bit == invert_first_bit && second_bit == invert_second_bit){
      quadro_manchester_diferencial_decodificado.push_back(1);
    }

    else{
      std::cout << "\033[1;31m\ERROR! Bit inválido em Codificação Manchester\033[0m\n";
    }

    previous_first_bit = first_bit;
    previous_second_bit = second_bit;
  }

  return quadro_manchester_diferencial_decodificado;

  //implementacao do algoritmo para DECODIFICAR
}//fim do CamadaFisicaReceptoraDecodificacaoManchesterDiferencial

void CamadaDeAplicacaoReceptora (int quadro []) {
  /* Código do Geraldo
    std::string mensagem = quadro; //estava trabalhando com bits
  */

  //chama proxima camada

  /* Código do Geraldo
    AplicacaoReceptora(mensagem);
  */
}//fim do metodo CamadaDeAplicacaoReceptora

void AplicacaoReceptora (std::string mensagem) {
  std::cout << "A mensagem recebida foi:" << mensagem << std::endl;
}//fim do metodo AplicacaoReceptora
