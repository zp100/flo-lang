# Based off of: https://makefiletutorial.com/

# CONSTANTS
TARGET :=		flo
SRC_DIR :=		./src/
BUILD_DIR :=	./build/
BUILD_GUARD :=	mkdir -p ${BUILD_DIR}
COMP :=			g++
CPP_FLAGS :=	-std=c++20 -Wall -Wno-sign-compare -Wextra -Wpedantic -Werror

# VARIABLES
SRC_FILES :=	$(shell find ${SRC_DIR} -name '*.cpp')
OBJ_FILES :=	${SRC_FILES:%=${BUILD_DIR}/%.o}
DEP_FILES :=	${OBJ_FILES:.o=.d}
INC_DIRS :=		$(shell find ${SRC_DIR} -type d)
INC_FLAGS :=	$(addprefix -I,${INC_DIRS})

# COMMANDS
all: ${BUILD_DIR}/${TARGET}
	mkdir -p ${BUILD_DIR}/

clean:
	rm ${BUILD_DIR}/*

${BUILD_DIR}/${TARGET}: ${BUILD_DIR}/main.o ${BUILD_DIR}/lib.o ${BUILD_DIR}/BigInt.o ${BUILD_DIR}/ParseContext.o ${BUILD_DIR}/Value.o ${BUILD_DIR}/Null.o ${BUILD_DIR}/Bool.o ${BUILD_DIR}/Num.o ${BUILD_DIR}/Char.o ${BUILD_DIR}/Error.o
	${COMP} $^ -o $@

# GENERAL O FILES
${BUILD_DIR}/main.o: ${SRC_DIR}/main.cpp ${SRC_DIR}/main.hpp ${SRC_DIR}/types/Num.hpp ${SRC_DIR}/types/Value.hpp ${SRC_DIR}/util/ParseContext.hpp ${SRC_DIR}/lib.hpp
	${BUILD_GUARD}
	${COMP} ${CPP_FLAGS} $< -c -o $@

${BUILD_DIR}/lib.o: ${SRC_DIR}/lib.cpp ${SRC_DIR}/lib.hpp ${SRC_DIR}/types/Error.hpp ${SRC_DIR}/types/Null.hpp ${SRC_DIR}/types/Num.hpp ${SRC_DIR}/types/Value.hpp ${SRC_DIR}/util/ParseContext.hpp
	${BUILD_GUARD}
	${COMP} ${CPP_FLAGS} $< -c -o $@

${BUILD_DIR}/BigInt.o: ${SRC_DIR}/util/BigInt.cpp ${SRC_DIR}/util/BigInt.hpp
	${BUILD_GUARD}
	${COMP} ${CPP_FLAGS} $< -c -o $@

${BUILD_DIR}/ParseContext.o: ${SRC_DIR}/util/ParseContext.cpp ${SRC_DIR}/util/ParseContext.hpp ${SRC_DIR}/types/Value.hpp
	${BUILD_GUARD}
	${COMP} ${CPP_FLAGS} $< -c -o $@

# TYPES O FILES
${BUILD_DIR}/Value.o: ${SRC_DIR}/types/Value.cpp ${SRC_DIR}/types/Value.hpp
	${BUILD_GUARD}
	${COMP} ${CPP_FLAGS} $< -c -o $@

${BUILD_DIR}/Null.o: ${SRC_DIR}/types/Null.cpp ${SRC_DIR}/types/Null.hpp ${SRC_DIR}/types/Value.hpp
	${BUILD_GUARD}
	${COMP} ${CPP_FLAGS} $< -c -o $@

${BUILD_DIR}/Bool.o: ${SRC_DIR}/types/Bool.cpp ${SRC_DIR}/types/Bool.hpp ${SRC_DIR}/types/Value.hpp
	${BUILD_GUARD}
	${COMP} ${CPP_FLAGS} $< -c -o $@

${BUILD_DIR}/Num.o: ${SRC_DIR}/types/Num.cpp ${SRC_DIR}/types/Num.hpp ${SRC_DIR}/types/Value.hpp ${SRC_DIR}/util/BigInt.hpp
	${BUILD_GUARD}
	${COMP} ${CPP_FLAGS} $< -c -o $@

${BUILD_DIR}/Char.o: ${SRC_DIR}/types/Char.cpp ${SRC_DIR}/types/Char.hpp ${SRC_DIR}/types/Value.hpp
	${BUILD_GUARD}
	${COMP} ${CPP_FLAGS} $< -c -o $@

${BUILD_DIR}/Error.o: ${SRC_DIR}/types/Error.cpp ${SRC_DIR}/types/Error.hpp ${SRC_DIR}/types/Value.hpp
	${BUILD_GUARD}
	${COMP} ${CPP_FLAGS} $< -c -o $@
