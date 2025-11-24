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
	model/cadastro/cliente.o\
	model/cadastro/equipe.o\
	controller/cadastro/cliente_controller.o\
	controller/cadastro/equipe_controller.o\
	view/cadastro/cliente_view.o\
	view/cadastro/equipe_view.o\
	model/cadastro/produtora.o\
	controller/cadastro/produtora_controller.o\
	view/cadastro/produtora_view.o\
	model/cadastro/fornece_e_parce.o\
	view/cadastro/fornece_e_parce_view.o\
	controller/cadastro/fornece_e_parce_controller.o\
	model/cadastro/operador.o\
	view/cadastro/operador_view.o\
	controller/cadastro/operador_controller.o\
	controller/saida_controller.o\
	model/cadastro/recursos.o\
	controller/cadastro/recursos_controller.o\
	view/cadastro/recursos_view.o
	
# Regra principal: compilar tudo
$(TARGET):	$(OBJ)	
	$(CC)	$(OBJ)	-o	$(TARGET)
										
# Regra pra compilar e limpar antes (all)
all:	pre_clean $(TARGET)

# Regra pra deletar os .o (objetos) e o .exe antes de compilar pra ser uma compilação limpa
pre_clean:
	if	exist	$(TARGET)	del	$(TARGET)
	if	exist	main.o	del	main.o
	if	exist	model/cadastro/cliente.o	del	model/cadastro/cliente.o
	if	exist	model/cadastro/equipe.o	del	model/cadastro/equipe.o
	if	exist	view/cadastro/cliente_view.o	del	view/cadastro/cliente_view.o
	if	exist	view/cadastro/equipe_view.o	del	view/cadastro/equipe_view.o
	if	exist	controller/cadastro/cliente_controller.o	del	controller/cadastro/cliente_controller.o
	if	exist	controller/cadastro/equipe_controller.o	del	controller/cadastro/equipe_controller.o
	
	if	exist	controller/saida_controller.o	del	controller/saida_controller.o
	
	if	exist	model/cadastro/produtora.o	del	model/cadastro/produtora.o
	if	exist	view/cadastro/produtora_view.o	del	view/cadastro/produtora_view.o
	if	exist	controller/cadastro/produtora_controller.o	del	controller/cadastro/produtora_controller.o
	
	if	exist	model/cadastro/fornece_e_parce.o	del	model/cadastro/fornece_e_parce.o
	if	exist	view/cadastro/fornece_e_parce_view.o	del	view/cadastro/fornece_e_parce_view.o
	if	exist	controller/cadastro/fornece_e_parce_controller.o	del	controller/cadastro/fornece_e_parce_controller.o
	
	if	exist	model/cadastro/operador.o	del	model/cadastro/operador.o
	if	exist	view/cadastro/operador_view.o	del	view/cadastro/operador_view.o
	if	exist	controller/cadastro/operador_controller.o	del	controller/cadastro/operador_controller.o
	
	if	exist	model/cadastro/recursos.o	del	model/cadastro/recursos.o
	if	exist	view/cadastro/recursos_view.o	del	view/cadastro/recursos_view.o
	if	exist	controller/cadastro/recursos_controller.o	del	controller/cadastro/recursos_controller.o

# Regra pra limpar tudo geral (vc roda make clean)
clean:
ifeq ($(OS),Windows_NT)
	echo "[Windows] Verificando seguranca"
	if not exist "main.c" (echo [ERRO] Nao esta no diretorio do projeto & exit 1)
	echo "[Windows] Limpando arquivos"
	del *.o 2>nul
	del *.exe 2>nul
	if exist "model\cadastro" del "model\cadastro\*.o" 2>nul
	if exist "view\cadastro" del "view\cadastro\*.o" 2>nul
	if exist "controller\cadastro" del "controller\cadastro\*.o" 2>nul
	if exist "model" del "model\*.o" 2>nul
	if exist "view" del "view\*.o" 2>nul
	if exist "controller" del "controller\*.o" 2>nul
else
	@echo "[Unix] Verificando seguranca"
	if [ ! -f "main.c" ]; then echo "[ERRO] Nao esta no diretorio do projeto"; exit 1; fi
	@echo "[Unix] Limpando arquivos"
	rm -f *.o
	rm -f model/*.o
	rm -f view/*.o
	rm -f controller/*.o
	rm -f model/cadastro/*.o
	rm -f view/cadastro/*.o
	rm -f controller/cadastro/*.o
	rm -f *.exe
endif
	@echo "Limpeza concluida"
.PHONY: clean # Avisa q 'clean' nao é um arquivo pra n dar erro