using System;
using System.Collections.Generic;

public class Rps {
	
	public const string PROGRAM_NAME = "Sample Random C#";

	private static List<int> oppHistory;
	private static List<int> myHistory;
	private static Random random;
	private static int gameLength;
	private const int ROCK = 0;
	private const int PAPER = 1;
	private const int SCISSORS = 2;

	private static int GetNextMove(){
		// do your fancy maths here
		return random.Next(3);
	}

	public static void Main(string[] args){
		Console.WriteLine(PROGRAM_NAME);
		random = new Random(Int32.Parse(Console.In.ReadLine()));
		gameLength = Int32.Parse(Console.In.ReadLine());
		oppHistory = new List<int>(gameLength);
		myHistory = new List<int>(gameLength);
		while(true){
			int move = GetNextMove();
			Console.WriteLine(move);
			oppHistory.Add(Int32.Parse(Console.In.ReadLine()));
			myHistory.Add(move);
		}
	}
}
