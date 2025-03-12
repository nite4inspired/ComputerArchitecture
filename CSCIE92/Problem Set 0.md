 (15 Points) Write a program named word-count.c in C, that uses file
  I/O to read a text file containing printable characters (i.e., only
  ASCII characters whose decimal codes are between 32 and 126,
  inclusive) and the control characters horizontal tab (decimal 9),
  line feed (decimal 10), and possibly carriage return (decimal 13).
  An warning must be emitted if any other character is present in the
  file and the offending character skipped over.  The name of the file
  to be read is specified on the command line to the program as the
  only command line argument following the command name.  An warning
  must be emitted if any other arguments are present on the command
  line.  An error must be emitted if no file name is present.

  All code for word-count.c should be placed in a src/word-count
  directory.  The program will parse the input file into words and
  will use a data structure of your choice to keep track of the number
  of occurrences of each unique word that is found in the input file.
  Words will be delimited by white space which for our purposes is
  defined to be any mix of spaces (' '), horizontal tabs ('\t'), or
  newlines ('\n') -- including multiple occurrences of white space.
  You are welcome to include a carriage-return ('\r') as another white
  space character -- this facilitates code development on Windows
  computers.  Lines are delimited by a newline character (or
  additionally and optionally for development on Windows computers, by
  a carriage-return immediately followed by a linefeed).  No other
  characters should be treated specially (i.e., punctuation, hyphens,
  etc. should just be considered as non-white-space characters that
  should be treated as part of words).

  Do not convert the case of letters (e.g., your program should
  consider the words "case" and "Case" to be different words).  Upon
  reaching end-of-file, the program will output to stdout: (1) the
  number of lines in the input file (include blank lines in the count
  of the number of lines), (2) the total number of words in the input
  file (*not* the number of unique words), (3) a list of each unique
  word in the input file along with the number of times that word
  appears in the file.  The list of unique words need not be sorted in
  any particular order.

  Your solution must compile and execute correctly on our cscie92
  instance.  Compilation must not produce any warnings (or errors!).
  Remember to include a makefile to complete the build.  You *must*
  check return values from *all* functions with meaningful return
  values.

  Depending on your programming experience, you should choose an
  appropriate data structure in which the words and word counts are
  stored.  A solution that establishes a maximum word length would be
  eligible for full credit.  If you take this approach, the maximum
  word length should allow at least 1024 characters per word (this
  does *not* include a possible terminating NUL character).  However,
  (1) establishing a maximum number of unique words (for example, by
  using an array of fixed size for the unique words), (2) reading the
  entire text file into memory, and (3) making more than one pass
  through the input file are all *not* worthy of full credit.  Using a
  linked list -- perhaps sorted in alphabetical order -- would be
  worthy of full credit even though the performance of searching and
  inserting into a linked list may be inefficient.  Do not spend your
  time implementing a more efficient solution unless you are sure that
  you can complete this problem set on time.


### 1. Understand the Requirements

- **Command-line Arguments:**
    
    - Your program should accept exactly one file name as an argument.
    - Emit an error if no file is provided and a warning if more than one is provided.
- **File I/O & Character Checking:**
    
    - Open the file for reading.
    - Read the file character by character (or line by line) and check each character to ensure it falls within the allowed ASCII range (32–126) or is one of the allowed control characters (tab, newline, carriage return).
    - Emit a warning and skip any character that doesn’t meet these criteria.
- **Word Parsing:**
    
    - Consider words as sequences of characters separated by whitespace.
    - Decide how you want to handle multiple whitespace characters and line breaks.
- **Data Structure for Word Counting:**
    
    - You need to track each unique word along with how many times it appears.
    - Choose a data structure (like a linked list, a tree, or even a simple array with dynamic allocation) that lets you add new words and update counts efficiently.
- **Output:**
    
    - Count and print the total number of lines (including blank lines) and total number of words.
    - List each unique word along with its count (order is not important).
- **Error Handling & Return Value Checks:**
    
    - For every function that returns an error code or a pointer (like file operations or memory allocations), check and handle errors appropriately.
- **Makefile:**
    
    - Prepare a Makefile that compiles your code with no warnings or errors. Use compiler flags (e.g., `-Wall -Werror`) to enforce this.

### 2. Break Down the Problem

- **Main Function:**
    
    - Parse and validate command-line arguments.
    - Open the file and handle errors if the file cannot be opened.
- **File Processing Loop:**
    
    - Loop through the file, count lines (increment when you see a newline) and parse words using the defined whitespace characters.
    - As you build each word, validate each character and emit warnings if needed.
- **Word Storage and Counting:**
    
    - When a word is complete (you encounter whitespace), check your data structure:
        - If the word already exists, increment its counter.
        - If it's new, add it to the data structure.
- **Cleanup and Output:**
    
    - After processing the file, output the total line count, word count, and each unique word with its count.
    - Free any allocated memory to avoid leaks.

### 3. Choose and Set Up Your Development Environment

- Use an environment similar to Unix/Linux (WSL, Virtual Machine, or Docker) to mimic the course's cscie92 instance.
- Make sure you have a C compiler (like `gcc`) and `make` installed.
- Set up your repository structure with a `src/word-count` directory for your code and place your Makefile in the appropriate location.

### 4. Plan Incremental Development

- **Start Small:**
    - First, write code to handle the command-line arguments and file opening.
- **Process Input:**
    - Then, work on reading the file and simply counting lines and words without worrying about the detailed warnings.
- **Enhance Parsing:**
    - Add in character validation and warnings as you get more comfortable.
- **Implement the Data Structure:**
    - Choose your data structure and write functions to insert and update word counts.
- **Integrate Everything:**
    - Once each part works independently, combine them and test thoroughly.
- **Finalize:**
    - Create and refine your Makefile, ensuring no compilation warnings or errors, and add proper error checking for all functions.

