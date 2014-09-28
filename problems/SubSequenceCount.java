package main;

public class SubSequenceCount implements Problem{

	
	public void solve() {
		int[][] d = {	{0,1,2},
						{1,2,4},
						{3,2,1,0},
						{1,2,4,8,16},
						{1,3,5,5,5,5,64,4,23,2,3,4,5,4,3}};
		for(int i = 0; i< d.length; i++){
			System.out.print(SubSequenceCount.numberOfSubsequences(d[i]) +"\t: ");
			System.out.print("{");
			for(int j = 0; j < d[i].length-1; j++){
				System.out.print(d[i][j]+",");
				
			}
			System.out.println(d[i][d[i].length-1]+"}");
		}
	}
	
	public static int numberOfSubsequences(int[] d){
		int delta = 0;
		int subCount = 0;
		int count = 0;
		for(int i = 0; i < d.length; i++){
			delta = 0;
			subCount = 0;
			for(int j = i; j < d.length; j++){
				if (subCount == 1){
					delta = d[j] - d[j-1];
				}
				if (subCount > 0){
					if(d[j] - d[j-1] != delta){
						break;
					}
				}
				count++;
				subCount++;
			}
			
		}
		return count;
	}

}


