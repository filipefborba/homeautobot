# homeautobot

## Projeto 1 - Mundo Digital
Filipe Borba, Gabriel Moreira, Hugo Mendes

## Materiais

* Microcontrolador SAME 70
* Sensor de Presença/Movimento
* LED verde
* Sensor Touch Capacitivo TTP223B
* Mini Cooler
* MOSFET

## Descrição do Projeto
Nosso projeto consiste na automação e praticidade na realização de tarefas simples do cotidiano como ligar a luz e um ventilador. Nosso projeto tem por entradas um Sensor de Presença e um Sensor Touch. Já as saídas são um Mini Cooler e um LED Azul.

![Diagrama Básico do Projeto](diagrama.jpeg)

## Detalhamento

Utilizamos o PIOC porque não achamos necessário utilizar mais de um PIO para o projeto, porque é bastante simples. Além disso, foi necessário o uso de um MOSFET para conseguir controlar o Mini Cooler, pois a tensão de alimentação necessária dele era de 5V. A seguir, temos o diagrama de blocos com mais detalhes:

![Diagrama Detalhado do Projeto](diagrama2.jpeg)


## Vídeo do Projeto

https://youtu.be/pCus8W2sSO8