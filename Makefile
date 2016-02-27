#OCR Makefile

CXX=g++
PKG_CONFIG_PATH=/usr/share/pkgconfig
PKG_CONFIG_CFLAGS=$(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH); pkg-config gtkmm-2.4 --cflags)
PKG_CONFIG_LIBS=$(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH); pkg-config gtkmm-2.4 --libs)
CFLAGS=-std=c++0x -g -Iinc $(PKG_CONFIG_CFLAGS)
LIBS=$(PKG_CONFIG_LIBS)
OBJS=main.o gui.o
TESTS_GUI=
TESTS_IO=
TESTS_PREPROC=
TESTS_POSTPROC=

#Build everything
.PHONY: all
all: build bin/ocr test

#Load dependency information
-include $(addprefix build/, $OBJS:.o=.d)


#Make build, test, and bin directories
.PHONY: build
build:
	@echo "Building objects..."
	mkdir -p build
	mkdir -p build/test
	mkdir -p bin

#Build object files
build/%.o: src/%.cpp | build
	$(CXX) -c -o $@ $< $(CFLAGS) -MMD

#Build output binary
bin/ocr: build/main.o $(addprefix build/, $(OBJS))
	@echo "Building OCR binary..."
	$(CXX) -o $@ $^ $(LIBS)


#Test individual objects
.PHONY: test
test: | test-gui test-io test-preprocessing test-postprocessing

.PHONY: test-gui
test-gui: $(addprefix build/test/, $(TESTS)) | build
	@echo "Running tests..."
	for t in $^; do ./$$t; done

.PHONY: test-io
test-io: $(addprefix build/test/, $(TESTS)) | build
	@echo "Running tests..."
	for t in $^; do ./$$t; done

.PHONY: test-preprocessing
test-preprocessing: $(addprefix build/test/, $(TESTS)) | build
	@echo "Running tests..."
	for t in $^; do ./$$t; done

.PHONY: test-postprocessing
test-postprocessing: $(addprefix build/test/, $(TESTS)) | build
	@echo "Running tests..."
	for t in $^; do ./$$t; done

build/test/%: test/%.cpp $(addprefix build/, $(OBJS)) | build
	$(CXX) -o $@ $< $(addprefix build/, $(OBJS)) $(CFLAGS)


#Create release archives
.PHONY: release
release: | all
	tar cvzf OCR_Alpha.tar.gz --exclude=CVS README COPYRIGHT INSTALL bin/ doc/
	tar cvzf OCR_Alpha_src.tar.gz --exclude=CVS README COPYRIGHT INSTALL Makefile bin/ doc/ inc/ src/ test/


#Clean up old build and release files
.PHONY: clean
clean:
	@echo "Cleaning up build files..."
	rm -rf build/ bin/ *.tar.gz