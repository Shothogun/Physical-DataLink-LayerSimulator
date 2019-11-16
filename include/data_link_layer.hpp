#ifndef DATA_LINK_LAYER_H
#define DATA_LINK_LAYER_H

#include "../include/physical_layer.hpp"

std::vector<int>  CamadaEnlaceDadosTransmissoraEnquadramentoContagemCaracteres(std::vector<int>);
std::vector<int>  CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoBytes (std::vector<int>);
std::vector<int>  CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoBits (std::vector<int>);
std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoViolacaoCamadaFisica (std::vector<int>);
void CamadaEnlaceDadosTransmissoraEnquadramento (std::vector<int>);
void CamadaEnlaceDadosTransmissoraControleErroBitParidadePar (std::vector<int>);
void CamadaEnlaceDadosTransmissoraControleErroBitParidadeImpar (std::vector<int>);
void CamadaEnlaceDadosTransmissoraControleErroCRC (std::vector<int>);
void CamadaEnlaceDadosTransmissoraControleErroCodigoDeHamming (std::vector<int>);
void CamadaEnlaceDadosTransmissoraControleErro (std::vector<int>);
void CamadaEnlaceDadosTransmissoraControleFluxo (std::vector<int>);
void CamadaEnlaceDadosTransmissora (std::vector<int>);
std::vector<int> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(std::vector<int>);
std::vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoBytes (std::vector<int>);
std::vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoBits (std::vector<int>);
std::vector<int> CamadaEnlaceDadosReceptoraEnquadramentoViolacaoCamadaFisica (std::vector<int>);
void CamadaEnlaceDadosReceptoraEnquadramento (std::vector<int>);
std::vector<int> CamadaDeEnlaceDadosReceptoraControleErro (std::vector<int>);
std::vector<int> CamadaDeEnlaceDadosReceptoraControleFluxo (std::vector<int>);
void CamadaEnlaceDadosReceptora (std::vector<int>);


#endif
