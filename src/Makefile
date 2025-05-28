# COMMANDS
all: flo

clean:
	rm flo *.o

# GENERAL O FILES
flo: main.o lib.o BigInt.o ParseContext.o Value.o Null.o Bool.o Num.o Char.o Error.o
	g++ main.o lib.o BigInt.o ParseContext.o Value.o Null.o Bool.o Num.o Char.o Error.o -o flo

main.o: main.cpp main.hpp types/Num.hpp types/Value.hpp util/ParseContext.hpp lib.hpp
	g++ -std=c++20 -Wall -Wno-sign-compare -Wextra -Wpedantic -Werror main.cpp -c

lib.o: lib.cpp lib.hpp types/Error.hpp types/Null.hpp types/Num.hpp types/Value.hpp util/ParseContext.hpp
	g++ -std=c++20 -Wall -Wno-sign-compare -Wextra -Wpedantic -Werror lib.cpp -c

BigInt.o: util/BigInt.cpp util/BigInt.hpp
	g++ -std=c++20 -Wall -Wno-sign-compare -Wextra -Wpedantic -Werror util/BigInt.cpp -c

ParseContext.o: util/ParseContext.cpp util/ParseContext.hpp types/Value.hpp
	g++ -std=c++20 -Wall -Wno-sign-compare -Wextra -Wpedantic -Werror util/ParseContext.cpp -c

# TYPES O FILES
Value.o: types/Value.cpp types/Value.hpp
	g++ -std=c++20 -Wall -Wno-sign-compare -Wextra -Wpedantic -Werror types/Value.cpp -c

Null.o: types/Null.cpp types/Null.hpp types/Value.hpp
	g++ -std=c++20 -Wall -Wno-sign-compare -Wextra -Wpedantic -Werror types/Null.cpp -c

Bool.o: types/Bool.cpp types/Bool.hpp types/Value.hpp
	g++ -std=c++20 -Wall -Wno-sign-compare -Wextra -Wpedantic -Werror types/Bool.cpp -c

Num.o: types/Num.cpp types/Num.hpp types/Value.hpp util/BigInt.hpp
	g++ -std=c++20 -Wall -Wno-sign-compare -Wextra -Wpedantic -Werror types/Num.cpp -c

Char.o: types/Char.cpp types/Char.hpp types/Value.hpp
	g++ -std=c++20 -Wall -Wno-sign-compare -Wextra -Wpedantic -Werror types/Char.cpp -c

Error.o: types/Error.cpp types/Error.hpp types/Value.hpp
	g++ -std=c++20 -Wall -Wno-sign-compare -Wextra -Wpedantic -Werror types/Error.cpp -c
