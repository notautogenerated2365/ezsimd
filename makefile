run: main.exe
	.\main.exe

main.exe: main.cpp ezsimd3.hpp libezsimd3.hpp ezsimd3.cpp
	g++ ezsimd3.cpp -Ofast -fexpensive-optimizations -c -o ezsimd3.obj
	ar -rcs ezsimd3.lib ezsimd3.obj
	rm ezsimd3.obj
	g++ main.cpp -pipe -L./ -lezsimd3 -o main.exe