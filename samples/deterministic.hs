module Main where
import System.IO

programName = "Sample Deterministic Haskell"

rock     = 0
paper    = 1
scissors = 2

getNextMove :: [Int] -> [Int] -> Int -> Int
getNextMove myHistory oppHistory gameLength = 
	case oppHistory of
		-- do your fancy maths here
		[]     -> scissors
		(x:xs) -> (x + 1) `mod` 3

runGame myHistory oppHistory gameLength = do
	let value = getNextMove myHistory oppHistory gameLength
	putStrLn $ show value
	hFlush stdout
	h <- readLn
	runGame (value:myHistory) (h:oppHistory) gameLength

main = do
	putStrLn programName
	hFlush stdout
	_ <- readLn :: IO Int
	gameLength <- readLn
	runGame [] [] gameLength
