#ifndef DATA_LINK_LAYER_H
#define DATA_LINK_LAYER_H

#include "../include/physical_layer.hpp"

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
std::vector<int> CamadaEnlaceDadosTransmissoraControleErroBitParidadePar (std::vector<int> quadro);
std::vector<int> CamadaEnlaceDadosTransmissoraControleErroBitParidadeImpar (std::vector<int> quadro);
void CamadaEnlaceDadosTransmissoraControleErroCRC (std::vector<int> quadro);
void CamadaEnlaceDadosTransmissoraControleErroCodigoDeHamming (std::vector<int> quadro);

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
void CamadaEnlaceDadosReceptoraControleErroCodigoHamming (std::vector<int> quadro);
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
