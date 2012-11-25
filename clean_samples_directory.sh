#!/bin/bash

DIR="`dirname "$0"`"

cd "$DIR/samples" || exit 1

rm -vf *.cmo *.cmi *.o *.class *.out *.exe *.ali *.hi
