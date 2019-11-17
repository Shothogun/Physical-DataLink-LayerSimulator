#include "../include/data_link_layer.hpp"
#include "../include/utilities.hpp"

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemCaracteres (std::vector<int> quadro) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraContagemCaracteres

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoBytes (std::vector<int> quadro) {
  // Indica qual a posição dentro do quadro, usando caractere como medida
  int car_atual;
  char car_lido;
  std::vector<int> resultado;
  resultado = InserirCaractere(resultado, BYTE_FLAG);

  // Percorrendo o quadro por bytes
  for (car_atual = 0; car_atual < (int)(quadro.size()/8); car_atual++) {
	// Lendo o caractere atual do quadro
    car_lido = LerCaractere(quadro, car_atual);

	// Verificando se o caractere de dado é um especial
	if ((car_lido == BYTE_FLAG) || (car_lido == BYTE_ESC)) {
	  resultado = InserirCaractere(resultado, BYTE_ESC);
	}

	// Inserindo o caractere de dado no vetor resultante
	resultado = InserirCaractere(resultado, car_lido);
  }
  return InserirCaractere(resultado, BYTE_FLAG);
}//fim do metodo CamadaEnlaceDadosTransmissoraInsercaoBytes

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoBits (std::vector<int> quadro) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraInsercaoBits

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoViolacaoCamadaFisica (std::vector<int> quadro) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraViolacaoDaCamadaFisica

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramento (std::vector<int> quadro) {
  int tipoEnquadramento= 0; //alterar de acordo com o teste
  std::vector<int> quadroEnquadrado;
  switch (tipoEnquadramento) {
    case 0 : //contagem de caracteres
      quadroEnquadrado =
      CamadaEnlaceDadosTransmissoraEnquadramentoContagemCaracteres(quadro);
      break;
    case 1 : //insercao de bytes
      quadroEnquadrado =
      CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoBytes(quadro);
      break;
    case 2 : //insercao de bits
      quadroEnquadrado =
      CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoBits(quadro);
      break;
    case 3 : //violacao da camada fisica
      quadroEnquadrado =
      CamadaEnlaceDadosTransmissoraEnquadramentoViolacaoCamadaFisica(quadro);
      break;
  }//fim do switch/case

  return quadroEnquadrado;
}//fim do metodo CamadaEnlaceTransmissoraEnquadramento

