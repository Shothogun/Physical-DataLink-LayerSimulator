#ifndef PHYSICAL_LAYER_H
#define PHYSICAL_LAYER_H

#include <iostream>
#include <list> 
#include <vector>
#include <string>         
#include <bitset>

enum CodType{COD_BIN=0, COD_MANCH, COD_MANCH_DIF};

void AplicacaoTransmissora (void);
void CamadaDeAplicacaoTransmissora (std::string mensagem);
void CamadaFisicaTransmissora (std::vector<int>);
std::vector<int> CamadaFisicaTransmissoraCodificacaoBinaria (std::vector<int> quadro);
std::vector<int> CamadaFisicaTransmissoraCodificacaoManchester (std::vector<int> quadro);
std::vector<int> CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(std::vector<int> quadro);
void MeioDeComunicacao (std::vector<int> fluxoBrutoDeBits);
void CamadaFisicaReceptora (std::vector<int>);
std::vector<int> CamadaFisicaReceptoraCodificacaoBinaria (std::vector<int> quadro);
std::vector<int> CamadaFisicaReceptoraCodificacaoManchester (std::vector<int> quadro);
std::vector<int> CamadaFisicaReceptoraCodificacaoManchesterDiferencial(std::vector<int> quadro);
void CamadaDeAplicacaoReceptora (std::vector<int> quadro);
void AplicacaoReceptora (std::string mensagem);

#endif
