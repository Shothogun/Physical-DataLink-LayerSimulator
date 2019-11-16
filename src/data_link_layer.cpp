#include "../include/data_link_layer.hpp"
#include "../include/physical_layer.hpp"

void CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres
(int quadro []) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraContagemDeCaracteres

void CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes (int
quadro []) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraInsercaoDeBytes

void CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBits (int
quadro []) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraInsercaoDeBits

void CamadaEnlaceDadosTransmissoraEnquadramentoViolacaoDaCamadaFisica
(int quadro []) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraViolacaoDaCamadaFisica

void CamadaEnlaceDadosTransmissoraEnquadramento (int quadro []) {
  int tipoDeEnquadramento= 0; //alterar de acordo com o teste
  int quadroEnquadrado [];
  switch (tipoDeEnquadramento) {
    case 0 : //contagem de caracteres
    quadroEnquadrado =
    CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(quadro);
    break;
    case 1 : //insercao de bytes
    quadroEnquadrado =
    CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(quadro);
    break;
    case 2 : //insercao de bits
    quadroEnquadrado =
    CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBits(quadro);
    case 3 : //violacao da camada fisica
    quadroEnquadrado =
    CamadaEnlaceDadosTransmissoraEnquadramentoViolacaoDaCamadaFisica(quadro);
    break;
  }//fim do switch/case
}//fim do metodo CamadaEnlaceTransmissoraEnquadramento

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar (int quadro []) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroBitParidadePar

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar (int quadro [])
{
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroBitParidadeImpar

void CamadaEnlaceDadosTransmissoraControleDeErroCRC (int quadro []) {
//implementacao do algoritmo
//usar polinomio CRC-32(IEEE 802)
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroCRC

void CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming (int quadro []) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraControleDeErroCodigoDehamming

void CamadaEnlaceDadosTransmissoraControleDeErro (int quadro []) {
  int tipoDeControleDeErro = 0; //alterar de acordo com o teste
  switch (tipoDeControleDeErro) {
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
}//fim do metodo CamadaEnlaceDadosTransmissoraControleDeErro

void CamadaEnlaceDadosTransmissoraControleFluxo (int quadro []) {
//algum codigo aqui
}//fim do metodo CamadaEnlaceDadosTransmissoraControleDeFluxo

void CamadaEnlaceDadosTransmissora (int quadro []) {
  CamadaEnlaceDadosTransmissoraEnquadramento(quadro);
  CamadaEnlaceDadosTransmissoraControleErro(quadro);
  CamadaEnlaceDadosTransmissoraControleFluxo(quadro);
  //chama proxima camada
  CamadaFisicaTransmissora(quadro);
}//fim do metodo CamadaEnlaceDadosTransmissora

void CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres
(int quadro []) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosReceptoraContagemDeCaracteres

void CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes (int
quadro []) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosReceptoraInsercaoDeBytes

void CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBits (int
quadro []) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosReceptoraInsercaoDeBits

void CamadaEnlaceDadosReceptoraEnquadramentoViolacaoCamadaFisica
(int quadro []) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosReceptoraViolacaoDaCamadaFisica

void CamadaEnlaceDadosReceptoraEnquadramento (int quadro []) {
  int tipoDeEnquadramento= 0; //alterar de acordo com o teste
  int quadroDesenquadrado [];
  switch (tipoDeEnquadramento) {
  case 0 : //contagem de caracteres
  quadroDesenquadrado =
  CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(quadro);
  break;
  case 1 : //insercao de bytes
  quadroDesenquadrado =
  CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(quadro);
  break;
  case 2 : //insercao de bits
  quadroDesenquadrado =
  CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBits(quadro);
  case 3 : //violacao da camada fisica
  quadroDesenquadrado =
  CamadaEnlaceDadosReceptoraEnquadramentoViolacaoCamadaFisica(quadro);
  break;
  }//fim do switch/case
}//fim do metodo CamadaEnlaceDadosReceptoraEnquadramento

void CamadaDeEnlaceDadosReceptoraControleDeErro (int quadro []) {
//algum codigo aqui
}//fim do metodo CamadaEnlaceDadosReceptoraControleDeErro

void CamadaDeEnlaceDadosReceptoraControleDeFluxo (int quadro []) {
//algum codigo aqui
}//fim do metodo CamadaEnlaceDadosReceptoraControleDeFluxo

void CamadaEnlaceDadosReceptora (int quadro []) {
  CamadaDeEnlaceDadosReceptoraEnquadramento(quadro);
  CamadaDeEnlaceDadosReceptoraControleDeErro(quadro);
  CamadaDeEnlaceDadosReceptoraControleDeFluxo(quadro);
  //chama proxima camada
  CamadaDeAplicacaoReceptora(quadro);
}//fim do metodo CamadaEnlaceDadosReceptora

