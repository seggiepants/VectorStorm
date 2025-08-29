CC = em++
SOURCES = main.cpp 
SOURCES += Globals.cpp 
SOURCES += Scene.cpp
SOURCES += SceneGame.cpp 
SOURCES += SceneTitle.cpp
SOURCES += VectorFont.cpp
SOURCES += Level.cpp
SOURCES += Models.cpp
SOURCES += Enemy.cpp
SOURCES += Tanker.cpp
HEADERS = Globals.h 
HEADERS += Scene.h 
HEADERS += SceneGame.h
HEADERS += SceneTitle.h 
HEADERS += Utility.h
HEADERS += VectorFont.h
HEADERS += Level.h
HEADERS += Models.h
HEADERS += Enemy.h
HEADERS += Tanker.h

EXE = VectorStorm.html

EMFLAGS = -std=c++17 -O2 -s ALLOW_MEMORY_GROWTH=1 -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2 -s USE_LIBPNG=1 -s USE_SDL=2 -s USE_SDL_MIXER=2 --preload-file res

$(EXE): $(SOURCES) $(HEADERS)
	$(CC) $(EMFLAGS) $(SOURCES) -o $(EXE)
	mv *.wasm wasm
	mv *.js wasm
	mv *.html wasm
	mv *.data wasm

test:
	echo "Hello World"
clean:
	rm -f $(EXE) *.o *.js *.wasm *.wasm.pre