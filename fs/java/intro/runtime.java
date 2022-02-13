
public class runtime
{
    public static void main(String[] args)
    {
           printNum(0);
           
           /*get the current runtime associated with this process
        Runtime run = Runtime.getRuntime();
        ArrayList<int[]> list = new ArrayList<int[]>();
          int nums[] = new int[100000];
        Arrays.fill(nums, 5);
       while (true)
        {
    		list.add(nums);
    		// print the current free memory for this runtime
    		System.out.println("" + run.freeMemory());
    	}*/
        
    }
    static void printNum(int num)
    {
	if (num == 100)
	{
		return;
	}
        System.out.println(num);
        printNum(num+1);
    }
}
