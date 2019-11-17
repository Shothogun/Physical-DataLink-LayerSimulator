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
  std::vector<int> quadro;
  CamadaFisicaTransmissora(quadro);
}//fim do metodo CamadaDeAplicacaoTransmissora

void CamadaFisicaTransmissora (std::vector<int> quadro) {
  int tipoDeCodificacao = 0; //alterar de acordo o teste
  std::vector<int> fluxoBrutoDeBits; //ATENÇÃO: trabalhar com BITS!!!
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
std::vector<int> CamadaFisicaTransmissoraCodificacaoBinaria (std::vector<int> quadro) {
  std::cout << "-----Codificacao Binária-----" << std::endl;
  std::cout << "Quadro com a codificação Binária:" << std::endl;

  for (int bit : quadro) {
	std::cout << bit;
  }

  std::cout << std::endl;

  return quadro;
}//fim do metodo CamadaFisicaTransmissoraCodificacaoBinaria

// Faz a codificação do sinal para o formato Manchester
std::vector<int> CamadaFisicaTransmissoraCodificacaoManchester (std::vector<int> quadro) {
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

std::vector<int> CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(std::vector<int> quadro){
  // Quadro codificado em mancheste diferencial
  std::vector<int> quadro_manchester_diferencial;

  int first_bit;
  int second_bit;

  std::cout << "-----Codificacao Manchester Diferencial-----" << std::endl;

  // Bits do manchester code
  if(quadro[0] == 1){
    first_bit = 1;
    second_bit = 0;
  }

  else{
    first_bit = 0;
    second_bit = 1;
  }

  // Bit de iteração do quadro codificado
  std::vector<int>::iterator bit = quadro_manchester_diferencial.begin()++;

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

  // Imprimir novo quadro
  std::cout << std::endl << "Quadro com a codificacao Manchester Diferencial:" << std::endl;
  for(auto j = quadro_manchester_diferencial.begin(); j != quadro_manchester_diferencial.end(); ++j){
    std::cout << *j;
  }
  std::cout << std::endl;
  std::cout << "--------------------------------" << std::endl;

  return quadro_manchester_diferencial;
}//fim do CamadaFisicaTransmissoraCodificacaoManchesterDiferencial

/* Este metodo simula a transmissao da informacao no meio de
* comunicacao, passando de um pontoA (transmissor) para um
* ponto B (receptor)
*/
void MeioDeComunicacao (std::vector<int> fluxoBrutoDeBits) {
  //OBS IMPORTANTE: trabalhar com BITS e nao com BYTES!!!
  int erro, porcentagemDeErros;
  std::vector<int> fluxoBrutoDeBitsPontoA, fluxoBrutoDeBitsPontoB;
  fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

  porcentagemDeErros = 0; //10%, 20%, 30%, 40%, ..., 100%
  fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

  /* Código do Geraldo
  while (fluxoBrutoDeBitsPontoB.lenght!=
  fluxoBrutoDeBitsPontoA) {
    fluxoBrutoBitsPontoB += fluxoBrutoBitsPontoA; //BITS! Sendo transferidos
    if ((rand()%100)== ... ){ //fazer a probabilidade do erro
      fluxoBrutoBitsPontoB += fluxoBrutoBitsPontoA; //BITS!!!
    }
    else //ERRO! INVERTER (usa condicao ternaria){
      fluxoBrutoBitsPontoB==0) ?
      fluxoBrutoBitsPontoA=fluxoBrutoBitsPontoB++ :
      fluxoBrutoBitsPontoA=fluxoBrutoBitsPontoB--;
    }
}//fim do while
  }//fim do while
  */

  //chama proxima camada
  CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}//fim do metodo MeioDeTransmissao

void CamadaFisicaReceptora (std::vector<int> quadro) {
  int tipoDeDecodificacao = 0; //alterar de acordo o teste
  std::vector<int> fluxoBrutoDeBits; //ATENÇÃO: trabalhar com BITS!!!
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
std::vector<int> CamadaFisicaReceptoraCodificacaoBinaria (std::vector<int> quadro) {
  std::cout << "----Decodificacao Binária----" << std::endl;

  std::cout << "Quadro com a decodificação Binária:" << std::endl;

  for(int bit : quadro) {
	std::cout << bit;
  }

  std::cout << std::endl;
  
  return quadro;
}//fim do metodo CamadaFisicaReceptoraDecodificacaoBinaria

// Faz a decodificação de um sinal em formato Mnachester
std::vector<int> CamadaFisicaReceptoraCodificacaoManchester (std::vector<int> quadro) {
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

std::vector<int> CamadaFisicaReceptoraCodificacaoManchesterDiferencial(std::vector<int> quadro){
  std::vector<int> quadro_manchester_diferencial_decodificado;

  std::cout << "----Decodificacao Manchester Diferencial----" << std::endl;


  // Bits from manchester code
  int first_bit = 1;
  int second_bit = 0;
  int previous_first_bit = 1;
  int previous_second_bit = 0;

  // Se o manchester diferencial começa com 0 1,
  // o primeiro bit é 0 
  if(quadro[0] == 0){
    first_bit = 0;
    second_bit = 1;
    previous_first_bit = 0;
    previous_second_bit = 1;
    quadro_manchester_diferencial_decodificado.push_back(0);
  }

  // Se o manchester diferencial começa com 1 0,
  // o primeiro bit é 1
  else if(quadro[0] == 1) {
    first_bit = 1;
    second_bit = 0;
    previous_first_bit = 1;
    previous_second_bit = 0;
    quadro_manchester_diferencial_decodificado.push_back(1);
  }

  else{
    std::cout << "ERRO na codificacao Manchester Diferencial" << std::endl;
  }


  int invert_first_bit;
  int invert_second_bit;


  // Percorre o Quadro Codificado
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

  std::cout << "Quadro com a decodificacao Manchester Diferencial:" << std::endl;
  for(auto j = quadro_manchester_diferencial_decodificado.begin(); 
      j != quadro_manchester_diferencial_decodificado.end(); ++j)
  {
    std::cout << *j;
  }
  std::cout << std::endl;
  std::cout << "--------------------------------" << std::endl;

  return quadro_manchester_diferencial_decodificado;

  //implementacao do algoritmo para DECODIFICAR
}//fim do CamadaFisicaReceptoraDecodificacaoManchesterDiferencial

void CamadaDeAplicacaoReceptora (std::vector<int> quadro) {
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
