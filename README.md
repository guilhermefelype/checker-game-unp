# checker-game-unp
Este é um projeto de um **jogo de damas em 3D**, desenvolvido utilizando **C++** com **OpenGL**. O jogo apresenta um tabuleiro tridimensional, peças estilizadas e permite alternar entre os turnos dos jogadores. O tabuleiro é rotacionado automaticamente para que as peças do jogador atual estejam sempre na parte inferior da tela.

## Recursos do Projeto

- **Tabuleiro em 3D**: Renderização realista utilizando OpenGL.
- **Peças estilizadas**: Cilindros representando as peças, com uma coroa visual para as damas.
- **Turnos alternados**: Tabuleiro rotaciona automaticamente para o jogador ativo.
- **Organização inicial padrão**: Peças brancas na parte inferior e peças pretas na superior.
- **Câmera dinâmica**: Visualização adaptada para proporcionar imersão ao jogador.

## Tecnologias Utilizadas

- **Linguagem**: C++
- **Biblioteca Gráfica**: OpenGL (GLUT)

## Requisitos para Execução

- Um compilador C++ (como GCC ou MSVC).
- A biblioteca OpenGL instalada no sistema.
- GLUT configurado.

## Como Executar

1. Clone este repositório:
   ```bash
   git clone https://github.com/seu-usuario/jogo-damas-3d.git

2. Compile o código:
    ```bash
    g++ -o damas3d jogo_damas_3d.cpp -lGL -lGLU -lglut

3. Execute o programa:
    ```bash
    ./damas3d