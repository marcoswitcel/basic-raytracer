a.out:
	g++ -pthread main.cpp

run: a.out
	@echo ""
	./a.out
	@echo "\n"
	@rm ./a.out

clear:
	rm ./a.out
