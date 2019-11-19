#include "../include/data_link_layer.hpp"
#include "../include/utilities.hpp"

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemCaracteres (std::vector<int> quadro) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraContagemCaracteres

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoBytes (std::vector<int> quadro) {
  // Indica qual a posição dentro do quadro, usando caractere como medida
  int car_atual;
  char car_lido;
  std::vector<int> resultado;

  // Inserindo flag inicial
  resultado = InserirCaractere(resultado, BYTE_FLAG);

  // Percorrendo o quadro byte a byte
  for (car_atual = 0; car_atual < (int)(quadro.size()/8); car_atual++) {
	
	// Lendo o caractere atual da quadro
    car_lido = LerCaractere(quadro, car_atual);

	// Verificando se o caractere de dado é um especial
	if ((car_lido == BYTE_FLAG) || (car_lido == BYTE_ESC)) {
	  resultado = InserirCaractere(resultado, BYTE_ESC);
	}

	// Inserindo o caractere de dado no vetor resultante
	resultado = InserirCaractere(resultado, car_lido);
  }
  
  return InserirCaractere(resultado, BYTE_FLAG);
}//fim do metodo CamadaEnlaceDadosTransmissoraInsercaoBytes

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoBits (std::vector<int> quadro) {
  std::cout << "-----Inserção De Bits-----" << std::endl;
  // Declaração de Variáveis
  int cont_uns; // Contagem de quantos 1s apareceram após um zero
  std::vector<int> enviar;

  //Inserir Padrão inicial
  enviar = InserirCaractere(enviar, BIT_FLAG);

  // Inserir Quadro no Enviar
  cont_uns = 0;
  for(unsigned long int i = 0; i < quadro.size(); i++){
    int bit_atual = quadro[i];
    // COlocar bit no vetor 'enviar'
    enviar.push_back(bit_atual);
    // Verificar qual é o bit
    if(bit_atual == 0){
      // Reinicia a contagem de uns
      cont_uns = 0;
    }else{
      // Incrementa contagem de uns
      cont_uns++;
    }
    // Insere bit de proteção caso contagem esteja em 5
    if(cont_uns == 5){
      enviar.push_back(0);
      cont_uns = 0;
    }
  }

  // Inserir Padrão Final
  enviar = InserirCaractere(enviar, BIT_FLAG);

  // Impirmir Quadro
  std::cout << std::endl << "Quadro com a insercao de bits:" << std::endl;
  for(auto j = enviar.begin(); j != enviar.end(); ++j){
    std::cout << *j;
  }
  std::cout << std::endl;
  std::cout << "--------------------------" << std::endl;

  return enviar;

}//fim do metodo CamadaEnlaceDadosTransmissoraInsercaoBits

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoViolacaoCamadaFisica (std::vector<int> quadro) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraViolacaoDaCamadaFisica

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramento (std::vector<int> quadro) {
  int tipoEnquadramento= 0; //alterar de acordo com o teste
  std::vector<int> quadroEnquadrado;
  switch (tipoEnquadramento) {
    case 0 : //contagem de caracteres
      quadroEnquadrado =
      CamadaEnlaceDadosTransmissoraEnquadramentoContagemCaracteres(quadro);
      break;
    case 1 : //insercao de bytes
      quadroEnquadrado =
      CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoBytes(quadro);
      break;
    case 2 : //insercao de bits
      quadroEnquadrado =
      CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoBits(quadro);
      break;
    case 3 : //violacao da camada fisica
      quadroEnquadrado =
      CamadaEnlaceDadosTransmissoraEnquadramentoViolacaoCamadaFisica(quadro);
      break;
  }//fim do switch/case

  return quadroEnquadrado;
}//fim do metodo CamadaEnlaceTransmissoraEnquadramento

