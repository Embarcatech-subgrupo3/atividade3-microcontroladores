# atividade3-microcontroladores

# Geração de Animações em Matriz de LEDs 5x5  

Este projeto foi desenvolvido como parte da atividade obrigatória da Unidade 4 | Capítulo 3 – 201234A do curso de Microcontroladores. 
O objetivo é gerar animações em uma matriz de LEDs 5x5 utilizando o microcontrolador Raspberry Pi Pico W, um teclado matricial 4x4 e, opcionalmente, um buzzer.  

## **Descrição do Projeto**  
O sistema responde às entradas do teclado matricial, gerando animações ou configurando a matriz de LEDs de acordo com as teclas pressionadas.  

### **Funcionalidades**  
1. **Animações (1-8)**:  
   - Cada tecla numérica (1 a 8) executa uma animação específica na matriz de LEDs.  
   - Cada animação possui pelo menos 5 frames e é exibida com fluidez.
  

2. **Comandos Especiais**:  
   - **Tecla A**: Desliga todos os LEDs.  
   - **Tecla B**: Liga todos os LEDs na cor azul com 100% de intensidade.  
   - **Tecla C**: Liga todos os LEDs na cor vermelha com 80% de intensidade.  
   - **Tecla D**: Liga todos os LEDs na cor verde com 50% de intensidade.  
   - **Tecla #**: Liga todos os LEDs na cor branca com 20% de intensidade.  


## **Componentes Utilizados**  
- **Microcontrolador**: Raspberry Pi Pico W.  
- **Matriz de LEDs**: WS2812 (5x5).  
- **Teclado Matricial**: 4x4.  
- **Buzzer Passivo Eletromagnético**: MLT-8530 SMD 3.6V.

## **Requisitos do Ambiente**  
- **Software**:  
  - Visual Studio Code com Pico SDK configurado.  
  - Simulador Wokwi integrado ao VS Code.  

- **Hardware**:  
  - Raspberry Pi Pico W.  
  - Conexões para o teclado matricial e matriz de LEDs.
 
# Estrutura da equipe
Líder: Luiz Gustavo do Valle Vieira

Desenvolvedores:<br>
Lana Ramos Gomes<br>
Matheus Félix Dias<br>
Paulo Henrique de Farias Martins<br>
Douglas Ramos de Almeida<br>

## **Instruções de Uso**  

### **1. Importar o projeto**
1. Abra o **VS Code** ou outro editor compatível.
2. Certifique-se de ter a **extensão Raspberry Pico PI** instalada.
3. Importe os arquivos do projeto para o editor.

---

### **2. Compilar o projeto**
1. Compile o projeto para gerar a build, configurando o ambiente de acordo com a Raspberry Pi Pico.
2. Certifique-se de que todas as dependências estão configuradas corretamente.

---

### **3. Executar a simulação**
1. Abra o arquivo `diagram.json` utilizando a extensão **Wokwi**.
2. Inicie a simulação para visualizar o funcionamento do circuito e testar as funcionalidades.

   #Teclas do teclado matricial com funcionalidades:
   - **Tecla A**: Desliga todos os LEDs.  (Responsável Paulo Henrique).
   - **Tecla B**: Liga todos os LEDs na cor azul com 100% de intensidade.  (Responsável Luiz Gustavo).
   - **Tecla C**: Liga todos os LEDs na cor vermelha com 80% de intensidade. (Responsável Lana Ramos).
   - **Tecla D**: Liga todos os LEDs na cor verde com 50% de intensidade.  (Responsável Luiz Gustavo).
   - **Tecla #**: Liga todos os LEDs na cor branca com 20% de intensidade. (Responsável Douglas Ramos).
   - Tecla 1 🔊 (Animação com musica) (Responsável Paulo Henrique).
   - Tecla 2 🔇 (Animação sem musica) (Responsável Lana Ramos).
   - Tecla 3 🔊 (Animação com musica) (Responsável Luiz Gustavo).
   - Tecla 4 🔇 (Animação sem musica) (Responsável Paulo Henrique).
   - Tecla 5 🔇 (Animação sem musica) (Responsável Paulo Henrique).
   - Tecla 6 🔇 (Animação sem musica) (Responsável Luiz Gustavo).
   - Tecla 7 🔇 (Animação sem musica) (Responsável Paulo Henrique).
   - Tecla 8 🔇 (Animação sem musica) (Responsável Luiz Gustavo).

---

## Demonstração em Vídeo

Confira uma demonstração prática do projeto no YouTube:

https://www.youtube.com/watch?v=jkjOIlceyRM
