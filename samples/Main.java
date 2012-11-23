import java.util.*;
import java.io.*;

public class Main{

	public static final String PROGRAM_NAME = "Sample Random Java";

	private static List<Integer> oppHistory;
	private static List<Integer> myHistory;
	private static Random random;
	private static int gameLength;
	private static final int ROCK = 0;
	private static final int PAPER = 1;
	private static final int SCISSORS = 2;

	private static int getNextMove(){
		// do your fancy maths here
		return random.nextInt(3);
	}
	
	public static void main(String... args) throws IOException{
		int seed = 42;
		System.out.println(PROGRAM_NAME);
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		seed = Integer.parseInt(br.readLine());
		random = new Random(seed);
		gameLength = Integer.parseInt(br.readLine());
		oppHistory = new ArrayList<Integer>(gameLength);
		myHistory = new ArrayList<Integer>(gameLength);
		while(true){
			int move = getNextMove();
			System.out.println(move);
			myHistory.add(move);
			oppHistory.add(Integer.parseInt(br.readLine()));
		}
	}
}

