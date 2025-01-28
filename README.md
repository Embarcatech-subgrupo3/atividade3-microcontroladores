# atividade3-microcontroladores

# Geração de Animações em Matriz de LEDs 5x5  

Este projeto foi desenvolvido como parte da atividade obrigatória da Unidade 4 | Capítulo 3 – 201234A do curso de Microcontroladores. 
O objetivo é gerar animações em uma matriz de LEDs 5x5 utilizando o microcontrolador Raspberry Pi Pico W, um teclado matricial 4x4 e, opcionalmente, um buzzer.  

## **Descrição do Projeto**  
O sistema responde às entradas do teclado matricial, gerando animações ou configurando a matriz de LEDs de acordo com as teclas pressionadas.  

### **Funcionalidades**  
1. **Animações (0-9)**:  
   - Cada tecla numérica (0 a 9) executa uma animação específica na matriz de LEDs.  
   - Cada animação possui pelo menos 5 frames e é exibida com fluidez.  

2. **Comandos Especiais**:  
   - **Tecla A**: Desliga todos os LEDs.  
   - **Tecla B**: Liga todos os LEDs na cor azul com 100% de intensidade.  
   - **Tecla C**: Liga todos os LEDs na cor vermelha com 80% de intensidade.  
   - **Tecla D**: Liga todos os LEDs na cor verde com 50% de intensidade.  
   - **Tecla #**: Liga todos os LEDs na cor branca com 20% de intensidade.  
   - **Tecla \***: Reinicia o microcontrolador para o modo de gravação.  

3. **Especificações Opcionais**:  
   - Geração de sinal sonoro com o buzzer para uma das animações.  

## **Componentes Utilizados**  
- **Microcontrolador**: Raspberry Pi Pico W.  
- **Matriz de LEDs**: WS2812 (5x5).  
- **Teclado Matricial**: 4x4.  
- **Buzzer Passivo Eletromagnético**: MLT-8530 SMD 3.6V (opcional).  

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

