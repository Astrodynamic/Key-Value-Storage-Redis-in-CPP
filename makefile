all: run

build:
	cmake -S ./ -B ./build
	cmake --build ./build

run: build
	./build/Transaction

hash_table.a:
	cmake -S ./table/ -B ./table/build
	cmake --build ./table/build

self_balancing_binary_search_tree.a:
	cmake -S ./binary_tree/ -B ./binary_tree/build
	cmake --build ./binary_tree/build

b_plus_tree.a:
	cmake -S ./tree_plus/ -B ./tree_plus/build
	cmake --build ./tree_plus/build

test:
	cmake -S ./tests/ -B ./tests/build
	cmake --build ./tests/build
	./tests/build/TEST

lcov: test
	cd ./tests/build; make coverage;
	open ./tests/build/coverage-report/index.html 

style: build
	cd ./build;\
	make style

cppcheck: build
	cd ./build;\
	make cppcheck

clean:
	find ./ -name "build" -type d -exec rm -rf {} +
	rm -rf ./lib/*
