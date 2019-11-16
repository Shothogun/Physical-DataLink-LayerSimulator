#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <string>
#include <vector>

/**
 * @brief      Cria um vetor de bits
 *
 * @details    Cria a partir de uma mensagem string de acordo
 *             com a tabela AScii
 *
 * @param      mensagem Mensagem a ser transformada
 *
 * @return     quadro Quadro resultante da transformação
 */
std::vector<int> CriarVetorBits(std::string mensagem);

/**
 * @brief      Cria uma string
 *
 * @details    Cria a partir de um vetor de bits
 *
 * @param      quadro Vetor de bits que vai virar string
 *
 * @return     resultado String resultante da conversão
 */
std::string CriarString(std::vector<int> quadro);

#endif /* UTILITIES_H */
