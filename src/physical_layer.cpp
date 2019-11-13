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

// Faz a codificação do sinal para o formato Manchester
std::vector<int> CamadaFisicaTransmissoraCodificacaoManchester (std::vector<int> &quadro) {
  std::cout << "-----Codificacao Manchester-----" << std::endl;
  // Descobrir o tamanho do quadro pego
  unsigned long int tam = quadro.size();
  // Criar array que representará novo quadro com o dobro do tamanho
  int manchesterArray[tam*2];

  // Formar novo quadro por meio do xor entre o quadro antigo e um clock
  // de meio periodo começado em 0
  std::cout << "Clock:" << std::endl;
  for(unsigned int i = 0; i < tam; i++){
    // Clock = 0
    std::cout << "0";
    if(quadro[i] == 0){
      manchesterArray[i*2] = 0;
    }else{
      manchesterArray[i*2] = 1;
    }
    // Clock = 1
    std::cout << "1";
    if(quadro[i] == 1){
      manchesterArray[i*2+1] = 0;
    }else{
      manchesterArray[i*2+1] = 1;
    }
  }

  // Criar vetor com a codificacao manchester
  std::vector<int> novo_quadro;
  novo_quadro.insert(novo_quadro.begin(), manchesterArray, manchesterArray + tam*2);
  // Imprimir novo quadro
  std::cout << std::endl << "Quadro com a codificacao Manchester:" << std::endl;
  for(auto j = novo_quadro.begin(); j != novo_quadro.end(); ++j){
    std::cout << *j;
  }
  std::cout << std::endl;
  std::cout << "--------------------------------" << std::endl;

  return novo_quadro;
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

// Faz a decodificação de um sinal em formato Mnachester
std::vector<int> CamadaFisicaReceptoraCodificacaoManchester (std::vector<int> &quadro) {
  std::cout << "----Decodificacao Manchester----" << std::endl;
  // Descobrir o tamanho do quadro pego
  unsigned long int tam = quadro.size();
  // Criar array que representará novo quadro com a metade do tamanho
  unsigned long int novoTam = tam/2;
  int decodeArray[novoTam];

  // Achar quadro original verificando se, no periodo de dois bits
  // ocorre uma subida ou descida
  for(unsigned int i = 0; i < novoTam; i++){
    // Verificar se é subida
    if(quadro[i*2] == 0 && quadro[i*2+1] == 1){
      decodeArray[i] = 0;
    }
    // Verificar se é descida
    else if(quadro[i*2] == 1 && quadro[i*2+1] == 0){
      decodeArray[i] = 1;
    }
    // Apontar erro caso não for nem descida nem subida
    else{
      std::cout << "ERRO!" << std::endl;
    }
  }

  // Criar vetor com a decodificacao manchester
  std::vector<int> novo_quadro;
  novo_quadro.insert(novo_quadro.begin(), decodeArray, decodeArray + novoTam);
  // Imprimir novo quadro
  std::cout << "Quadro com a decodificacao Manchester:" << std::endl;
  for(auto j = novo_quadro.begin(); j != novo_quadro.end(); ++j){
    std::cout << *j;
  }
  std::cout << std::endl;
  std::cout << "--------------------------------" << std::endl;

  return novo_quadro;
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
