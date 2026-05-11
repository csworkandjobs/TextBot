# TextBot
--Project Overview--
Simple text generator built in C++, meant to be used from the command line.  Source files, training files, and compiled files included.  Based on training data, forms simple relationships and probabilities between words.  A random first word is selected, then the program will output words based on previously identified probabilities until the number of words printed is equal to the number of words specified in the command line call.


--VERSIONS--
Two versions, basic and improved, as described below.

Basic is more rigid and requires more inputs.  It takes in an input file name (located in the same folder as it) to use as training data and a number of words to output.  It then will create a basic map of word relationships, then select a random word to be the first word, it then prints the first word and selects a next word based off the relationships identified when mapping the training files.  That next word will then be printed and a next word will be selected based on its relationships mapped in the training data.  This will continue until the specified number of output words has been reached.

Improved structures its command line arguments a bit different, taking in a number of words to output first, then taking in any number of training files, including none.  It assumes that a file called "classicNovelsTrainingData.custom-input.txt" (which contains about 10 MB of data, from books in the public domain to even constitutions) exists in the same folder and uses it as training data, meaning it does not strictly need to be told what files to use.  It can take additional files, though, which it will add to its training data.  The "moreTrainingStuff.custom-input.txt" exists to demonstrate this.  It also includes some additional in-line comments about what functions do and what steps would help with improving the program.


--EXECUTION--
The programs can be executed as follows.  Both versions will refuse to run if provided insufficient arguments (though providing input files to the improved version of the program is optional, not required).

To use the compiled file of the basic text generator, execute in the console: ./basic <NAME_OF_TRAINING_FILE> <NUMBER_OF_WORDS_TO_OUTPUT>

To use the compiled file of the improved text generator, execute in the console: ./improved <NUMBER_OF_WORDS_TO_OUTPUT> <INPUT_FILE_NAMES>


--EXTRA INFORMATION--
Developed around October of 2025 as a basic C++ project.  Developed in CLion and tested using an Ubuntu console in the Windows Subsystem for Linux (WSL).
