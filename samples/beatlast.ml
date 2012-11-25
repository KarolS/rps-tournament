let program_name = "Sample Beat Last O'Caml" ;;

let paper = 2;;
let scissors = 1;;
let rock = 0;;

let get_move my_history = function
(* do your fancy maths here *)
| [] -> paper
| last_move::opp_history -> (last_move+1) mod 3;;

let rec main_loop my_history opp_history = 
	let my_move = get_move my_history opp_history in
	print_endline (string_of_int my_move);
	let their_move = read_int() in
	main_loop (my_move::my_history) (their_move::opp_history) ;;

let run_game = 
	print_endline program_name;
	let seed = read_int() in
	let game_length = read_int() in
	main_loop [] [] ;;

run_game;;