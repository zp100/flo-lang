# Based off of: https://makefiletutorial.com/

# CONSTANTS
TARGET :=		flo
SRC_DIR :=		./src/
BUILD_DIR :=	./build/
COMP :=			g++
CPP_FLAGS :=	-std=c++20 -Wall -Wextra -Wpedantic -Werror

# VARIABLES
SRC_FILES :=	$(shell find ${SRC_DIR} -name '*.cpp')
OBJ_FILES :=	${SRC_FILES:%=${BUILD_DIR}/%.o}
DEP_FILES :=	${OBJ_FILES:.o=.d}
INC_DIRS :=		$(shell find ${SRC_DIR} -type d)
INC_FLAGS :=	$(addprefix -I,${INC_DIRS})

# TARGETS
all: ${BUILD_DIR}/${TARGET}

clean:
	rm -r ${BUILD_DIR}

${BUILD_DIR}/${TARGET}: ${OBJ_FILES}
	${COMP} $^ -o $@

$(BUILD_DIR)/%.cpp.o: %.cpp %.hpp
	mkdir -p $(dir $@)
	${COMP} ${CPP_FLAGS} -c $< -o $@
