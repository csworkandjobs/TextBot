# TextBot
Simple text generator.  Source files, training files, and compiled files included.  Based on training data, forms simple relationships and probabilities between words.  A random first word is selected, then the program will output words based on previously identified probabilities until the number of words printed is equal to the number of words specified in the command line call.

Two versions, basic and improved.  
Basic requires direction to a file of training data and lacks some of the internal functionality of the improved version.
Improved automatically checks for a certain training file and has some additional internal functionality.

To use the basic compiled file, execute in the console: ./basic <NAME_OF_TRAINING_FILE> <NUMBER_OF_WORDS_TO_OUTPUT>

To use the improved compiled file, execute in the console: ./improved <NUMBER_OF_WORDS_TO_OUTPUT>

