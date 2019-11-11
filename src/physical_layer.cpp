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
  case 0 : //codificao binaria
    fluxoBrutoDeBits = 
    CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
    break;
  case 1 : //codificacao manchester
    fluxoBrutoDeBits = 
    CamadaFisicaTransmissoraCodificacaoManchester(quadro);
    break;
  case 2 : //codificacao manchester diferencial
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

int* CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(int quadro []){
  //implementacao do algoritmo
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

int* CamadaFisicaReceptoraCodificacaoManchesterDiferencial(int quadro[]){
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
