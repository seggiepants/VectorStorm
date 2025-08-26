CC = em++
SOURCES = main.cpp 
SOURCES += Globals.cpp 
SOURCES += Scene.cpp 
SOURCES += SceneTitle.cpp
SOURCES += VectorFont.cpp
SOURCES += Models.cpp
HEADERS = Globals.h 
HEADERS += Scene.h 
HEADERS += SceneTitle.h 
HEADERS += Utility.h
HEADERS += VectorFont.h
HEADERS += Models.h
EXE = VectorStorm.html

EMFLAGS = -std=c++17 -O2 -s ALLOW_MEMORY_GROWTH=1 -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2 -s USE_LIBPNG=1 -s USE_SDL=2

$(EXE): $(SOURCES) $(HEADERS)
	$(CC) $(EMFLAGS) $(SOURCES) -o $(EXE)
	mv *.wasm wasm
	mv *.js wasm
	mv *.html wasm

test:
	echo "Hello World"
clean:
	rm -f $(EXE) *.o *.js *.wasm *.wasm.pre