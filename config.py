#!/usr/bin/env python

ITSELF              = ["$INPUT"]
MKDIR               = ["/bin/mkdir", "-p", "$INPUT"]
EXECUTABLE_EXT      = None

AWK_INTERPRETER     = ["/usr/bin/awk", "-f", "$INPUT"]
BASH_INTERPRETER    = ["/bin/bash", "$INPUT"]
BF_INTERPRETER      = ["/usr/bin/bf", "$INPUT"]
C_COMPILER          = ["/usr/bin/gcc", "-std=c99", "-o", "$OUTPUT", "$INPUT"]
CLOJURE_INTERPRETER = ["/usr/bin/java", "-jar", "/opt/clojure-1.4.jar", "$INPUT"]
CPP_COMPILER        = ["/usr/bin/g++", "-std=c++0x", "-o", "$OUTPUT", "$INPUT"]
CSHARP_COMPILER     = ["/usr/bin/gmcs", "-out:$OUTPUT", "$INPUT"]
CSHARP_LAUNCHER     = ["/usr/bin/mono", "$INPUT"]
D_COMPILER          = ["/usr/bin/dmd", "-o", "$OUTPUT", "$INPUT"]
EXE_LAUNCHER        = ["/usr/bin/cognac", "--backslash-none", "$INPUT"]
FSHARP_COMPILER     = ["/usr/bin/fsharpc", "-out:$OUTPUT", "$INPUT"]
FSHARP_LAUNCHER     = ["/usr/bin/mono", "$INPUT"]
GO_LAUNCHER         = ["/opt/go/bin/go", "run", "$INPUT"]
HASKELL_COMPILER    = ["/usr/bin/ghc", "-outputdir", "/tmp", "-o", "$OUTPUT", "$INPUT"]
JAVA_COMPILER       = ["/usr/bin/javac", "-d", "$OUTPUT", "$INPUT"]
JAVA_LAUNCHER       = ["/usr/bin/java", "-cp", "$INPUT", "Main"]
JS_INTERPRETER      = ["/usr/bin/rhino", "-s", "$INPUT"]
PHP_INTERPRETER     = ["/usr/bin/php", "$INPUT"]
PERL_INTERPRETER    = ["/usr/bin/perl", "$INPUT"]
PROLOG_INTERPRETER  = ["/usr/bin/swipl", "-s", "$INPUT"]
PYTHON_INTERPRETER  = ["/usr/bin/python", "$INPUT"]
RUBY_INTERPRETER    = ["/usr/bin/irb", "$INPUT"]
SCALA_COMPILER      = ["/opt/scala-2.9.2/bin/scalac", "-d", "$OUTPUT", "$INPUT"]
SCALA_LAUNCHER      = ["/opt/scala-2.9.2/bin/scala", "-cp", "$INPUT", "Main"]
TCL_INTERPRETER     = ["/usr/bin/tcl", "$INPUT"]