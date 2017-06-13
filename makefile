All:
	@echo "Compiling Hash Table..."
	@g++ -Wall -std=c++11 driver_ht.cpp -o bin/hash
	@echo "Running Hash Table..."
	@./bin/hash
clean:
	@echo "Cleaning..."
	@rm bin/*
