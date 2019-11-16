#ifndef DATA_LINK_LAYER_H
#define DATA_LINK_LAYER_H


void CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(int quadro []);
void CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes (int quadro []);
void CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBits (int quadro []);
void CamadaEnlaceDadosTransmissoraEnquadramentoViolacaoDaCamadaFisica (int quadro []);
void CamadaEnlaceDadosTransmissoraEnquadramento (int quadro []);
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar (int quadro []);
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar (int quadro []);
void CamadaEnlaceDadosTransmissoraControleDeErroCRC (int quadro []);
void CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming (int quadro []);
void CamadaEnlaceDadosTransmissoraControleDeErro (int quadro []);
void CamadaEnlaceDadosTransmissoraControleFluxo (int quadro []);
void CamadaEnlaceDadosTransmissora (int quadro []);
void CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(int quadro []);
void CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes (int quadro []);
void CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBits (int quadro []);
void CamadaEnlaceDadosReceptoraEnquadramentoViolacaoCamadaFisica (int quadro []);
void CamadaEnlaceDadosReceptoraEnquadramento (int quadro []);
void CamadaDeEnlaceDadosReceptoraControleDeErro (int quadro []);
void CamadaDeEnlaceDadosReceptoraControleDeFluxo (int quadro []);
void CamadaEnlaceDadosReceptora (int quadro []);


#endif
