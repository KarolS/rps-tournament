

(define (run-game seed game-length)
	(define (get-move my-history opp-history)
		;;; do your fancy maths here
		(if (null? opp-history)
			(remainder seed 3)
			(remainder (+ 1 (car opp-history)) 3) ))
	(define (main-loop my-history opp-history)
		(let
			((my-move (get-move my-history opp-history)))
			(display my-move)
			(newline)
			(let ((their-move (read)))
				(main-loop (cons my-move my-history) (cons their-move opp-history)) )))
	(main-loop '() '()) )

(define (main args)
	(define program-name "Sample Beat Last Scheme")
	(display program-name)
	(newline)
	(let ((seed (read)))
		(let ((game-length (read))) 
			(run-game seed game-length) )))