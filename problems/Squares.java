package main;

public class Squares implements Problem{
	public void solve(){
		int n = 6;
		String square = Squares.toString(Squares.draw(4*n+1));
		System.out.println("Result for "+(4*n+1)+": \n" + square);
	}
	public static String[] draw(int n){
		String[] square = new String[n];
		
		//initialize empty square
		StringBuffer empty =  new StringBuffer(n);
		StringBuffer full =  new StringBuffer(n);
		for(int i = 0; i < n; i++){
			empty.append(' ');
			full.append('#');
		}
		for(int i = 0; i < n; i++){
			if(i == 0 || i == n-1){
				square[i] = full.toString();				
			}else{
				square[i] = empty.toString();	
			}
		}
		rdraw(square,n);
		return square;
	}
	
	private static void rdraw(String[] square,int squareSize){
		
		if(squareSize <= 0)return;
		
		int offset = (square.length - squareSize) >> 1;

		String line = square[0].substring(0, squareSize);
		for(int i = 0; i < squareSize; i++){
			if(i == 0 || i == squareSize-1){
				square[offset+i] = 	square[offset+i].substring(0, offset) + 
									line +
									square[offset+i].substring(offset+squareSize);
			}else{
				square[offset+i] = 	square[offset+i].substring(0, offset) + 
						"#" +
						square[offset+i].substring(offset+1,offset+squareSize-1)+
						"#" +
						square[offset+i].substring(offset+squareSize);
			}
		}
		//System.out.println("rdwraw " + squareSize + ":");
		//System.out.println(Squares.toString(square));
		rdraw(square, squareSize-4);
	}
	
	public static String toString(String[] square){
		StringBuffer str = new StringBuffer(square.length*(square.length+1));
		for(int i = 0; i < square.length; i++){
			str.append(square[i]);
			str.append("\n");
		}
		return str.toString();
		
	}
}
