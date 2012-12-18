rps-tournament
==============

Rock-Paper-Scissors Polyglot Tournament Framework

To host a tournament between several programs, given their source files, try the following:

    $ python tournament.py <list of source files>
    
For example:

    $ python samples/sample.cs samples/Main.java samples/beatlast.ml

    $ python fodder/*.c

For list of supported options, try:

    $ python tournament.py --help

Tournament Manager will compile the files (if needed) and then will host a tournament of rock-paper-scissors between them. Each pair of programs will compete exactly twice.

The framework was tested to work on Python 2.6.2, 2.7.1, 2.7.3 and Pypy 1.9. Python 3 is not yet supported (due to different implementation of subprocess library), nor is Shedskin (due to no implementation of threading library, amongst others).

Protocol
--------

At the beginning of a match, manager launches two programs from scratch, with no commandline parameters. Then, it reads one line from their standard outputs, which contains their human-friendly name.

Next, the manager sends to standard inputs of each of the the programs two lines, containing one integer each:

* an arbitrary number between 0 and 60000 (treat is as a seed for RNG)

* length of the game in rounds

Then, (number of rounds) times, the manager first reads one line containing a number from each program's standard output, and then sends each program it's opponents output.

Then, both programs are killed.

Number 0 means rock. Number 1 means paper. Number 2 means scissors.

If it's not clear, this is an example exchange between the manager and a compatible program. > means "data sent from manager to program", < means data sent from program to manager.

    < Sample Program 1.0
    > 31241
    > 5
    < 0
    > 1
    < 1
    > 2
    < 1
    > 2
    < 1
    > 2
    < 1
    > 2

Program loses the game prematurely, if it:

    * fails to respond in time

    * sends invalid move (something other than 0, 1, or 2)

    * exits or crashes before the end of the game

Hosting a tournament: tips
--------------------------

* Pick a decent machine.

* Configure the manager (file config.py) by providing paths to necessary interpreters, compilers, and launchers. The file contains reasonably decent defaults for some languages on Linux.

* Check if code send by participants satisfies the guidelines below.

Implementing programs: guidelines
---------------------------------

* Pick one of the supported languages. 
I **tested it to work** with C (.c), C++ (.cpp, .cxx), C# (.cs), Haskell (.hs, .lhs), Java (.java), O'Caml (.ml), Python (.py), and Scheme (.scm). See "samples" directory. 
Other languages that **should work** (in the worst case requiring a little configuration on the host's side; I haven't tested them yet) are: Ada (.adb), Awk (.awk), Bash (.sh), Brainfuck (.bf), Clojure (.clj), Common Lisp (.lisp), D (.d), F# (.fs), Fortran 90/95 (.f90/.f95), Go (.go), Javascript (.js), PHP (.php), Prolog (.pro), Perl (.pl), Ruby (.rb), Scala (.scala), Tcl (.tclsh).

* Always return the same name, and make it unique. The manager cannot handle two programs with the same names yet.

* Do not use any other sources of randomness apart from the integers from the standard input. The goal is to have reproducible results, at least on one machine. The recommended way is to initialize a deterministic pseudo-random number generator with the first integer from the input, or just be totally deterministic.

* Do not ignore opponent's moves: if the only parameter influencing your AI are the current turn number and initial random seed, you're doing it wrong.

* Do not use any other input/output, including shared memory, networking, environment, hardware devices, and so on. The only exception is standard error output, but it would be better if your program didn't print anything there, either.

* Do not use threads, do not spawn other processes, do not use GPU.

* Calculate your moves in less than one second.

* Always flush standard output after writing anything to it.

* You don't have to bother with counting how many moves are there left till the end of the game. The manager will kill your program just after the game.

* In case of Java, the entry point for your program should be main static method in class named Main, in default (null) package.

* In case of Scala, the entry point for your program should be main method in object named Main, in default (null) package.

Disclaimer
----------

Programs in 1999 and 1999-dummies directories have been copied and adapted from http://webdocs.cs.ualberta.ca/~darse/rsb-ts1.c

See http://webdocs.cs.ualberta.ca/~darse/rsbpc.html for more details.
