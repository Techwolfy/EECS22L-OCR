//Test-PostProcessing.cpp
//Tests for postprocessing functions

#include <stdio.h>
#include <assert.h>
#include <string>
#include "postproc.h"

int main(int argc, char *argv[]) {
	std::string input = "Hel1o W0rld\n";
	std::string valid = "Hello World\n";

	PostProc spellcheck(input);
	std::string output = spellcheck.execute();
	
	assert(output == valid);
	
	printf("Post-processing test passed!\n");
	return 0;
}