std::vector<int> CamadaEnlaceDadosTransmissoraControleErroBitParidadePar (std::vector<int> quadro) {
  int paridade = 0;

  // Conta quantos bits 1 existem
  for(auto bit: quadro){
    paridade += bit;
  }

  // Se é ímpar, a paridade é 1
  if(paridade%2 == 1){
    quadro.push_back(1);
  }

  // Se é par, a paridade é 0
  else {
    quadro.push_back(0);
  }

  // Retorna o quadro com o Bit paridade
  return quadro;
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroBitParidadePar

std::vector<int> CamadaEnlaceDadosTransmissoraControleErroBitParidadeImpar (std::vector<int> quadro)
{
  int paridade = 0;

  // Conta quantos bits 1 existem
  for(auto bit: quadro){
    paridade += bit;
  }

  // Se é ímpar, a paridade é 0
  if(paridade%2 == 1){
    quadro.push_back(0);
  }

  // Se é par, a paridade é 1
  else {
    quadro.push_back(1);
  }

  // Retorna o quadro com o Bit paridade
  return quadro;
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroBitParidadeImpar

void CamadaEnlaceDadosTransmissoraControleErroCRC (std::vector<int> quadro) {
//implementacao do algoritmo
//usar polinomio CRC-32(IEEE 802)
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroCRC

std::vector<int> CamadaEnlaceDadosTransmissoraControleErroCodigoHamming (std::vector<int> quadro) {
  std::cout << "--------- Transmissão Controle de erros por Hamming --------" << std::endl;
  int bits_redundantes = 0;
  int tam_quadro = quadro.size();

  // Calculando a quantidade de bits de paridade necessários
  while(bits_redundantes + tam_quadro + 1 > pow(2, bits_redundantes)) {
  	bits_redundantes++;
  }
  std::cout << "Número de bits redundantes a adicionar: " << bits_redundantes << std::endl;

  // Criando o vetor para resultado com o tamanho necessário
  int tam_res = tam_quadro + bits_redundantes;
  std::vector<int> resultado(tam_res, 0);

  int potencia, pos_quadro;
  for (int i = 1, pos_quadro = 1, potencia = 0; i <= tam_res; i++) {
    if (i == pow(2, potencia)) {
	  resultado[i - 1] = 0;
	  potencia++;
	}
	else {
	  resultado[i - 1] = quadro[pos_quadro - 1];
	  pos_quadro++;
	}
  }

  // Janela é um dos conjuntos de bits consecutivos dentro do quadro que
  // que fazem parte da formação de um bit de paridade
  int bits_jan_percorridos; // Indica quantos bits da janela atual já foram percorridos
  int tam_janela; // Indica o tamanho máximo de uma janela, se for o bit-paridade 2, tamanho da janela é 2
  int qtd_uns; // Indica a quantidade de 1's que fazem parte da formação daquele bit de paridade
  int inic_janela; // Indica o início da janela atual para um certo bit de paridade
  int cont_janela; // Usado para percorrer uma janela de um bit de paridade

  // Loop para percorrer cada bit de paridade detro do quadro
  for (int bitp = 1, potencia = 0; bitp <= tam_res; bitp = pow(2, potencia)) {
    potencia++;
	qtd_uns = 0;
	inic_janela = bitp;
	cont_janela = bitp;
	bits_jan_percorridos = 1;
	tam_janela = bitp;

	// Loop para percorrer cada janela do bit de paridade (bitp) atual
	while (inic_janela <= tam_res) {
	  // Loop para percorrer uma única janela do bitp
      for (cont_janela = inic_janela; tam_janela >= bits_jan_percorridos && cont_janela <= tam_res; cont_janela++, bits_jan_percorridos++) {
		if (resultado[cont_janela - 1] == 1) {
		  qtd_uns++;
		}
	  }
	  inic_janela = cont_janela + bitp;
	  bits_jan_percorridos = 1;
	}

	if (qtd_uns % 2 == 0) {
	  resultado[bitp - 1] = 0;
	}
	else {
	  resultado[bitp - 1] = 1;
	}
  }

  std::cout << "Quadro resultante do controle com código de Hamming:" << std::endl;
  for (int bit : resultado) {
	std::cout << bit;
  }
  std::cout << std::endl;

  return resultado;
}//fim do metodo CamadaEnlaceDadosTransmissoraControleDErroCodigohamming

std::vector<int> CamadaEnlaceDadosTransmissoraControleErro (std::vector<int> quadro) {
  int tipoControleErro = 0; //alterar de acordo com o teste
  switch (tipoControleErro) {
    case 0 : //bit de paridade par
      // Retorna quadro com bit paridade
      return CamadaEnlaceDadosTransmissoraControleErroBitParidadePar(quadro);
      break;
    case 1 : //bit de paridade impar
      // Retorna quadro com bit paridade
      return CamadaEnlaceDadosTransmissoraControleErroBitParidadeImpar(quadro);
      break;
    case 2 : //CRC
      //codigo
      break;
    case 3 : //codigo de Hamming
      //codigo
      break;
  }//fim do switch/case
}//fim do metodo CamadaEnlaceDadosTransmissoraControleErro

void CamadaEnlaceDadosTransmissoraControleFluxo (std::vector<int> quadro) {
//algum codigo aqui
}//fim do metodo CamadaEnlaceDadosTransmissoraControleFluxo

void CamadaEnlaceDadosTransmissora (std::vector<int> quadro) {
  quadro = CamadaEnlaceDadosTransmissoraEnquadramento(quadro);
  quadro = CamadaEnlaceDadosTransmissoraControleErro(quadro);
  CamadaEnlaceDadosTransmissoraControleFluxo(quadro);
  //chama proxima camada
  CamadaFisicaTransmissora(quadro);
}//fim do metodo CamadaEnlaceDadosTransmissora

std::vector<int> CamadaEnlaceDadosReceptoraEnquadramentoContagemCaracteres (std::vector<int> quadro) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosReceptoraContagemCaracteres

std::vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoBytes (std::vector<int> quadro) {
  int car_atual;
  char car_lido;

  std::vector<int> resultado;

  for (car_atual = 0; car_atual < (int)(quadro.size()/8); car_atual++) {
    car_lido = LerCaractere(quadro, car_atual);

	// Verifica se o byte de dado é especial
	if (car_lido == BYTE_ESC) {
	  car_lido = LerCaractere(quadro, ++car_atual);
	  resultado = InserirCaractere(resultado, car_lido);
	}
	else if (car_lido != BYTE_FLAG) {
	  resultado = InserirCaractere(resultado, car_lido);
	}
  }

  return resultado;
}//fim do metodo CamadaEnlaceDadosReceptoraInsercaoBytes

std::vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoBits (std::vector<int> quadro) {
  std::cout << "-----Decodificação Inserção De Bits-----" << std::endl;
  // Declaração de Variáveis
  int cont_uns; // Contagem de uns seguidos
  int bit_pos_ref; // Posição do ultimo bit '0'
  std::vector<int> buffer; // Buffer para ser anexo ao vetor de envio
  std::vector<int> enviar;

  // Espera-se que o primeiro byte seja 0x7E
  if(LerCaractere(quadro, 0) != BIT_FLAG){
    std::cout << "ERRO! Padrão Inicial Incompativel" << std::endl;
  }
  
  // Deocidificar Padrão
  bit_pos_ref = 8;
  cont_uns = 0;
  unsigned long int i;
  for(i = 8; i < quadro.size(); i++){
    int bit_atual = quadro[i];

    // Vericar caso em que o bit é 0
    if(bit_atual == 0){
      // Caso a contagem atual for 6 (BIT_FLAG)
      if(cont_uns == 6){
        // Chegou no fim do quadro
        buffer.clear();
        break;
      }
      // Caso a contagem de uns atual for 5
      if(cont_uns == 5){
        enviar.insert(enviar.end(), buffer.begin(), buffer.end()); //Colocar buffer no vetor de envio sem o bit atual
        buffer.clear(); //Limpar buffer
      }
      else{
        enviar.insert(enviar.end(), buffer.begin(), buffer.end());;
        buffer.clear(); //Limpar Buffer
        buffer.push_back(bit_atual); // Reinicia o Buffer com o novo 0
      }
      cont_uns = 0;
    }
    // Vericar caso em que o bit é 1
    else{
      buffer.push_back(bit_atual);
      cont_uns++;
    }
  }

  // Verificar se o fim do quadro conincidiu com o fim da sequencia de bits
  if(i < (quadro.size() - 1)){
    std::cout << "ERRO! Fim Do quadro nao coincidiu com fim do padrao de bits" << std::endl;
  }

  // Imprimir quadro
  std::cout << std::endl << "Quadro decodificado:" << std::endl;
  for(auto j = enviar.begin(); j != enviar.end(); ++j){
    std::cout << *j;
  }
  std::cout << std::endl;
  std::cout << "----------------------------------------" << std::endl;

  return enviar;
}//fim do metodo CamadaEnlaceDadosReceptoraInsercaoBits

std::vector<int> CamadaEnlaceDadosReceptoraEnquadramentoViolacaoCamadaFisica (std::vector<int> quadro) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosReceptoraViolacaoDaCamadaFisica

void CamadaEnlaceDadosReceptoraEnquadramento (std::vector<int> quadro) {
  int tipoEnquadramento= 0; //alterar de acordo com o teste
  std::vector<int> quadroDesenquadrado;
  switch (tipoEnquadramento) {
  case 0 : //contagem de caracteres
    quadroDesenquadrado =
    CamadaEnlaceDadosReceptoraEnquadramentoContagemCaracteres(quadro);
    break;
  case 1 : //insercao de bytes
    quadroDesenquadrado =
    CamadaEnlaceDadosReceptoraEnquadramentoInsercaoBytes(quadro);
    break;
  case 2 : //insercao de bits
    quadroDesenquadrado =
    CamadaEnlaceDadosReceptoraEnquadramentoInsercaoBits(quadro);
    break;
  case 3 : //violacao da camada fisica
    quadroDesenquadrado =
    CamadaEnlaceDadosReceptoraEnquadramentoViolacaoCamadaFisica(quadro);
    break;
  }//fim do switch/case
}//fim do metodo CamadaEnlaceDadosReceptoraEnquadramento


void CamadaEnlaceDadosReceptoraControleErroBitParidadePar (std::vector<int> quadro ) {
  // Conta quantos bits 1 existe
  int paridade = 0;

  // Retira o último bit paridade 
  // e guarda para verificação
  int bit_paridade = quadro.back();
  quadro.pop_back();

  // Conta quantos bits 1 existem
  for(auto bit: quadro){
    paridade += bit;
  }

  // Condição de Erro
  // A paridade deve ser igual do bit paridade,
  // para provocar a paridade par
  if(paridade%2 != bit_paridade){
    std::cout << "ERRO: Bit paridade par incorrespondente" << std::endl;
  }
}//fim do metodo CamadaEnlaceDadosReceptoraControleErroBitParidadePar

void CamadaEnlaceDadosReceptoraControleErroBitParidadeImpar (std::vector<int> quadro ) {
  // Conta quantos bits 1 existe
  int paridade = 0;

  // Retira o último bit paridade 
  // e guarda para verificação
  int bit_paridade = quadro.back();
  quadro.pop_back();

  // Conta quantos bits 1 existem
  for(auto bit: quadro){
    paridade += bit;
  }

  // Condição de Erro
  // A paridade correta deve ser diferente do bit paridade,
  // para provocar a paridade impar
  if(paridade%2 == bit_paridade){
    std::cout << "ERRO: Bit paridade impar incorrespondente" << std::endl;
  }
}//fim do metodo CamadaEnlaceDadosReceptoraControleErroBitParidadeImpar

void CamadaEnlaceDadosReceptoraControleErroCRC (std::vector<int> quadro) {
//implementacao do algoritmo para VERIFICAR SE HOUVE ERRO
//usar polinomio CRC-32(IEEE 802)
}//fim do metodo CamadaEnlaceDadosReceptoraControleErroCRC

void CamadaEnlaceDadosReceptoraControleErroCodigoHamming (std::vector<int> quadro) {
//implementacao do algoritmo para VERIFICAR SE HOUVE ERRO
}//fim do metodo CamadaEnlaceDadosReceptoraControleErroCodigoHamming

std::vector<int> CamadaEnlaceDadosReceptoraControleErro (std::vector<int> quadro) {
  int tipoControleErro = 0; //alterar de acordo com o teste
  switch (tipoControleErro) {
    case 0 : //bit de paridade par
      // Verifica Paridade Par
      CamadaEnlaceDadosReceptoraControleErroBitParidadePar(quadro);

      // Retira Bit paridade do quadro final
      quadro.pop_back();
      break;

    case 1 : //bit de paridade impar
      // Verifica Paridade Impar
      CamadaEnlaceDadosReceptoraControleErroBitParidadeImpar(quadro);

      // Retira Bit paridade do quadro final
      quadro.pop_back();
      break;

    case 2 : //CRC
      //codigo
      break;

    case 3 : //codigo de hamming
      //codigo
      break;
  }//fim do switch/case

  return quadro;

}//fim do metodo CamadaEnlaceDadosReceptoraControleErro

void CamadaEnlaceDadosReceptoraControleFluxo (std::vector<int> quadro) {
//algum codigo aqui
}//fim do metodo CamadaEnlaceDadosReceptoraControleFluxo

void CamadaEnlaceDadosReceptora (std::vector<int> quadro) {
  CamadaEnlaceDadosReceptoraEnquadramento(quadro);
  quadro = CamadaEnlaceDadosReceptoraControleErro(quadro);
  CamadaEnlaceDadosReceptoraControleFluxo(quadro);
  //chama proxima camada
  CamadaDeAplicacaoReceptora(quadro);
}//fim do metodo CamadaEnlaceDadosReceptora

