#ifndef DATA_LINK_LAYER_H
#define DATA_LINK_LAYER_H

#include "../include/physical_layer.hpp"
#include <math.h>

#define BYTE_FLAG '$'
#define BYTE_ESC '#'
#define BIT_FLAG 0x7E

///////////////////////////////////////////////
//                 Transmissor               //
///////////////////////////////////////////////

// Enquadramento
std::vector<int>  CamadaEnlaceDadosTransmissoraEnquadramentoContagemCaracteres(std::vector<int>);

/**
 * @brief      Faz enquadramento com inserção de bytes
 *
 * @param      Vetor de bits para fazer enquadramento
 *
 * @return     Vetor de bits com enquadramento feito
 */
std::vector<int>  CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoBytes (std::vector<int>);

/**
 * @brief      Faz enquadramento com inserção de bits
 *
 * @param      Vetor de bits para fazer enquadramento
 *
 * @return     Vetor de bits com enquadramento feito
 */
std::vector<int>  CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoBits (std::vector<int>);
std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoViolacaoCamadaFisica (std::vector<int>);
std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramento (std::vector<int>);

// Controle de erro 
std::vector<int> CamadaEnlaceDadosTransmissoraControleErroBitParidadePar (std::vector<int>);
std::vector<int> CamadaEnlaceDadosTransmissoraControleErroBitParidadeImpar (std::vector<int>);
void CamadaEnlaceDadosTransmissoraControleErroCRC (std::vector<int>);

/**
 * @brief      Faz o cotrole de erros pelo Código de Hamming para transmissão
 *
 * @param      quadro Quadro em que se deseja aplicar o código de Hamming
 *
 * @return     
 */
std::vector<int> CamadaEnlaceDadosTransmissoraControleErroCodigoHamming  (std::vector<int>);

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

/**
 * @brief      Decodifica o enquadramento com inserção de bits
 *
 * @param      Vetor de bits com o enquadramento
 *
 * @return     Vetor de bits com enquadramento desfeito
 */
std::vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoBits (std::vector<int>);
std::vector<int> CamadaEnlaceDadosReceptoraEnquadramentoViolacaoCamadaFisica (std::vector<int>);
void CamadaEnlaceDadosReceptoraEnquadramento (std::vector<int>);

std::vector<int> CamadaDeEnlaceDadosReceptoraControleErro (std::vector<int>);
std::vector<int> CamadaDeEnlaceDadosReceptoraControleFluxo (std::vector<int>);
void CamadaEnlaceDadosReceptora (std::vector<int>);

#endif
