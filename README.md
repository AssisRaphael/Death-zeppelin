# Death Zeppelin

Death Zeppelin é um jogo 3D onde o jogador controla um zepelin que sobrevoa uma pequena cidade.  O zepelin está equipado com uma metralhadora rotatória e uma bomba nuclear, tornando possível a destruição completa da cidade. Porém, seu ataque não será ignorado, um trem cruzando a ferrovia  lança minas voadoras que perseguem seu zepelin e tentam te matar. Você tem tudo o que precisa  para destruí-los, mas não será tão fácil vencê-los. E aí, vai encarar?

Este jogo foi desenvolvido por Raphael Assis e Gleiston Guimarães, estudantes do CEFET-MG como um trabalho prático da disciplina de computação gráfica, cursada no segundo período da faculdade de Engenharia de Computação. O jogo é escrito em C e utiliza a biblioteca OpenGL.  Todos os modelos presentes foram modelados e texturizados por Gleiston Guimarães e a jogabilidade  foi desenvolvida por Raphael Assis. 

## Como instalar

​	O Jogo foi desenvolvido utilizando a linguagem C e foi escrito para rodar em ambiente linux. Para executá-lo é necessário instalar as bibliotecas openGL, freeGLUT, glew e SOIL. A biblioteca openGL já vem instala por padrão nos sistemas linux e por isso é necessário instalar apenas as outras 3 bibliotecas.	
Para baixá-las basta executar os seguintes comandos:

```shell
sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install freeglut3-dev 			#Instala a freeGLUT
sudo apt-get install libglew-dev 			#instala a glew
sudo apt install libsoil-dev 				#instala a SOIL
```

Após baixar as bibliotecas, basta acessar a pasta `src` do projeto no terminal e digitar o comando `make`. 
Os arquivos do jogo serão compilados e preparados para o uso. Em seguida basta utilizar o comando `make run` para executar o jogo. Caso ocorra algum problema nesse processo, tente usar o comando `make clean` para deletar os executáveis gerados e novamente usar `make` e `make run`.

## Tutorial do jogo

​	Para controlar a movimentação do zepelin basta usar as teclas **w, a, s, d** igual na maioria dos jogos.  As teclas **'w'** e **'s'** movem para frente e para trás e também controlam a velocidade do zepelin. Apertando **'w'** duas vezes ele irá acelerar seu movimento para frente e ao apertar **'s'** ele irá reduzir sua velocidade (se estiver se movendo para frente) ou andar para trás (se estiver parado). 

​	Há várias câmeras (ângulos de visão) disponíveis no jogo. Por padrão o jogo começa com uma câmera fixa na parte de cima do zepelin. Basta pressionar a tecla **'c'** para alternar entre as câmeras fixas. A tecla **'1'** ativa as câmeras fixas. Além dessas câmeras existe uma câmera god que pode andar livremente pelo cenário. Para ativá-la basta pressionar a tecla **'2'**. Os controle para movimentar a câmera god são as teclas **u, h, j, k** e eles funcionam similar as teclas **w, a, s, d**. Para alterar a inclinação da câmera god basta precionar **shift+u** ou **shift+j**. Para subir ou descer o ponto da câmera basta pressionar as teclas **shift+h** ou **shift+k**.

​	O zepelin é equipado com uma metralhadora e para acessa-lá basta pressionar a tecla **'m'**. A câmera da metralhadora é controlada da mesma forma da câmera god, exceto pelo fato de que ela não se move verticalmente. Basta mirar nos inimigos ou nas casas do cenário e atirar pressionando a tecla **'f'**. Para sair da metralhadora basta pressionar as teclas **'m'**, **'1'** ou **'2'** e voltar para as câmeras. 

​	Você está equipado com uma bomba nuclear e para ativá-la basta abrir a tampa do zepelin pressionando a tecla **'t'** (fecha com **shift+t**) e lançar a bomba pressionando a tecla **'b'**. É possível controlar a iluminação e efeitos visuais do cenário com as teclas **'l'** e **'n'**. Para fechar o jogo basta pressionar **'esc'** ou fechar a janela.

OBS: A jogabilidade não é muito boa devido ao fato de não se utilizar o mouse, porém esse trabalho foi feito no segundo período da faculdade. No mais, apreciem o jogo e obrigado por tê-lo baixado.

## Controles

* **w:** acelera o zepelin para frente, aperte novamente para ir mais rapido  (3 velocidades);

* **s:** acelera o zepelin para tras, caso estiver indo para frente desacelera o 
  zepelin (3 velocidades);

* **a, d:** muda a direçao do zepelin (esquerda/direita);

* **1:** entra na camera god, que é totalmente livre e te permite ir para qualquer ponto do cenário;

* **u, j:** move camera god para frente e para tras pelo cenário;

* **shift+u, shift+j:** Inclina camera god para cima e para baixo;

* **h, k:** olha pra esquerda e pra direita na camera god;

* **shift+h, shift+k:** move camera god para cima e para baixo;

* **2:** entra no modo camera fixa, que abilita as cameras que seguem o zepelin em um ponto fixo;

* **c:** muda ângulo de visao do zepelin;

* **m:** entra na camera de metralhadora;

* **u,h,j,k:** muda a direção em que a câmera mira;

* **f:** atira uma bala na direcão em que a câmera mira;

* **t:** abre o porta bombas;

* **T:** fechea a porta bombas;

* **b:** lança uma bomba (somente se a porta da bomba estiver aberta);

* **l:** liga e desliga iluminaçao;

* **n:** liga e desliga neblina;

* **r:** reinicia o jogo(demorado);

* **p:** para o zepellin;

## Conteúdo Extra

* Cenario destruivel: O cenario possui varias casas e uma torre do relogio "Great George" que podem ser destruidas com a metralhadora ou com a bomba.

* ArquiRival "Legendary Express": O trem navega a ferrovia continuamente lançando minas voadoras que perseguem o zepelin. As minas podem ser destruidas com a metralhadora.

* SkyBox: O cenario possui uma SkyBox texturizada.

* Neblina: O Cenario possui neblina ligavel e desligavel.

* Terceira Camera: O zepelin nao possui uma cabine, porém possui uma metralhadora em seu topo, que é controlada por uma camera em primeira pessoa.

* Ciclo de dia e noite usando a combinação entre iluminação e fog. 

* Música: O jogo possui música.
