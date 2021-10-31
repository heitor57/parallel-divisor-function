all:
	mkdir -p build &&	cd build &&	cmake .. &&	cmake --build .
clean:
	cmake --build ./build --target clean
	rm -rf build
