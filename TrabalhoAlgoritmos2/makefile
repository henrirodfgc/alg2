CC = gcc
CFLAGS = -Wall -Wextra -Wunused -I./model -I./view -I./controller -I./lib -g 

TARGET = projeto_final.exe 
OBJ = main.o \
	lib/ui_console.o \
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
	view/cadastro/recursos_view.o\
	model/orcamento/evento.o\
	view/orcamento/evento_view.o\
	controller/orcamento/evento_controller.o\
	model/orcamento/item_orcamento.o\
	view/orcamento/item_orcamento_view.o\
	controller/orcamento/item_orcamento_controller.o\
	model/transacao/caixa.o\
	model/transacao/contas_receber.o\
	model/transacao/contas_pagar.o\
	view/transacao/transacao_view.o\
	controller/transacao/transacao_controller.o\
	view/relatorio/relatorio_view.o\
	controller/relatorio/relatorio_controller.o\
	view/xml/xml_view.o\
	controller/xml/xml_controller.o
	
	
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)
	
all: pre_clean $(TARGET)

pre_clean:
	if exist $(TARGET) del $(TARGET)
	if exist main.o del main.o
	if exist lib\ui_console.o del lib\ui_console.o
	if exist model/cadastro/cliente.o del model/cadastro/cliente.o
	if exist model/cadastro/equipe.o del model/cadastro/equipe.o
	if exist view/cadastro/cliente_view.o del view/cadastro/cliente_view.o
	if exist view/cadastro/equipe_view.o del view/cadastro/equipe_view.o
	if exist controller/cadastro/cliente_controller.o del controller/cadastro/cliente_controller.o
	if exist controller/cadastro/equipe_controller.o del controller/cadastro/equipe_controller.o
	
	if exist controller/saida_controller.o del controller/saida_controller.o
	
	if exist model/cadastro/produtora.o del model/cadastro/produtora.o
	if exist view/cadastro/produtora_view.o del view/cadastro/produtora_view.o
	if exist controller/cadastro/produtora_controller.o del controller/cadastro/produtora_controller.o
	
	if exist model/cadastro/fornece_e_parce.o del model/cadastro/fornece_e_parce.o
	if exist view/cadastro/fornece_e_parce_view.o del view/cadastro/fornece_e_parce_view.o
	if exist controller/cadastro/fornece_e_parce_controller.o del controller/cadastro/fornece_e_parce_controller.o
	
	if exist model/cadastro/operador.o del model/cadastro/operador.o
	if exist view/cadastro/operador_view.o del view/cadastro/operador_view.o
	if exist controller/cadastro/operador_controller.o del controller/cadastro/operador_controller.o
	
	if exist model/cadastro/recursos.o del model/cadastro/recursos.o
	if exist view/cadastro/recursos_view.o del view/cadastro/recursos_view.o
	if exist controller/cadastro/recursos_controller.o del controller/cadastro/recursos_controller.o

	if exist model/orcamento/evento.o del model/orcamento/evento.o
	if exist view/orcamento/evento_view.o del view/orcamento/evento_view.o
	if exist controller/orcamento/evento_controller.o del controller/orcamento/evento_controller.o

	if exist model/orcamento/item_orcamento.o del model/orcamento/item_orcamento.o
	if exist view/orcamento/item_orcamento_view.o del view/orcamento/item_orcamento_view.o
	if exist controller/orcamento/item_orcamento_controller.o del controller/orcamento/item_orcamento_controller.o

	# REGRAS PARA O MODULO TRANSACAO
	if exist model/transacao/caixa.o del model/transacao/caixa.o
	if exist model/transacao/contas_receber.o del model/transacao/contas_receber.o
	if exist model/transacao/contas_pagar.o del model/transacao/contas_pagar.o
	if exist view/transacao/transacao_view.o del view/transacao/transacao_view.o
	if exist controller/transacao/transacao_controller.o del controller/transacao/transacao_controller.o

	# REGRAS PARA O MODULO RELATORIO
	if exist controller/relatorio/relatorio_controller.o del controller/relatorio/relatorio_controller.o
	if exist view/relatorio/relatorio_view.o del view/relatorio/relatorio_view.o

	# REGRAS PARA O MODULO XML
	if exist controller/xml/xml_controller.o del controller/xml/xml_controller.o
	if exist view/xml/xml_view.o del view/xml/xml_view.o


clean:
ifeq ($(OS),Windows_NT)
	echo "[Windows] Verificando seguranca"
	if not exist "main.c" (echo [ERRO] Nao esta no diretorio do projeto & exit 1)
	echo "[Windows] Limpando arquivos"
	del *.o 2>nul
	del *.exe 2>nul
	if exist "lib" del "lib\*.o" 2>nul
	if exist "model\cadastro" del "model\cadastro\*.o" 2>nul
	if exist "view\cadastro" del "view\cadastro\*.o" 2>nul
	if exist "controller\cadastro" del "controller\cadastro\*.o" 2>nul
	if exist "model" del "model\*.o" 2>nul
	if exist "view" del "view\*.o" 2>nul
	if exist "controller" del "controller\*.o" 2>nul
	if exist "model\orcamento" del "model\orcamento\*.o" 2>nul
	if exist "view\orcamento" del "view\orcamento\*.o" 2>nul
	if exist "controller\orcamento" del "controller\orcamento\*.o" 2>nul
	if exist "model\transacao" del "model\transacao\*.o" 2>nul
	if exist "view\transacao" del "view\transacao\*.o" 2>nul
	if exist "controller\transacao" del "controller\transacao\*.o" 2>nul
	if exist "view\relatorio" del "view\relatorio\*.o" 2>nul
	if exist "controller\relatorio" del "controller\relatorio\*.o" 2>nul
	if exist "view\xml" del "view\xml\*.o" 2>nul
	if exist "controller\xml" del "controller\xml\*.o" 2>nul

else
	@echo "[Unix] Verificando seguranca"
	if [ ! -f "main.c" ]; then echo "[ERRO] Nao esta no diretorio do projeto"; exit 1; fi
	@echo "[Unix] Limpando arquivos"
	rm -f *.o
	rm -f lib/*.o
	rm -f model/*.o
	rm -f view/*.o
	rm -f controller/*.o
	rm -f model/cadastro/*.o
	rm -f view/cadastro/*.o
	rm -f controller/cadastro/*.o
	rm -f model/orcamento/*.o
	rm -f view/orcamento/*.o
	rm -f controller/orcamento/*.o
	rm -f model/transacao/*.o
	rm -f view/transacao/*.o
	rm -f controller/transacao/*.o
	rm -f *.exe
endif
	@echo "Limpeza concluida"
.PHONY: clean