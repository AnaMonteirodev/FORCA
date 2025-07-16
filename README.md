# 🎮 Jogo da Forca em C

Este é um projeto de um jogo da forca desenvolvido em linguagem C. O jogo escolhe palavras aleatórias de um arquivo `.txt`, permite que o jogador selecione o nível de dificuldade e até adicione novas palavras ao banco de dados!

## 📚 Funcionalidades

- Escolha entre 3 níveis de dificuldade (Fácil, Médio, Difícil).
- Palavras são lidas de um arquivo externo (`palavras.txt`).
- Jogador pode adicionar novas palavras ao jogo.
- Registro de pontuação com nome no arquivo `ranking.txt`.

## 🗂️ Estrutura de Arquivos

├── main.c // Código principal do jogo

├── forca.h // Arquivo de cabeçalho com declarações de funções e constantes

├── palavras.txt // Banco de dados com as palavras do jogo

├── ranking.txt // Armazena o nome do jogador e a pontuação

## 🧠 Lógica do Jogo

1. O jogador escolhe o nível de dificuldade.
2. Uma palavra é sorteada aleatoriamente do arquivo `palavras.txt`.
3. O jogador tenta adivinhar a palavra antes de completar o desenho da forca.
4. No final, o jogador pode:
   - Adicionar uma nova palavra.
   - Salvar sua pontuação no ranking com seu nome.

## ✅ Requisitos

- Compilador C (GCC, por exemplo)
- Terminal (Linux, macOS ou Windows com suporte a terminal)

📝 Licença
Este projeto é de uso educacional e pode ser reutilizado livremente com os devidos créditos.

Feito com ❤️ por Ana Paula
