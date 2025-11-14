all:
	@mkdir -p Build
	@cd Build && cmake .. -G "MinGW Makefiles"
	@cd Build && cmake --build .

clean:
	@rm -rf Build Dist

run:
	@Dist/Aurora-Qt.exe