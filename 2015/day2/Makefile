default: clean run
	echo "[MAKE] done !"

run: compile
	echo "[MAKE] running the program:"
	./out/output input.txt

compile:
	echo "[MAKE] compiling the program:"
	mkdir -p out/
	gcc main.c -o out/output

clean:
	echo "[MAKE] cleaning the output:"
	rm out/*
