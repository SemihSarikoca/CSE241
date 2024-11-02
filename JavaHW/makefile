 # Makefile for Java project

JAVAC = javac
JAVAC_FLAGS = -d

SRC_DIR = src
OUT_DIR = bin

SOURCES = $(wildcard $(SRC_DIR)/*.java)
CLASSES = $(SOURCES:$(SRC_DIR)/%.java=$(OUT_DIR)/%.class)

all: $(CLASSES) run

$(OUT_DIR)/%.class: $(SRC_DIR)/%.java
	$(JAVAC) $(JAVAC_FLAGS) $(OUT_DIR) $<

clean:
	rm -rf $(OUT_DIR)

run:
	java -cp $(OUT_DIR) $(SRC_DIR).Main

rebuild: clean all

.PHONY: all clean run rebuild