std::vector<int> CamadaEnlaceDadosTransmissoraControleErroBitParidadePar (std::vector<int> quadro) {
  int paridade = 0;

  // Conta quantos bits 1 existem
  for(auto bit: quadro){
    paridade += bit;
  }

  // Se é ímpar, a paridade é 1
  if(paridade%2 == 1){
    quadro.push_back(1);
  }

  // Se é par, a paridade é 0
  else {
    quadro.push_back(0);
  }

  // Retorna o quadro com o Bit paridade
  return quadro;
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroBitParidadePar

std::vector<int> CamadaEnlaceDadosTransmissoraControleErroBitParidadeImpar (std::vector<int> quadro)
{
  int paridade = 0;

  // Conta quantos bits 1 existem
  for(auto bit: quadro){
    paridade += bit;
  }

  // Se é ímpar, a paridade é 0
  if(paridade%2 == 1){
    quadro.push_back(0);
  }

  // Se é par, a paridade é 1
  else {
    quadro.push_back(1);
  }

  // Retorna o quadro com o Bit paridade
  return quadro;
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroBitParidadeImpar

void CamadaEnlaceDadosTransmissoraControleErroCRC (std::vector<int> quadro) {
//implementacao do algoritmo
//usar polinomio CRC-32(IEEE 802)
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroCRC

void CamadaEnlaceDadosTransmissoraControleErroCodigoHamming (std::vector<int> quadro) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraControleDErroCodigohamming

std::vector<int> CamadaEnlaceDadosTransmissoraControleErro (std::vector<int> quadro) {
  int tipoControleErro = 0; //alterar de acordo com o teste
  switch (tipoControleErro) {
    case 0 : //bit de paridade par
      // Retorna quadro com bit paridade
      return CamadaEnlaceDadosTransmissoraControleErroBitParidadePar(quadro);
      break;
    case 1 : //bit de paridade impar
      // Retorna quadro com bit paridade
      return CamadaEnlaceDadosTransmissoraControleErroBitParidadeImpar(quadro);
      break;
    case 2 : //CRC
      //codigo
      break;
    case 3 : //codigo de Hamming
      //codigo
      break;
  }//fim do switch/case
}//fim do metodo CamadaEnlaceDadosTransmissoraControleErro

void CamadaEnlaceDadosTransmissoraControleFluxo (std::vector<int> quadro) {
//algum codigo aqui
}//fim do metodo CamadaEnlaceDadosTransmissoraControleFluxo

void CamadaEnlaceDadosTransmissora (std::vector<int> quadro) {
  quadro = CamadaEnlaceDadosTransmissoraEnquadramento(quadro);
  quadro = CamadaEnlaceDadosTransmissoraControleErro(quadro);
  CamadaEnlaceDadosTransmissoraControleFluxo(quadro);
  //chama proxima camada
  CamadaFisicaTransmissora(quadro);
}//fim do metodo CamadaEnlaceDadosTransmissora

std::vector<int> CamadaEnlaceDadosReceptoraEnquadramentoContagemCaracteres (std::vector<int> quadro) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosReceptoraContagemCaracteres

std::vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoBytes (std::vector<int>) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosReceptoraInsercaoBytes

std::vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoBits (std::vector<int>) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosReceptoraInsercaoBits

std::vector<int> CamadaEnlaceDadosReceptoraEnquadramentoViolacaoCamadaFisica (std::vector<int> quadro) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosReceptoraViolacaoDaCamadaFisica

void CamadaEnlaceDadosReceptoraEnquadramento (std::vector<int> quadro) {
  int tipoEnquadramento= 0; //alterar de acordo com o teste
  std::vector<int> quadroDesenquadrado;
  switch (tipoEnquadramento) {
  case 0 : //contagem de caracteres
    quadroDesenquadrado =
    CamadaEnlaceDadosReceptoraEnquadramentoContagemCaracteres(quadro);
    break;
  case 1 : //insercao de bytes
    quadroDesenquadrado =
    CamadaEnlaceDadosReceptoraEnquadramentoInsercaoBytes(quadro);
    break;
  case 2 : //insercao de bits
    quadroDesenquadrado =
    CamadaEnlaceDadosReceptoraEnquadramentoInsercaoBits(quadro);
    break;
  case 3 : //violacao da camada fisica
    quadroDesenquadrado =
    CamadaEnlaceDadosReceptoraEnquadramentoViolacaoCamadaFisica(quadro);
    break;
  }//fim do switch/case
}//fim do metodo CamadaEnlaceDadosReceptoraEnquadramento


void CamadaEnlaceDadosReceptoraControleErroBitParidadePar (std::vector<int> quadro ) {
  // Conta quantos bits 1 existe
  int paridade = 0;

  // Retira o último bit paridade 
  // e guarda para verificação
  int bit_paridade = quadro.back();
  quadro.pop_back();

  // Conta quantos bits 1 existem
  for(auto bit: quadro){
    paridade += bit;
  }

  // Condição de Erro
  // A paridade deve ser igual do bit paridade,
  // para provocar a paridade par
  if(paridade%2 != bit_paridade){
    std::cout << "ERRO: Bit paridade par incorrespondente" << std::endl;
  }
}//fim do metodo CamadaEnlaceDadosReceptoraControleErroBitParidadePar

void CamadaEnlaceDadosReceptoraControleErroBitParidadeImpar (std::vector<int> quadro ) {
  // Conta quantos bits 1 existe
  int paridade = 0;

  // Retira o último bit paridade 
  // e guarda para verificação
  int bit_paridade = quadro.back();
  quadro.pop_back();

  // Conta quantos bits 1 existem
  for(auto bit: quadro){
    paridade += bit;
  }

  // Condição de Erro
  // A paridade correta deve ser diferente do bit paridade,
  // para provocar a paridade impar
  if(paridade%2 == bit_paridade){
    std::cout << "ERRO: Bit paridade impar incorrespondente" << std::endl;
  }
}//fim do metodo CamadaEnlaceDadosReceptoraControleErroBitParidadeImpar

void CamadaEnlaceDadosReceptoraControleErroCRC (std::vector<int> quadro) {
//implementacao do algoritmo para VERIFICAR SE HOUVE ERRO
//usar polinomio CRC-32(IEEE 802)
}//fim do metodo CamadaEnlaceDadosReceptoraControleErroCRC

void CamadaEnlaceDadosReceptoraControleErroCodigoHamming (std::vector<int> quadro) {
//implementacao do algoritmo para VERIFICAR SE HOUVE ERRO
}//fim do metodo CamadaEnlaceDadosReceptoraControleErroCodigoHamming

std::vector<int> CamadaEnlaceDadosReceptoraControleErro (std::vector<int> quadro) {
  int tipoControleErro = 0; //alterar de acordo com o teste
  switch (tipoControleErro) {
    case 0 : //bit de paridade par
      // Verifica Paridade Par
      CamadaEnlaceDadosReceptoraControleErroBitParidadePar(quadro);

      // Retira Bit paridade do quadro final
      quadro.pop_back();
      break;

    case 1 : //bit de paridade impar
      // Verifica Paridade Impar
      CamadaEnlaceDadosReceptoraControleErroBitParidadeImpar(quadro);

      // Retira Bit paridade do quadro final
      quadro.pop_back();
      break;

    case 2 : //CRC
      //codigo
      break;

    case 3 : //codigo de hamming
      //codigo
      break;
  }//fim do switch/case

  return quadro;

}//fim do metodo CamadaEnlaceDadosReceptoraControleErro

void CamadaEnlaceDadosReceptoraControleFluxo (std::vector<int> quadro) {
//algum codigo aqui
}//fim do metodo CamadaEnlaceDadosReceptoraControleFluxo

void CamadaEnlaceDadosReceptora (std::vector<int> quadro) {
  CamadaEnlaceDadosReceptoraEnquadramento(quadro);
  quadro = CamadaEnlaceDadosReceptoraControleErro(quadro);
  CamadaEnlaceDadosReceptoraControleFluxo(quadro);
  //chama proxima camada
  CamadaDeAplicacaoReceptora(quadro);
}//fim do metodo CamadaEnlaceDadosReceptora

