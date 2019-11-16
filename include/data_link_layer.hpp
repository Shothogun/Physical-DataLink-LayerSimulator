#ifndef DATA_LINK_LAYER_H
#define DATA_LINK_LAYER_H

#include "../include/physical_layer.hpp"

///////////////////////////////////////////////
//                 Transmissor               //
///////////////////////////////////////////////

// Enquadramento
std::vector<int>  CamadaEnlaceDadosTransmissoraEnquadramentoContagemCaracteres(std::vector<int>);
std::vector<int>  CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoBytes (std::vector<int>);
std::vector<int>  CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoBits (std::vector<int>);
std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoViolacaoCamadaFisica (std::vector<int>);
std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramento (std::vector<int>);

// Controle de erro 
std::vector<int> CamadaEnlaceDadosTransmissoraControleErroBitParidadePar (std::vector<int>);
std::vector<int> CamadaEnlaceDadosTransmissoraControleErroBitParidadeImpar (std::vector<int>);
void CamadaEnlaceDadosTransmissoraControleErroCRC (std::vector<int>);
void CamadaEnlaceDadosTransmissoraControleErroCodigoDeHamming (std::vector<int>);

std::vector<int> CamadaEnlaceDadosTransmissoraControleErro (std::vector<int>);
void CamadaEnlaceDadosTransmissoraControleFluxo (std::vector<int>);
void CamadaEnlaceDadosTransmissora (std::vector<int>);

///////////////////////////////////////////////
//                  Receptor                 //
///////////////////////////////////////////////

// Controle de erro 
void CamadaEnlaceDadosReceptoraControleErroBitParidadePar (std::vector<int>);
void CamadaEnlaceDadosReceptoraControleErroBitParidadeImpar (std::vector<int>);
void CamadaEnlaceDadosReceptoraControleErroCRC (std::vector<int>);
void CamadaEnlaceDadosReceptoraControleErroCodigoHamming (std::vector<int>);
std::vector<int> CamadaEnlaceDadosReceptoraControleErro (std::vector<int> quadro);

// Enquadramento
std::vector<int> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(std::vector<int>);
std::vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoBytes (std::vector<int>);
std::vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoBits (std::vector<int>);
std::vector<int> CamadaEnlaceDadosReceptoraEnquadramentoViolacaoCamadaFisica (std::vector<int>);
void CamadaEnlaceDadosReceptoraEnquadramento (std::vector<int>);

std::vector<int> CamadaDeEnlaceDadosReceptoraControleErro (std::vector<int>);
std::vector<int> CamadaDeEnlaceDadosReceptoraControleFluxo (std::vector<int>);
void CamadaEnlaceDadosReceptora (std::vector<int>);

#endif