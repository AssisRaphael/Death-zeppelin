CC=gcc
OPCOES_COMPILADOR=-I. -lSOIL -lglut -lGLU -lGLEW -lGL -lm -lSDL -lSDL_mixer
TODOS_ARQUIVOS_PONTOH = glm.h glmint.h funcoes.h image_DXT.h image_helper.h stbi_DDS_aug.h stbi_DDS_aug_c.h stb_image_aug.h
TODOS_ARQUIVOS_OBJ = main.o glm.o glmimg.o glm_util.o stb_image_aug.o image_DXT.o image_helper.o

%.o: ../%.c $(TODOS_ARQUIVOS_PONTOH)
	$(CC) -o $@ -c $< $(OPCOES_COMPILADOR)

all: $(TODOS_ARQUIVOS_OBJ)
	gcc -o main $^ $(OPCOES_COMPILADOR)

run: all
	./main

clean:
	rm *.o main
