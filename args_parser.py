import sys

def parse_args(args):
	remaining = args[1:]
	seed1 = 1
	seed2 = 2
	match_length = 50
	while remaining:
		if remaining[0]=="--help":
			print ("""
rps-tournament - framework for hosting AI rock-paper-scissors tournaments

Home page and documentation: https://github.com/KarolS/rps-tournament

Usage:
	rps-tournament [options] <list of programs or program source files>

Options:
	--seed1 N   - random seed for player 1 in each match (default: 1)
	--seed2 N   - random seed for player 2 in each match (default: 2)
	-l N        - length of a match
	--help      - show this text
""")
			sys.exit(0)
		elif remaining[0]=="--seed1":
			seed1 = int(remaining[1])
			remaining = remaining[2:]
		elif remaining[0]=="--seed2":
			seed2 = int(remaining[1])
			remaining = remaining[2:]
		elif remaining[0]=="-l":
			match_length = int(remaining[1])
			remaining = remaining[2:]
		elif remaining[0]=="--":
			remaining = remaining[1:]
			break
		else:
			break
	return [seed1, seed2, match_length, remaining]