# =============================================
# MAKEFILE (O COMPILADOR)
# Pra compilar o projeto todo de uma vez no MinGW/Linux
# =============================================

CC	=	gcc
# Flags de compilação: -Wall -Wextra pra mostrar todos os avisos (bom pra achar erro)
# -I pra dizer onde estão os includes (model view controller)
CFLAGS	=	-Wall	-Wextra	-Wunused	-I./model	-I./view	-I./controller	-g 

TARGET	=	projeto_final.exe # O nome do arquivo final
OBJ	= main.o	\
	model/cliente.o\
	model/equipe.o\
	controller/cliente_controller.o\
	controller/equipe_controller.o\
	view/cliente_view.o\
	view/equipe_view.o\
	model/produtora.o\
	controller/produtora_controller.o\
	view/produtora_view.o\
	model/fornece_e_parce.o\
	view/fornece_e_parce_view.o\
	controller/fornece_e_parce_controller.o\
	controller/saida_controller.o\
	model/recursos.o\
	controller/recursos_controller.o\
	view/recursos_view.o
	
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
	if	exist model/equipe.o	del	model/equipe.o
	if	exist	view/cliente_view.o	del	view/cliente_view.o
	if	exist	view/equipe_view.o	del	view/equipe_view.o
	if	exist	controller/cliente_controller.o	del	controller/cliente_controller.o
	if	exist	controller/equipe_controller.o	del	controller/equipe_controller.o
	if	exist	controller/saida_controller.o	del	controller/saida_controller.o
	if	exist	model/produtora.o	del	model/produtora.o
	if	exist	view/produtora_view.o	del	view/produtora_view.o
	if	exist	controller/produtora_controller.o	del	controller/produtora_controller.o
	if	exist	model/fornece_e_parce.o	del	model/fornece_e_parce.o
	if	exist	view/fornece_e_parce_view.o	del	view/fornece_e_parce_view.o
	if	exist	controller/fornece_e_parce_controller.o	del	controller/fornece_e_parce_controller.o
	if	exist	model/recursos.o	del	model/recursos.o
	if	exist	view/recursos_view.o	del	view/recursos_view.o
	if	exist	controller/recursos_controller.o	del	controller/recursos_controller.o

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