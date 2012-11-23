from do_tournament import do_tournament
from args_parser import parse_args
import sys

if __name__ == "__main__":
	do_tournament(*parse_args(sys.argv))
