#!/usr/bin/env python

from config import *
import subprocess
from subprocess import PIPE
import uuid
import sys



def interpreted(interpreter):
	def f(program_file):
		return format(interpreter, program_file)
	return f
def compiled(compiler, launcher = ITSELF, ext = None):
	def f(program_file):
		exe = temp_file(ext)
		subprocess.Popen(format(compiler, program_file, exe), bufsize=0, stderr = sys.stderr).wait()
		return format(launcher, exe)
	return f
def compiled_dir(compiler, launcher = ITSELF, ext = None):
	def f(program_file):
		exe = temp_file(ext)
		subprocess.Popen(format(MKDIR, exe)).wait()
		subprocess.Popen(format(compiler, program_file, exe), bufsize=0, stderr = sys.stderr).wait()
		return format(launcher, exe)
	return f
def itself(program_file):
	return [program_file]

def format(line, input, output = ""):
	result = [
		x.replace("$OUTPUT",output).replace("$INPUT",input)
		for x in line]
	#print (result)
	return result

def temp_file(ext=None):
	if ext is None:
		ext = ""
	else:
		ext = "."+ext
	return "/tmp/"+str(uuid.uuid4())+ext

COMPILED_CACHE = dict()

def run_program_file(program_file):
	global COMPILED_CACHE
	try:
		command = COMPILED_CACHE[program_file]
	except:
		f = itself
		if program_file.endswith(".c"):
			f = compiled(C_COMPILER, ext = EXECUTABLE_EXT)
		elif program_file.endswith(".d"):
			f = compiled(D_COMPILER, ext = EXECUTABLE_EXT)
		elif program_file.endswith(".cpp") or program_file.endswith(".cxx"):
			f = compiled(CPP_COMPILER, ext = EXECUTABLE_EXT)
		elif program_file.endswith(".adb"):
			f = compiled(ADA_COMPILER, ext = EXECUTABLE_EXT)
		elif program_file.endswith(".f95") or program_file.endswith(".f95"):
			f = compiled(FORTRAN_COMPILER, ext = EXECUTABLE_EXT)
		elif program_file.endswith(".hs") or program_file.endswith(".lhs"):
			f = compiled(HASKELL_COMPILER, ext = EXECUTABLE_EXT)
		elif program_file.endswith(".ml"):
			f = compiled(OCAML_COMPILER, launcher=OCAML_LAUNCHER, ext = EXECUTABLE_EXT)
		elif program_file.endswith(".java"):
			f = compiled_dir(JAVA_COMPILER, launcher = JAVA_LAUNCHER)
		elif program_file.endswith(".scala"):
			f = compiled_dir(SCALA_COMPILER, launcher = JAVA_LAUNCHER)
		elif program_file.endswith(".cs"):
			f = compiled(CSHARP_COMPILER, launcher = CSHARP_LAUNCHER, ext = "exe")
		elif program_file.endswith(".fs"):
			f = compiled(FSHARP_COMPILER, launcher = FSHARP_LAUNCHER, ext = "exe")
		elif program_file.endswith(".js"):
			f = interpretedd(JS_INTERPRETER)
		elif program_file.endswith(".php"):
			f = interpreted(PHP_INTERPRETER)
		elif program_file.endswith(".awk"):
			f = interpreted(AWK_INTERPRETER)
		elif program_file.endswith(".pl"):
			f = interpreted(PERL_INTERPRETER)
		elif program_file.endswith(".bash"):
			f = interpreted(BASH_INTERPRETER)
		elif program_file.endswith(".bf"):
			f = interpreted(BF_INTERPRETER)
		elif program_file.endswith(".clj"):
			f = interpreted(CLOJURE_INTERPRETER)
		elif program_file.endswith(".lisp"):
			f = interpreted(CLISP_INTERPRETER)
		elif program_file.endswith(".scm"):
			f = interpreted(SCHEME_INTERPRETER)
		elif program_file.endswith(".go"):
			f = interpreted(GO_LAUNCHER)
		elif program_file.endswith(".tclsh"):
			f = interpreted(TCL_INTERPRETER)
		elif program_file.endswith(".pro"):
			f = interpreted(PROLOG_INTERPRETER)
		elif program_file.endswith(".exe"):
			f = interpreted(EXE_LAUNCHER)
		elif program_file.endswith(".py"):
			f = interpreted(PYTHON_INTERPRETER)
		elif program_file.endswith(".rb"):
			f = interpreted(RUBY_INTERPRETER)
		command = f(program_file)
		COMPILED_CACHE[program_file] = command
	return subprocess.Popen(command, bufsize = 1, 
		stdin = subprocess.PIPE, stdout = subprocess.PIPE, stderr = sys.stderr)