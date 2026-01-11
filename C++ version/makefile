CC = g++

CFLAGS = -std=c++17 -Wall \
	-I./src \
	-I./libs/bbop/include \
	-I./libs/glfw/include \
	-I./libs/glew/include \
	-I./libs/glm \
	$(shell pkg-config --cflags freetype2)

LIBS = \
	-L./libs/bbop -lbbop \
	-L./libs/glfw -lglfw3 \
	-L./libs/glew -lGLEW \
	-lGL \
	$(shell pkg-config --libs freetype2)


SRCS = $(wildcard src/*.cpp src/*/*.cpp) main.cpp
OBJDIR = build
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)
TARGET = game
LIBDIR = libs

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)
	@echo "Build terminé : $(TARGET)"

# Compile .cpp -> .o
$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<
	@echo "Compilé : $<"

# --- RUN ---
run: $(TARGET)
	./$(TARGET)

# --- CLEAN ---
clean:
	rm -rf $(OBJDIR) $(TARGET)
	@echo "Nettoyage terminé"

.PHONY: all clean run