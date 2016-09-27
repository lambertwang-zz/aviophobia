CC = g++

# DELETE = rm
DELETE = del /s

INC = -I src\\include -I $(SDL_DIR)\\include -I $(GLEW_DIR)\\include

ENGINESRC = \
	src/source/audio/Music.cpp \
	src/source/audio/Sound.cpp \
	src/source/events/Event.cpp \
	src/source/events/EventCollision.cpp \
	src/source/events/EventJoystick.cpp \
	src/source/events/EventKeyboard.cpp \
	src/source/events/EventMouse.cpp \
	src/source/events/EventQuit.cpp \
	src/source/events/EventStep.cpp \
	src/source/managers/GameManager.cpp \
	src/source/managers/GraphicsManager.cpp \
	src/source/managers/InputManager.cpp \
	src/source/managers/LogManager.cpp \
	src/source/managers/Manager.cpp \
	src/source/managers/ResourceManager.cpp \
	src/source/managers/WorldManager.cpp \
	src/source/models/Object.cpp \
	src/source/models/ObjectNode.cpp \
	src/source/models/ObjectTree.cpp \
	src/source/models/TreeIterator.cpp \
	src/source/models/WorldState.cpp \
	src/source/sprite/Shape.cpp \
	src/source/sprite/Sprite.cpp \
	src/source/utility/Clock.cpp \
	src/source/utility/Input.cpp \
	src/source/utility/utility.cpp


ENGINEFILES = $(ENGINESRC:.cpp=.o)

ENGINE = aviophobia.a

build: lib Makefile
	@echo "done"

lib: $(ENGINEFILES)
	ar rvs $(ENGINE) $(ENGINEFILES)

.cpp.o: 
	$(CC) -c $(INC) $< -o $@ $(LINK)

clean:
	$(DELETE) $(ENGINE)
	$(DELETE) /s $(subst /,\\, $(ENGINEFILES)) #Windows only
	@echo "clean"