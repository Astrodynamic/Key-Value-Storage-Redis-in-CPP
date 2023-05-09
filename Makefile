all: build

build: install

rebuild: clean install

install:
	cmake -S . -B ./build
	cmake --build ./build

unistall:
	find ./ -name "build" -type d -exec rm -rf {} +

hash_table.a:
	cmake -S ./table/ -B ./table/build
	cmake --build ./table/build

self_balancing_binary_search_tree.a:
	cmake -S ./binary_tree/ -B ./binary_tree/build
	cmake --build ./binary_tree/build

b_plus_tree.a:
	cmake -S ./tree_plus/ -B ./tree_plus/build
	cmake --build ./tree_plus/build

clean: unistall
	rm -rf ./lib/*

tests:
	cmake -S ./test/ -B ./test/build
	cmake --build ./test/build
	./test/build/TEST

cppcheck: install
	@cd build/; make cppcheck

clang-format: install
	@cd build/; make clang-format

lcov: test
	cd ./test/build; make coverage;
	open ./test/build/coverage-report/index.html 

.PHONY: all build rebuild unistall clean cppcheck clang-format tests lcov
