#include "../include/data_link_layer.hpp"
#include "../include/utilities.hpp"

int tipoEnquadramento=0;
int tipoControleErro = 0;

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemCaracteres (std::vector<int> quadro) {

  std::cout << "-----Contagem de caracteres-----" << std::endl;

  // Tamanho do quadro
  int tamanho_quadro;

  // Quadro com o cabecalho de contagem
  std::vector<int> quadro_cabecalho(quadro.size() + 8, 0);

  // Tamanho do quadro em bytes inteiro
  tamanho_quadro = quadro.size()/8;

  // Quantidade de bytes do quadro original em hexa
  char cabecalho = 0x0;

  cabecalho = (char) tamanho_quadro;

  int i, bit;

  // Começa do segundo byte
  // E preenche o quadro
  for (i = 0, bit = 0; i < 8; i++, bit++) {
    // Obtem o cabecalho bit a bit
    // e insere no inicio do quadro
    char temp = cabecalho >> (7 - bit);
    quadro_cabecalho[i] = temp & 0x01;
  }

  // Preenche o quadro com a carga util
  for (i = 8; i < (int)quadro_cabecalho.size(); i++) {
    quadro_cabecalho[i] = quadro[i-8];
  }

  // Imprimir Quadro
  std::cout << std::endl << "Quadro com contagem de caracteres:" << std::endl;
  for(auto j = quadro_cabecalho.begin(); j != quadro_cabecalho.end(); ++j){
    std::cout << *j;
  }
  std::cout << std::endl;
  std::cout << "----------------------------------------\n\n";

  return quadro_cabecalho;
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
  std::cout << "----------------------------------------\n\n";

  return enviar;

}//fim do metodo CamadaEnlaceDadosTransmissoraInsercaoBits

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramento (std::vector<int> quadro) {
  std::cout<< "Insira o tipo de enquadramento:\n";
  std::cout<< "0\t\tContatem de caracteres\n";
  std::cout<< "1\t\tInsercao de bytes\n";
  std::cout<< "2\t\tInsercao de bits\n";
  std::cin >> tipoEnquadramento;
  std::cout<<std::endl;

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
  }//fim do switch/case

  return quadroEnquadrado;
}//fim do metodo CamadaEnlaceTransmissoraEnquadramento

std::vector<int> CamadaEnlaceDadosTransmissoraControleErroBitParidadePar (std::vector<int> quadro) {
  int paridade = 0;

  std::cout << "-----Bit paridade par-----" << std::endl;

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

  // Imprimir quadro
  std::cout << std::endl << "Quadro com a bit paridade par:" << std::endl;
  for(auto j = quadro.begin(); j != quadro.end(); ++j){
    std::cout << *j;
  }
  std::cout << std::endl;
  std::cout << "----------------------------------------\n\n";

  // Retorna o quadro com o Bit paridade
  return quadro;
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroBitParidadePar

std::vector<int> CamadaEnlaceDadosTransmissoraControleErroBitParidadeImpar (std::vector<int> quadro)
{
  int paridade = 0;

  std::cout << "-----Bit paridade impar-----" << std::endl;

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

  // Imprimir quadro
  std::cout << std::endl << "Quadro com a bit paridade impar:" << std::endl;
  for(auto j = quadro.begin(); j != quadro.end(); ++j){
    std::cout << *j;
  }
  std::cout << std::endl;
  std::cout << "----------------------------------------\n\n";
  // Retorna o quadro com o Bit paridade

  return quadro;
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroBitParidadeImpar

void CamadaEnlaceDadosTransmissoraControleErroCRC (std::vector<int> quadro) {
//implementacao do algoritmo
//usar polinomio CRC-32(IEEE 802)
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroCRC

void CamadaEnlaceDadosTransmissoraControleErroCodigoHamming (std::vector<int> quadro) {
//implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraControleDErroCodigohamming

std::vector<int> CamadaEnlaceDadosTransmissoraControleErro (std::vector<int> quadro) {
  std::cout<< "Insira o tipo de enquadramento:\n";
  std::cout<< "0\t\tBit paridade par\n";
  std::cout<< "1\t\tBit paridade impar\n";
  std::cout<< "2\t\tCRC\n";
  std::cout<< "3\t\tCodigo de Hamming\n";
  std::cin>> tipoControleErro;
  std::cout<<std::endl;

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
  std::cout << "-----Decodificação Inserção De Bits-----" << std::endl;
  
  // Valores de iteracao
  // i: percorre o vetor do novo quadro
  // bit: percorre o quadro com cabecalho
  int i, bit;

  // Cabecalho que indica
  // tamanho do quadro
  int cabecalho = 0x00;

  // Mascara para setar os bits 1
  // Do MSB para o LSB do cabecalho
  int mask = 0x80;

  // Percorre os bits e cria
  // o cabecalho por meio da leitura
  for (bit = 0; bit < 8; bit++) {

    // Seta o bit correspondente quando eh 1
    if(quadro[bit] == 1) {
      cabecalho = (cabecalho|mask);
    }

    // Move a mascara de set 
    // para o proximo bit
    mask >>= 1;
  }

  // Novo quadro sem cabecalho
  std::vector<int> quadro_sem_cabecalho(cabecalho*8, 0);

  // Preenche o novo quadro com o quadro 
  // antigo, a partir do 2 byte(por isso i+8)
  for(i = 0; i < cabecalho*8 ; i++){
    quadro_sem_cabecalho[i] = quadro[i+8];
  }


  // Imprimir quadro
  std::cout << std::endl << "Quadro decodificado:" << std::endl;
  for(auto j = quadro_sem_cabecalho.begin(); j != quadro_sem_cabecalho.end(); ++j){
    std::cout << *j;
  }
  std::cout << std::endl;
  std::cout << "----------------------------------------\n\n";

  return quadro_sem_cabecalho;

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

  // Imprimir quadro
  std::cout << std::endl << "Quadro decodificado:" << std::endl;
  for(auto j = resultado.begin(); j != resultado.end(); ++j){
    std::cout << *j;
  }
  std::cout << std::endl;
  std::cout << "----------------------------------------\n\n";

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
  std::cout << "----------------------------------------\n\n";

  return enviar;
}//fim do metodo CamadaEnlaceDadosReceptoraInsercaoBits

std::vector<int> CamadaEnlaceDadosReceptoraEnquadramento (std::vector<int> quadro) {
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
  }//fim do switch/case

  return quadroDesenquadrado;
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
  quadro = CamadaEnlaceDadosReceptoraControleErro(quadro);
  quadro = CamadaEnlaceDadosReceptoraEnquadramento(quadro);
  CamadaEnlaceDadosReceptoraControleFluxo(quadro);
  //chama proxima camada
  CamadaDeAplicacaoReceptora(quadro);
}//fim do metodo CamadaEnlaceDadosReceptora

