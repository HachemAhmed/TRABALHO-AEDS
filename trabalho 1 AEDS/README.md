# 🔥 Simulador de Propagação de Incêndios em Florestas 🔥

<p align="center">
  <img src="https://github.com/HachemAhmed/Trabalho-AEDS/blob/main/trabalho%201%20AEDS/imagem/20250426_2058_Cervo%20em%20Perigo_remix_01jst8hp3zfgtvh9zw9yyybr29.png" alt="capa do projeto" width = 400/>
</p>

## 1. Introdução 📖

Este documento apresenta a documentação completa do simulador de propagação de incêndios em florestas, implementado como trabalho para a disciplina de AEDS (Algoritmos e Estrutura de Dados I), ministrada pelo professor [Michel Pires](https://github.com/mpiress) no CEFET-MG (Centro Federal de Educação Tecnológica de Minas Gerais).

O simulador modela computacionalmente a propagação do fogo em uma matriz representativa de uma floresta, onde cada célula representa um quadrante da área florestal com diferentes estados possíveis.

### Objetivos 🎯

O objetivo principal do simulador é analisar o comportamento da propagação de incêndios em diferentes condições ambientais, incluindo a influência ou não do vento, bem como simular a movimentação de um animal na busca por rotas de fuga seguras.

### Elementos do Sistema 🌲🔥🐾

| Elemento | Descrição |
|----------|-----------|
| **Floresta** 🌲 | Matriz de dimensões N × M, com diferentes estados para cada célula |
| **Fogo** 🔥    | Propaga-se ortogonalmente (com ou sem influência do vento) |
| **Animal** 🐾 | Busca rotas de fuga em direção a locais seguros ou fontes de água |

> A simulação ocorre por iterações, onde em cada ciclo o animal se move primeiro, depois o fogo se propaga, podendo dar ao animal uma "segunda chance" caso a posição onde ele se encontre seja atingida pelo fogo.

## 2. Metodologias 🛠️

### 2.1 Estruturas de Dados 📚

O sistema foi desenvolvido utilizando as seguintes estruturas de dados principais:

- **Matriz Bidimensional**: `std::vector<std::vector<int>>`
- **Vetores de Pares**: `std::vector<std::pair<int, int>>`
- **Buffering Duplo**: Técnica para a propagação do fogo

#### Justificativa das Estruturas 

✅ **Flexibilidade**: Permitem trabalhar com matrizes de tamanho variável  
✅ **Eficiência**: Acesso rápido aos elementos via organização direta  
✅ **Facilidade de manipulação**: Operações de inserção e atualização simplificadas

### 2.2 Representação dos Estados 🌳💧

A floresta é representada por uma matriz onde cada célula pode assumir um dos seguintes valores:

| Valor | Estado | Descrição |
|-------|--------|-----------|
| **0** | Área vazia      | Não queima |
| **1** | Árvore saudável  | Pode pegar fogo |
| **2** | Árvore em chamas  | Propaga fogo por 2 iterações |
| **3** | Árvore queimada    | Não propaga mais fogo |
| **4** | Presença de água  | Área segura |

### 2.3 Regras de Propagação do Fogo 🔥

O fogo se propaga seguindo estas regras:

1. Uma árvore saudável (1) entra em chamas (2) se houver ao menos uma árvore vizinha em chamas.
2. Uma árvore em chamas (2) permanece nesse estado por dois ciclos de simulação antes de se tornar queimada (3).
3. A propagação ocorre exclusivamente nas direções ortogonais, podendo ser:
   - **Sem influência do vento**: O fogo se propaga uniformemente nas quatro direções ortogonais.
   - **Com influência do vento** : O fogo se propaga apenas nas direções configuradas no arquivo `config.hpp`.

### 2.4 Mecanismo do Animal 🐾

#### Movimentação 🎯

O animal presente na simulação segue estas regras de movimentação:

1. **Nascimento** : Ocorre em uma posição aleatória segura (valor 0, 1 ou 4).
2. **Prioridade de movimento**:

   | Prioridade | Tipo de Célula | Valor |
   |------------|----------------|-------|
   | Alta       | Água         | 4     |
   | Média      | Área vazia ou árvore saudável | 0 ou 1 |
   | Baixa      | Árvore queimada  | 3     |

3. **Comportamento com água** 💧:
   - A posição se torna vazia (0)
   - Células adjacentes se tornam árvores saudáveis (1)

4. **Permanência**: Pode permanecer até 3 iterações em uma área vazia.

#### Mecanismo de Segunda Chance 🌟

Quando o animal é atingido pelo fogo, o sistema oferece uma "segunda chance":

1. O animal tenta se mover para:
   - A posição anterior onde estava ou casas adjacentes seguras não afetadas pelo fogo

2. Se o deslocamento for bem-sucedido:
   - Um passo adicional é contabilizado
   - As coordenadas são registradas no caminho percorrido

3. Se não houver opção de fuga, o animal morre.

#### Estatísticas do Animal 📊

Ao final da simulação, o arquivo de saída incluirá:
- Número total de passos realizados
- Quantidade de vezes que o animal encontrou água
- Caminho completo percorrido (coordenadas)
- Status final (sobreviveu ou foi atingido pelo fogo)

## 3. Estudo de Caso e Resultados 📈

### 3.1 Análise da Propagação do Fogo 

#### Sem Influência do Vento 

- Padrão de expansão simétrica
- Formação de círculos concêntricos
- Taxa de propagação consistente em todas as direções

#### Com Influência do Vento 

- Propagação assimétrica
- Padrões alongados nas direções do vento
- Velocidade maior nas direções favorecidas pelo vento

### 3.2 Comportamento do Animal 

A análise do comportamento do animal revela estratégias de sobrevivência e padrões de movimento:

1. **Busca por Água** : Prioridade máxima que garante segurança temporária
2. **Escolha de Rotas**: Variação devido à seleção aleatória entre opções equivalentes
3. **Taxa de Sobrevivência**: Correlacionada com disponibilidade de água e velocidade do fogo

### 3.3 Eficácia da Previsão de Incêndios 

O simulador permite estimar:

- **Tempo até extinção**: Número de iterações necessárias
- **Área máxima afetada**: Total de células atingidas pelo fogo
- **Velocidade de propagação**: Taxa de expansão por iteração

## 4. Conclusões 📝

### 4.1 Sobre o Simulador 💻

O simulador demonstra ser uma ferramenta eficaz para modelar e analisar padrões de propagação de fogo em ambientes florestais.

#### Principais Conclusões ✅

1. **Precisão da Modelagem**: O modelo baseado em células com estados discretos representa satisfatoriamente os aspectos da propagação de incêndios florestais.
2. **Importância do Fator Vento**: A inclusão do vento como variável resulta em padrões mais realistas.
3. **Buffering Duplo**: Técnica essencial para garantir a correta propagação do fogo sem interferências.

## 5. Modo de Compilação ⚙️

O programa foi desenvolvido para ser compilado e executado em ambientes Linux, utilizando o compilador g++ com suporte a C++11 ou superior.

### Passos para Compilação e Execução 

```bash
# Limpeza prévia
make clean

# Compilação
make

# Execução
make run
```

> O Makefile está configurado para compilar todos os arquivos `.cpp` localizados na pasta `src/` e gerar um executável na pasta raiz do projeto.

### 5.1 Requisitos do Sistema 💻

- Sistema operacional Linux
- Compilador g++ com suporte a C++11 ou superior
- Make instalado

### 5.2 Arquivos de Entrada e Saída 📂

#### Entrada (`input.dat`)
```
N M fogoLinha fogoCol
[matriz NxM com os estados iniciais]
```

Onde:
- **N, M**: Dimensões da matriz
- **fogoLinha, fogoCol**: Coordenadas iniciais do fogo
- **Matriz**: Valores inteiros de 0 a 4 representando os estados iniciais

#### Saída (`output.dat`)
- Estado da matriz a cada iteração
- Estatísticas finais do animal
- Registro dos eventos significativos

## 6. Tratamento de Erros 🚨

O simulador incorpora vários mecanismos de tratamento de erros para lidar com situações excepcionais:

| Tipo de Erro               | Mecanismo de Tratamento                |
|----------------------------|----------------------------------------|
| **Validação de Entrada**  | Verifica existência e validade do arquivo |
| **Verificação de Posições**  | Valida coordenadas dentro dos limites da matriz |
| **Registro de Erros**     | Todos os erros são registrados no `output.dat` |

### 6.1 Limitações no Tratamento de Erros 

⚠️ **Responsabilidades do Usuário:**

1. **Formato do Arquivo**: Seguir especificação de `input.dat`
2. **Valores Válidos**: Matriz deve conter apenas valores de 0 a 4
3. **Dimensões Consistentes**: Matriz deve ter exatamente as dimensões N × M
4. **Coordenadas Corretas**: Posição inicial do fogo deve ser válida

## 7. Bibliotecas e Dependências 📚

### 7.1 STL (Standard Template Library) 

#### 7.1.1 `<vector>` 
```cpp
// Exemplo de uso no arquivo floresta.hpp
private:
    int linhas;
    int colunas;
    vector<vector<int>> mapa;
```

#### 7.1.2 `<string>`  e `<sstream>`
```cpp
// Exemplo de uso no arquivo io.hpp
static void logError(const std::string &filename, const std::string &errorMessage);
```

#### 7.1.3 `<utility>` 
```cpp
// Exemplo de uso no arquivo simulacao.hpp
std::vector<std::pair<int, int>> caminhos;
```

### 7.2 Bibliotecas para Aleatoriedade 🎲

- `<random>` e `<cstdlib>`: Geradores de números aleatórios
- `<ctime>`: Inicialização da semente aleatória

### 7.3 Bibliotecas para Algoritmos 

- `<algorithm>`: Operações de ordenação e busca

### 7.4 Configurações Personalizadas 

#### 7.4.1 `config.hpp` 🛠️
```cpp
// Número máximo de iterações
const int K = 100;

// Configuração do vento
const bool VENTO_ATIVADO = false;

// Direções do vento
const bool VENTO_CIMA = false;
const bool VENTO_BAIXO = true;
const bool VENTO_ESQUERDA = false;
const bool VENTO_DIREITA = true;

// Tempo máximo de permanência do animal
const int MAX_MOVIMENTO = 3;
```
## 8. Creditos 📚

-Arquivo Makefile oferecido pelo professor [Michel Pires](https://github.com/mpiress)

## 9. Autores 👤

- **Nome**: Ahmed Amer Hachem
- **Instituição**: CEFET-MG
- **Disciplina**: AEDS (Algoritmos e Estrutura de Dados I)
- **Professor**: [Michel Pires](https://github.com/mpiress)
- **Meio de contato**: ahmedahachem@gmail.com 
- **Meio de contato**: instagram: @ahmed_hachem__ 

