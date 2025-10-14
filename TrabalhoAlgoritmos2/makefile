
CC	=	gcc
CFLAGS	=	-Wall	-Wextra	-Wunused	-I./model	-I./view	-I./controller	-g 

TARGET	=	projeto_final.exe
OBJ  = main.o	\
			model/cliente.o\
			controller/cliente_controller.o\
			view/cliente_view.o
	

$(TARGET):	$(OBJ)	
	$(CC)	$(OBJ)	-o	$(TARGET)
										
all:	pre_clean $(TARGET)

pre_clean:
	if	exist	$(TARGET)	del	$(TARGET)
	if	exist	main.o	del	main.o
	if	exist model/cliente.o	del	model/cliente.o
	if	exist	view/cliente_view.o	del	view.o
	if	exist	controller/cliente_controller.o	del	controller/cliente_controller.o


				
clean:
ifeq ($(OS),Windows_NT)
	@echo "[Windows] Verificando seguranca..."
	@if not exist "main.c" (echo [ERRO] Nao esta no diretorio do projeto! && exit 1)
	@echo "[Windows] Limpando arquivos..."
	@del *.o 2>nul
	@del model\*.o 2>nul
	@del view\*.o 2>nul
	@del controller\*.o 2>nul
	@del *.exe 2>nul
else
	@echo "[Unix] Verificando seguranca..."
	@if [ ! -f "main.c" ]; then echo "[ERRO] Nao esta no diretorio do projeto!"; exit 1; fi
	@echo "[Unix] Limpando arquivos..."
	@rm -f *.o
	@rm -f model/*.o
	@rm -f view/*.o
	@rm -f controller/*.o
	@rm -f *.exe
endif
	@echo "Limpeza concluida!"

.PHONY: clean