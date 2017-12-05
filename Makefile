-include config.mk

EXEC_SRC:=$(wildcard $(EXEC_SRC_DIR)/*.cpp)
EXEC_OBJ:=$(subst $(EXEC_SRC_DIR),$(EXEC_BUILD_DIR),$(EXEC_SRC:.cpp=.o))

SEQS_RAW:=$(wildcard $(EXEC_DATA_DIR)/*.sequence)
SEQS:=$(subst $(EXEC_DATA_DIR), $(BUILD_DIR), $(SEQS_RAW:.sequence=.seq))

TRG:=$(addprefix $(BUILD_DIR)/, $(notdir $(EXEC_SRC:.cpp=.out)))
LDFLAGS=-Wl,-Map,$@.map -mmcu=$(MCU)
HEXROMTRG=$(TRG:.out=.hex)
HEXFORMAT=ihex

LOGFILE=$(BUILD_DIR)/`date +'%y-%m-%d_%H:%M:%S'`.log

.PHONY: all pre-link install main test mem clean debug

## TARGETS ##
all: | pre-link $(HEXROMTRG)
	@echo "Le projet est prêt à être installé !"
	@echo $(BIG_SEPARATOR)

pre-link:
	@make -C $(LIB_DIR) --no-print-directory
	@make -C $(EXEC_DIR) --no-print-directory

$(TRG): $(BUILD_DIR)/%.out: $(EXEC_BUILD_DIR)/%.o $(LIB_DIR)/$(LIBL)
	@mkdir -p $(BUILD_DIR)
	$(eval NAME=$(notdir $(basename $@)))
	@$(CC) $(LDFLAGS) -o $@ $< -l $(LIB) -L $(LIB_BUILD_DIR)
	@echo "Liaison des différentes parties du programme \"$(NAME)\"..."
	@echo $(SEPARATOR)

$(HEXROMTRG): %.hex : %.out
	@echo "Génération du fichier hexadécimal pour "$<" en cours..."
	@$(OBJCOPY) -j .text -j .data -O $(HEXFORMAT) $< $@
	@echo $(SEPARATOR)

install: all
	@echo "Installation du programme \"$(project)\" en cours..."
	@$(AVRDUDE) -c $(AVRDUDE_PROGRAMMERID) -l $(LOGFILE) -p $(MCU) -P -e -U flash:w:$(BUILD_DIR)/$(project).hex
	@echo $(SEPARATOR)
	@echo "Installation terminée :D"
	@echo $(BIG_SEPARATOR)

$(SEQS) : $(BUILD_DIR)/%.seq : $(EXEC_DATA_DIR)/%.sequence
	@mkdir -p $(BUILD_DIR)
	@$(PROGMEM) -o $@ $<
	@echo "Séquence \"$(notdir $(basename $@))\" générée avec succès !"

## ALIASES ##
main:
	@make --no-print-directory install project=karl

test:
	@make --no-print-directory install project=test

mem:
	@make --no-print-directory install project=memloader
	$(if $(code), make --no-print-directory send code=$(code))

## COMMANDS ###
send: $(SEQS)
	@echo "Envoi de la séquence \"$(code)\" vers le robot..."
	@$(SERIEVIA) -e -f $(BUILD_DIR)/$(code).seq
	@echo $(BIG_SEPARATOR)

clean:
	@make -C $(LIB_DIR) clean --no-print-directory
	@make -C $(EXEC_DIR) clean --no-print-directory
	@rm -f $(BUILD_DIR)/*
	@echo "Tous les fichiers binaires ont été supprimés :'("

debug:
	@echo "$(SEQS)"
	@echo "Don't mind me"
