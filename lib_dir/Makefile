-include ../config.mk

LD:=ar
LDFLAGS:=-rcs
SRC:=$(wildcard $(SRC_DIR)/*.cpp)
OBJ:=$(subst $(SRC_DIR),$(BUILD_DIR),$(SRC:.cpp=.o))
INCLUDES:=-I ./ -I $(INCLUDE_DIR)

all: $(LIBL)
	@echo "La bibliothèque est prête !"
	@echo $(BIG_SEPARATOR)


$(LIBL): $(OBJ)
	@echo $(SEPARATOR)
	@$(LD) $(LDFLAGS) $(LIBL) $^
	@echo "La bibliothèque \"$(LIB)\" a été compilée !"
	@echo $(SEPARATOR)

$(OBJ) : $(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CCFLAGS) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<
	@echo "$(notdir $@) a été compilé."

-include $(BUILD_DIR)/*.d

.PHONY: all clean

clean:
	@rm -f $(BUILD_DIR)/*
	@echo "La bibliothèque a été supprimée :("
