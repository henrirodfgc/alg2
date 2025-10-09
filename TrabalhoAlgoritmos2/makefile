
CC	=	gcc
CFLAGS	=	-Wall	-Wextra	-Wunused	-I./model	-I./view	-I./controller	-g 

TARGET	=	projeto_final.exe
SRCS	=	main.c
OBJ  = main.o	\
			model/cliente.o\
			controller/cliente_controller.o\
			view/cliente_view.o
OBJS	=	$(SRCS:.c=.o)	
	

$(TARGET):	$(OBJ)	
	$(CC)	$(OBJ)	-o	$(TARGET)
										
all:	pre_clean $(TARGET)

pre_clean:
	if	exist	$(TARGET)	del	$(TARGET)
	if	exist	main.o	del	main.o
	if	exist model/cliente.o	del	model/cliente.o
	if	exist	view/cliente_view.o	del	view.o
	if	exist	controller/cliente_controller.o	del	controller/cliente_controller.o


main.o:	main.c 
	$(CC)	$(CFLAGS)	-c	main.c	-o	main.o 

model/cliente.o:	model/cliente.c	model/cliente.h
	$(CC)	$(CFLAGS)	-c	model/cliente.c	-o	model/cliente.o

view/cliente_view.o:	view/cliente_view.c	view/cliente_view.h
	$(CC)	$(CFLAGS)	-c	view/cliente_view.c	-o	view/cliente_view.o 

controller/cliente_controller.o:	controller/cliente_controller.c controller/cliente_controller.h model/cliente.h view/cliente_view.h
	$(CC)	$(CFLAGS)	-c	controller/cliente_controller.c	-o	controller/cliente_controller.o 


				
clean:
ifeq ($(OS),Windows_NT)
	@echo "[Windows] Verificando seguranca..."
	@if not exist "main.c" ( \
		echo [ERRO] Arquivo main.c nao encontrado! && \
		echo [INFO] Certifique-se de estar no diretorio: TrabalhoAlgoritmos2 && \
		exit 1 \
	)
	@echo "[Windows] Limpando arquivos..."
	-del *.o 2>nul
	-del model\*.o 2>nul
	-del view\*.o 2>nul
	-del controller\*.o 2>nul
	-del *.exe 2>nul
else
	@echo "[Unix] Verificando seguranca..."
	@if [ ! -f "main.c" ]; then \
		echo "[ERRO] Arquivo main.c nao encontrado!"; \
		echo "[INFO] Certifique-se de estar no diretorio: TrabalhoAlgoritmos2"; \
		exit 1; \
	fi
	@echo "[Unix] Limpando arquivos..."
	-rm -f *.o
	-rm -f model/*.o
	-rm -f view/*.o
	-rm -f controller/*.o
	-rm -f *.exe
endif
	@echo "Limpeza concluida com seguranca!"

.PHONY: clean