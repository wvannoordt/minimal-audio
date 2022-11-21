main:
	g++ -std=c++20 -I./src main.cc -o out.x

run: main
	./out.x

clean:
	rm out.x
