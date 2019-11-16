#include "../include/data_link_layer.hpp"

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemCaracteres (std::vector<int> quadro) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraContagemDeCaracteres

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoBytes (std::vector<int> quadro) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraInsercaoDeBytes

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoBits (std::vector<int> quadro) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraInsercaoDeBits

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoViolacaoCamadaFisica (std::vector<int> quadro) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraViolacaoDaCamadaFisica

void CamadaEnlaceDadosTransmissoraEnquadramento (std::vector<int> quadro) {
  int tipoDeEnquadramento= 0; //alterar de acordo com o teste
  std::vector<int> quadroEnquadrado;
  switch (tipoDeEnquadramento) {
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
    case 3 : //violacao da camada fisica
    quadroEnquadrado =
    CamadaEnlaceDadosTransmissoraEnquadramentoViolacaoCamadaFisica(quadro);
    break;
  }//fim do switch/case
}//fim do metodo CamadaEnlaceTransmissoraEnquadramento

void CamadaEnlaceDadosTransmissoraControleErroBitParidadePar (std::vector<int> quadro) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroBitParidadePar

void CamadaEnlaceDadosTransmissoraControleErroBitParidadeImpar (std::vector<int> quadro)
{
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroBitParidadeImpar

void CamadaEnlaceDadosTransmissoraControleErroCRC (std::vector<int> quadro) {
//implementacao do algoritmo
//usar polinomio CRC-32(IEEE 802)
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroCRC

void CamadaEnlaceDadosTransmissoraControleErroCodigoHamming (std::vector<int> quadro) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraControleDErroCodigohamming

void CamadaEnlaceDadosTransmissoraControleErro (std::vector<int> quadro) {
  int tipoControleErro = 0; //alterar de acordo com o teste
  switch (tipoControleErro) {
    case 0 : //bit de paridade par
    //codigo
    break;
    case 1 : //bit de paridade impar
    //codigo
    break;
    case 2 : //CRC
    //codigo
    case 3 : //codigo de Hamming
    //codigo
    break;
  }//fim do switch/case
}//fim do metodo CamadaEnlaceDadosTransmissoraControleErro

void CamadaEnlaceDadosTransmissoraControleFluxo (std::vector<int> quadro) {
//algum codigo aqui
}//fim do metodo CamadaEnlaceDadosTransmissoraControleFluxo

void CamadaEnlaceDadosTransmissora (std::vector<int> quadro) {
  CamadaEnlaceDadosTransmissoraEnquadramento(quadro);
  CamadaEnlaceDadosTransmissoraControleErro(quadro);
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
  case 3 : //violacao da camada fisica
  quadroDesenquadrado =
  CamadaEnlaceDadosReceptoraEnquadramentoViolacaoCamadaFisica(quadro);
  break;
  }//fim do switch/case
}//fim do metodo CamadaEnlaceDadosReceptoraEnquadramento

void CamadaEnlaceDadosReceptoraControleErro (std::vector<int> quadro) {
//algum codigo aqui
}//fim do metodo CamadaEnlaceDadosReceptoraControleDeErro

void CamadaEnlaceDadosReceptoraControleFluxo (std::vector<int> quadro) {
//algum codigo aqui
}//fim do metodo CamadaEnlaceDadosReceptoraControleDeFluxo

void CamadaEnlaceDadosReceptora (std::vector<int> quadro) {
  CamadaEnlaceDadosReceptoraEnquadramento(quadro);
  CamadaEnlaceDadosReceptoraControleErro(quadro);
  CamadaEnlaceDadosReceptoraControleFluxo(quadro);
  //chama proxima camada
  CamadaDeAplicacaoReceptora(quadro);
}//fim do metodo CamadaEnlaceDadosReceptora

