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


std::vector<int>  CamadaEnlaceDadosTransmissoraEnquadramentoContagemCaracteres(std::vector<int> quadro);

/**
 * @brief      Faz enquadramento com inserção de bytes
 *
 * @param      Vetor de bits para fazer enquadramento
 *
 * @return     Vetor de bits com enquadramento feito
 */
std::vector<int>  CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoBytes (std::vector<int> quadro);

/**
 * @brief      Faz enquadramento com inserção de bits
 *
 * @param      Vetor de bits para fazer enquadramento
 *
 * @return     Vetor de bits com enquadramento feito
 */
std::vector<int>  CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoBits (std::vector<int> quadro);
std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramento (std::vector<int> quadro);

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

std::vector<int> CamadaEnlaceDadosTransmissoraControleErro (std::vector<int> quadro);
void CamadaEnlaceDadosTransmissoraControleFluxo (std::vector<int> quadro);
void CamadaEnlaceDadosTransmissora (std::vector<int> quadro);

///////////////////////////////////////////////
//                  Receptor                 //
///////////////////////////////////////////////

// Controle de erro 
void CamadaEnlaceDadosReceptoraControleErroBitParidadePar (std::vector<int> quadro);
void CamadaEnlaceDadosReceptoraControleErroBitParidadeImpar (std::vector<int> quadro);
void CamadaEnlaceDadosReceptoraControleErroCRC (std::vector<int> quadro);

/**
 * @brief      Faz a detecção de erros por código de Hamming
 *
 * @param      quadro Quadro a ser verificado o erro
 *
 * @return     quadro Quadro resultante da verificação
 */
std::vector<int> CamadaEnlaceDadosReceptoraControleErroCodigoHamming (std::vector<int> quadro);
std::vector<int> CamadaEnlaceDadosReceptoraControleErro (std::vector<int> quadro);

// Enquadramento
std::vector<int> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(std::vector<int> quadro);
std::vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoBytes (std::vector<int> quadro);
/**
 * @brief      Decodifica o enquadramento com inserção de bits
 *
 * @param      Vetor de bits com o enquadramento
 *
 * @return     Vetor de bits com enquadramento desfeito
 */
std::vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoBits (std::vector<int> quadro);
std::vector<int> CamadaEnlaceDadosReceptoraEnquadramento (std::vector<int> quadro);

std::vector<int> CamadaDeEnlaceDadosReceptoraControleErro (std::vector<int> quadro);
std::vector<int> CamadaDeEnlaceDadosReceptoraControleFluxo (std::vector<int> quadro);
void CamadaEnlaceDadosReceptora (std::vector<int> quadro);

#endif
