
-include ../config.mk

INCLUDES:=-I ./ -I ../$(LIB_DIR) -I ../$(LIB_DIR)/$(INCLUDE_DIR)/
SRC:=$(wildcard $(SRC_DIR)/*.cpp)
OBJ:=$(subst $(SRC_DIR),$(BUILD_DIR),$(SRC:.cpp=.o))

.PHONY: all clean

all: $(OBJ)
	@echo "Les fichiers propres à l'exec sont prêts !"
	@echo $(BIG_SEPARATOR)

$(OBJ) : $(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CCFLAGS) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<
	@echo "$(notdir $@) a été compilé."

-include $(BUILD_DIR)/*.d

clean:
	@rm -f $(BUILD_DIR)/*
	@echo "Les fichiers binaires propres au projet ont été supprimés :("
