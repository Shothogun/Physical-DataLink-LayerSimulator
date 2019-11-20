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
  std::cout << "-------- Enquadramento por inserção de Bytes ----------" << std::endl;
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

  resultado = InserirCaractere(resultado, BYTE_FLAG);

  std::cout << "Quadro com enquadramento por inserção de bytes:" << std::endl;

  for (int bit : resultado) {
	std::cout << bit;
  }
  std::cout << std::endl;
  
  return resultado;
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

std::vector<int> CamadaEnlaceDadosTransmissoraControleErroCRC (std::vector<int> quadro) {
  std::cout << "-----Controle De Erro CRC32-----" << std::endl;

  // Criar vetor CRC_32
  std::vector<int> crc32;
  crc32.push_back(1); // Highest bit added
  int crc32_value = CRC_32;
  for(int i = 0; i < 32; i++){
    unsigned int temp = crc32_value >> (31-i);
    temp &= 0x01;
    crc32.push_back(temp);
  }
  // Imprimir CRC32
  std::cout << std::endl << "Polinomio CRC32:" << std::endl;
  for(auto j = crc32.begin(); j != crc32.end(); ++j){
    std::cout << *j;
  }
  std::cout << std::endl;

  std::vector<int> dividend = quadro;
  std::vector<int> reminder;

  // Adicionando 32 bits ao dividendo
  dividend.insert(dividend.end(), 32, 0);

  // Fazendo a divisão
  for(int i = 0; ((int)dividend.size() - i) > 32; i++){
    if(dividend[i] == 0) continue;
    for(int j = 0; j < 33; j++){
      if(dividend[i+j]){
        if(crc32[j]) dividend[i+j] = 0;
        else dividend[i+j] = 1; 
      }
      else{
        if(crc32[j]) dividend[i+j] = 1;
        else dividend[i+j] = 0; 
      }
    }
  }

  // Pegando o CRC
  reminder.insert(reminder.begin(), dividend.end()-32, dividend.end());

  // Imprimindo CRC
  std::cout << std::endl << "Resto/CRC:" << std::endl;
  for(auto j = reminder.begin(); j != reminder.end(); ++j){
    std::cout << *j;
  }
  std::cout << std::endl;

  // Pegando e Imprimindo quadro a enviar
  std::vector<int> result = quadro;
  result.insert(result.end(), reminder.begin(), reminder.end());
  std::cout << std::endl << "Quadro a Ser Enviado:" << std::endl;
  for(auto j = result.begin(); j != result.end(); ++j){
    std::cout << *j;
  }
  std::cout << std::endl;

  std::cout << std::endl;
  std::cout << "--------------------------------" << std::endl;

  return result;
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

	if (car_lido != BYTE_FLAG) {
	  if (car_atual == 0) {
		std::cout << "ERRO: Byte de flag de início de quadro com erros" << std::endl;
	  }
	  else if (car_atual == (int)(quadro.size()/8 - 1)) {
		std::cout << "ERRO: Byte de flag de final de quadro com erros" << std::endl;
	  }
	}
	
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

std::vector<int> CamadaEnlaceDadosReceptoraControleErroCRC (std::vector<int> quadro) {
  std::cout << "-----Recepcao CRC32-----" << std::endl;

  // Criar vetor CRC_32
  std::vector<int> crc32;
  crc32.push_back(1); // Highest bit added
  int crc32_value = CRC_32;
  for(int i = 0; i < 32; i++){
    unsigned int temp = crc32_value >> (31-i);
    temp &= 0x01;
    crc32.push_back(temp);
  }

  std::vector<int> dividend = quadro;
  std::vector<int> reminder;

  // Fazendo a divisão
  for(int i = 0; ((int)dividend.size() - i) > 32; i++){
    if(dividend[i] == 0) continue;
    for(int j = 0; j < 33; j++){
      if(dividend[i+j]){
        if(crc32[j]) dividend[i+j] = 0;
        else dividend[i+j] = 1; 
      }
      else{
        if(crc32[j]) dividend[i+j] = 1;
        else dividend[i+j] = 0; 
      }
    }
  }

  // Verificando Erros
  bool erro_flag = false;
  reminder.insert(reminder.begin(), dividend.end()-32, dividend.end());
  for(unsigned int i = 0; i < reminder.size(); i++){
    if(reminder[i] != 0){
      erro_flag = true;
    }
  }
  if(erro_flag){
    std::cout<< std::endl << "Erros ocorreram na transmissão" << std::endl;
  }

  // Imprimindo Resto
  std::cout << std::endl << "Resto:" << std::endl;
  for(auto j = reminder.begin(); j != reminder.end(); ++j){
    std::cout << *j;
  }
  std::cout << std::endl;

  // Recuperando e Imprimindo Dado
  std::vector<int> result;
  result.insert(result.end(), quadro.begin(), quadro.end()-32);
  std::cout << std::endl << "Dado Recuperado:" << std::endl;
  for(auto j = result.begin(); j != result.end(); ++j){
    std::cout << *j;
  }
  std::cout << std::endl;

  std::cout << std::endl;
  std::cout << "--------------------------------" << std::endl;

  return result;
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroCRC

std::vector<int> CamadaEnlaceDadosReceptoraControleErroCodigoHamming (std::vector<int> quadro) {
  std::cout << "-------- Recepção e verificação de erros por código de Hamming --------" << std::endl;
  int bits_redundantes = 0;
  int tam_quadro = quadro.size();

  while (tam_quadro + 1 > pow(2, bits_redundantes)) {
	bits_redundantes++;
  }
  int tam_res = tam_quadro - bits_redundantes;

  std::cout << "Quadro recebido:" << std::endl;
  for (int bit : quadro) {
	std::cout << bit;
  }
  std::cout << std::endl;

  // Janela é um dos conjuntos de bits consecutivos dentro do quadro que
  // que fazem parte da formação de um bit de paridade
  int bits_jan_percorridos; // Indica quantos bits da janela atual já foram percorridos
  int tam_janela; // Indica o tamanho máximo de uma janela, se for o bit-paridade 2, tamanho da janela é 2
  int qtd_uns; // Indica a quantidade de 1's que fazem parte da formação daquele bit de paridade
  int inic_janela; // Indica o início da janela atual para um certo bit de paridade
  int cont_janela; // Usado para percorrer uma janela de um bit de paridade
  int soma_paridades_erradas = 0;

  // Loop para percorrer cada bit de paridade detro do quadro
  for (int bitp = 1, potencia = 0; bitp <= tam_quadro; bitp = pow(2, potencia)) {
    potencia++;
	qtd_uns = 0;
	inic_janela = bitp;
	cont_janela = bitp;
	bits_jan_percorridos = 1;
	tam_janela = bitp;

	// Loop para percorrer cada janela do bit de paridade (bitp) atual
	while (inic_janela <= tam_quadro) {
	  // Loop para percorrer uma única janela do bitp
      for (cont_janela = inic_janela; tam_janela >= bits_jan_percorridos && cont_janela <= tam_quadro; cont_janela++, bits_jan_percorridos++) {
		if (quadro[cont_janela - 1] == 1) {
		  qtd_uns++;
		}
	  }
	  inic_janela = cont_janela + bitp;
	  bits_jan_percorridos = 1;
	}

	if (qtd_uns % 2 != 0) {
	  std::cout << "Erro na paridade do bit P" << bitp << std::endl;
	  soma_paridades_erradas += bitp;
	}
  }

  if (soma_paridades_erradas > 0) {
    std::cout << "Mudando o bit " << soma_paridades_erradas - 1 << " do quadro recebido..." << std::endl;
	quadro[soma_paridades_erradas - 1] ^= 1;
  }

  std::vector<int> resultado(tam_res, 0);
  int potencia, pos_res;
  for (int i = 1, pos_res = 1, potencia = 0; i <= tam_quadro; i++) {
    if (i == pow(2, potencia)) {
	  potencia++;
	}
	else {
	  resultado[pos_res - 1] = quadro[i - 1];
	  pos_res++;
	}
  }

  std::cout << "Quadro resultante:" << std::endl;
  for (int bit : resultado) {
	std::cout << bit;
  }
  std::cout << std::endl;

  return resultado;
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

