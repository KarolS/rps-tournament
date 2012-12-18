#!/usr/bin/env python

import sys
import threading
import math
from launching import run_program_file

class Player():
	def __init__(self, path):
		self.process = run_program_file(path)
		self.path = path
		self.read_from = self.process.stdout
		self.write_to = self.process.stdin
	def get_name(self):
		TIMEOUT = 1
		result = [self.path]
		def do_stuff():
			try:
				result[0] = self.read_from.readline().strip("\n")
			except: pass
		th = threading.Thread(target=do_stuff)
		th.start()
		th.join(TIMEOUT)
		return result[0]
	def poll(self):
		TIMEOUT = 1
		result = [-1]
		def do_stuff():
			try:
				result[0] = int(str(self.read_from.readline(2)))
				if result[0] not in [0,1,2]:
					print("  Unexpected output: "+str(result[0]))
					result[0] =  -1
			except Exception as e:
				print(str(e))
				result[0] = -1
		th = threading.Thread(target=do_stuff)
		th.start()
		th.join(TIMEOUT)
		return result[0]
	def notify(self, opponents_move):
		try:
			self.write_to.write(str(opponents_move)+"\n")
			self.write_to.flush()
			return True
		except:
			return False
	def kill(self):
		try:
			self.process.stdout.close()
			self.process.stdin.close()
		except Exception as e:
			print (str( e ))
		try:
			self.process.terminate()
		except: pass

ROCK = 0
PAPER = 1
SCISSORS = 2
NAMES = ["rock", "paper", "scissors"]

def game(path1, path2, length, seed1, seed2):
	name1 = path1
	name2 = path2
	result = 0
	detailed_result = length
	p1 = None
	p2 = None
	try:
		p1 = Player(path1)
		name1 = p1.get_name()
	except Exception as e:
		print ("Failed to run player 1: "+path1+", reason: "+str(e))
		result = 2 # P2 wins provided it doesn't crash as well
	try:
		p2 = Player(path2)
		name2 = p2.get_name()
	except Exception as e:
		print ("Failed to run player 2: "+path2+", reason: "+str(e))
		result = (2-result)/2 # 2->0, because both failed; 0->1, because now P1 wins
	try:
		if result == 0 and p1 is not None:
			print ("Match between "+name1+" and "+name2)
			p1.notify(seed1)
			p2.notify(seed2)
			(result, detailed_result) = game0(name1, name2, p1,p2, length)
	except Exception as e: 
		print ("  Match failed for unknown reasons: "+str(e))
	try:
		p1.kill()
	except: pass
	try:
		p2.kill()
	except: pass
	if result == 0:
		detailed_result = 0
	return ((name1,name2),(result, detailed_result))
def game0(name1, name2, p1, p2, length):
	score_for_2 = 0
	p1.notify(length)
	p2.notify(length)
	for i in range(length):
		m1 = p1.poll()
		m2 = p2.poll()
		if m1 < 0: 
			if m2 < 0:
				print ("  Both players failed to respond")
				return (0, 0)
			else:
				print ("  Player "+name1+" failed to respond")
				return (2, length)
		if m2 < 0:
			print ("  Player "+name2+" failed to respond")
			return (1, length)
		score_for_2 += (m2-m1+4)%3-1
		p1.notify(m2)
		p2.notify(m1)
		#print "round "+str(i+1)+" P1:"+NAMES[m1]+", P2:"+NAMES[m2]+", score="+str(score_for_2)
	if score_for_2 < 0:
		print ("  Player "+name1+" won by "+str(-score_for_2)+" points")
		return (1, -score_for_2)
	elif score_for_2 > 0:
		print ("  Player "+name2+" won by "+str(score_for_2)+" points")
		return (2, score_for_2)
	else:
		print ("  The game was drawn")
		return (0, 0)

def print_crosstable(sorted_names, crosstable, total_score, still_a_tie = 0):
	print ("")
	if still_a_tie < 0:
		still_a_tie = 0
	def shorten(n):
		if len(n)<=3 : return (n+"   ")[0:3]
		cleaned = n.replace("(","").replace("[","")
		split = list(filter(lambda x:x!="", cleaned.split(" ")))
		if len(split) >= 3: 
			return "".join(x[0] for x in split[0:3])
		return cleaned[0:3]
	shortened_names = [shorten(n) for n in sorted_names]
	name_length = 1+max([len(x) for x in sorted_names])
	padded_names = [("%"+str(name_length)+"s")%(x) for x in sorted_names]
	for x in range(3):
		print (
			" " * 7
			+ " " * name_length
			+ " " 
			+ "".join(n[x] for n in shortened_names)
			+ " Score"*(x/2))
	def nice_result(name1, name2):
		if name1==name2:
			return "\\"
		value = crosstable[name1,name2]
		if value > still_a_tie:
			return "+"
		elif value < -still_a_tie:
			return "-"
		else:
			return " "
	for i in range(len(sorted_names)):
		name1 = sorted_names[i]
		print (
			"%5d"%(i+1)
			+ ". "
			+ padded_names[i]
			+ " "
			+ "".join([nice_result(name1, name2) for name2 in sorted_names]) 
			+ " "
			+ "%5d"%(total_score[name1]))

def do_tournament(seed1, seed2, match_length, paths):
	no_paths = len(paths)
	if no_paths == 0:
		print("No programs specified!")
		sys.exit(1)
	player_names = set()
	crosstable_b = dict()
	total_score_b = dict()
	crosstable_s = dict()
	total_score_s = dict()
	def initialize_name(name):
		player_names.add(name)
		try:
			total_score_b[name]
		except:	
			total_score_b[name]=0
		try:
			total_score_s[name]
		except:	
			total_score_s[name]=0
	def initialize_names(name1,name2):
		initialize_name(name1)
		try: 
			crosstable_b[name1,name2]
		except:
			crosstable_b[name1,name2]=0
		try: 
			crosstable_s[name1,name2]
		except:
			crosstable_s[name1,name2]=0


	for path1 in paths:
		for path2 in paths:
			if path1 != path2:
				((name1, name2),(result, detailed_result)) = game(path1,path2,match_length, seed1, seed2)
				initialize_names(name1,name2)
				initialize_names(name2,name1)
				if result == 1:
					crosstable_b[name1,name2] += 1
					crosstable_b[name2,name1] -= 1
					total_score_b[name1] += 1
					total_score_b[name2] -= 1
					crosstable_s[name1,name2] += detailed_result
					crosstable_s[name2,name1] -= detailed_result
					total_score_s[name1] += detailed_result
					total_score_s[name2] -= detailed_result
				if result == 2:
					crosstable_b[name1,name2] -= 1
					crosstable_b[name2,name1] += 1
					total_score_b[name1] -= 1
					total_score_b[name2] += 1
					crosstable_s[name1,name2] -= detailed_result
					crosstable_s[name2,name1] += detailed_result
					total_score_s[name1] -= detailed_result
					total_score_s[name2] += detailed_result
	totals_b = [(total_score_b[n],n) for n in player_names]
	totals_s = [(total_score_s[n],n) for n in player_names]
	sorted_names_b = [t[1] for t in reversed(sorted(totals_b))]
	sorted_names_s = [t[1] for t in reversed(sorted(totals_s))]
	print_crosstable(sorted_names_b, crosstable_b, total_score_b, 0)
	print_crosstable(sorted_names_s, crosstable_s, total_score_s, math.sqrt(match_length))

