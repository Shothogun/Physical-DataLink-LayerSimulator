#ifndef PHYSICAL_LAYER_H
#define PHYSICAL_LAYER_H

#include <iostream>
#include <list> 

enum CodType{COD_BIN=0, COD_MANCH, COD_MANCH_DIF};

void AplicacaoTransmissora (void);
void CamadaDeAplicacaoTransmissora (std::string mensagem);
void CamadaFisicaTransmissora (int quadro[]);
int* CamadaFisicaTransmissoraCodificacaoBinaria (int quadro []);
int* CamadaFisicaTransmissoraCodificacaoManchester (int quadro []);
int* CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(int quadro []);
void MeioDeComunicacao (int fluxoBrutoDeBits[]);
void CamadaFisicaReceptora (int quadro[]);
int* CamadaFisicaReceptoraCodificacaoBinaria (int quadro []);
int* CamadaFisicaReceptoraCodificacaoManchester (int quadro []);
int* CamadaFisicaReceptoraCodificacaoManchesterDiferencial(int quadro[]);
void CamadaDeAplicacaoReceptora (int quadro []);
void AplicacaoReceptora (std::string mensagem);

#endif