All:
	@echo "Compiling Hash Table..."
	@g++ -Wall -std=c++11 src/driver_ht.cpp -I include/ -o bin/hash
	@echo "Running Hash Table..."
	@./bin/hash
clean:
	@echo "Cleaning..."
	@rm bin/*
