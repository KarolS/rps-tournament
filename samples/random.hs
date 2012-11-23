module Main where
import System.Random
import System.IO

type State = ()


programName = "Sample Random Haskell"

rock     = 0
paper    = 1
scissors = 2

initialState = ()

getNextMove :: RandomGen g => State -> [Int] -> [Int] -> g -> Int -> (Int, State, g)
getNextMove state myHistory oppHistory random gameLength = 
	let 
		-- do your fancy maths here
		newState = state
		(value, newRandom) = randomR (0,2) random
	in
		(value, newState, newRandom)

runGame state myHistory oppHistory random gameLength = do
	let (value, newState, newRandom) = getNextMove state myHistory oppHistory random gameLength
	putStrLn $ show value
	hFlush stdout
	h <- readLn
	runGame newState (value:myHistory) (h:oppHistory) newRandom gameLength

main = do
	putStrLn programName
	hFlush stdout
	seed <- readLn
	gameLength <- readLn
	runGame initialState [] [] (mkStdGen seed) gameLength
