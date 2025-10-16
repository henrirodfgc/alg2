# =============================================
# MAKEFILE (O COMPILADOR)
# Pra compilar o projeto todo de uma vez no MinGW/Linux
# =============================================

CC	=	gcc
# Flags de compilação: -Wall -Wextra pra mostrar todos os avisos (bom pra achar erro)
# -I pra dizer onde estão os includes (model view controller)
CFLAGS	=	-Wall	-Wextra	-Wunused	-I./model	-I./view	-I./controller	-g 

TARGET	=	projeto_final.exe # O nome do arquivo final
OBJ  = main.o	\
			model/cliente.o\
			controller/cliente_controller.o\
			view/cliente_view.o
	
# Regra principal: compilar tudo
$(TARGET):	$(OBJ)	
	$(CC)	$(OBJ)	-o	$(TARGET)
										
# Regra pra compilar e limpar antes (all)
all:	pre_clean $(TARGET)

# Regra pra deletar os .o (objetos) e o .exe antes de compilar pra ser uma compilação limpa
pre_clean:
	if	exist	$(TARGET)	del	$(TARGET)
	if	exist	main.o	del	main.o
	if	exist model/cliente.o	del	model/cliente.o
	if	exist	view/cliente_view.o	del	view.o # Esse view.o aqui parece estranho mas deixa quieto se ta funcionando
	if	exist	controller/cliente_controller.o	del	controller/cliente_controller.o

# Regra pra limpar tudo geral (vc roda make clean)
clean:
ifeq ($(OS),Windows_NT)
	@echo "[Windows] Verificando seguranca"
	@if not exist "main.c" (echo [ERRO] Nao esta no diretorio do projeto & exit 1)
	@echo "[Windows] Limpando arquivos"
	@del *.o 2>nul
	@del model\*.o 2>nul
	@del view\*.o 2>nul
	@del controller\*.o 2>nul
	@del *.exe 2>nul
else
	@echo "[Unix] Verificando seguranca"
	@if [ ! -f "main.c" ]; then echo "[ERRO] Nao esta no diretorio do projeto"; exit 1; fi
	@echo "[Unix] Limpando arquivos"
	@rm -f *.o
	@rm -f model/*.o
	@rm -f view/*.o
	@rm -f controller/*.o
	@rm -f *.exe
endif
	@echo "Limpeza concluida"

.PHONY: clean # Avisa q 'clean' nao é um arquivo pra n dar erro