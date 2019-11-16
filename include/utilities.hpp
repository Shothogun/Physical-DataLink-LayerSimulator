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

/**
 * @brief      Ler o próximo caractere do quadro
 *
 * @details    detailed description
 *
 * @param      quadro Quadro de se quer o caractere
 *
 * @param      letra_atual Qual posição de caractere se está atualmente, por exemplo
 *             na string "asdf", letra_atual = 1 significa que se está mexendo na
 *             letra 's'
 *
 * @return     Letra lida do quadro
 */
char LerCaractere(std::vector<int> quadro, int letra_atual);

#endif /* UTILITIES_H */
