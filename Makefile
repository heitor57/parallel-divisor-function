all:
	mkdir -p build &&	cd build &&	cmake -DCMAKE_BUILD_TYPE=Debug .. &&	cmake --build .
clean:
	cmake --build ./build --target clean
	rm -rf build
