//To THE BIGGEST
public class source
{ 
public static int SIZE = 10;
public static int RANGE = 100;


	static void fill (int[] a)
	{
		java.util.Random r = new java.util.Random();
		for (int i = 0; i<a.length;i++)
			a[i]=r.nextInt()%RANGE;
	}
	
	static boolean check(int[] a)
	{
		
		for (int i=0;i<a.length-1;i++)
			if (a[i]>a[i+1])
				return false;
		return true;
	}
	
	static void swap(final int[] arr, final int pos1, final int pos2)
	{
	    final int temp = arr[pos1];
	    arr[pos1] = arr[pos2];
	    arr[pos2] = temp;
	}
	
	static void sort_easy (int[] a)
	{
		for (int i=a.length;i>0;i--)
		{
			int max = int min value;
			if (max < a[i-1])
		}
	}
	
	public static void main (String[] arg)
	{
		int[] massive = new int[SIZE];
		fill(massive);
		
		for (int i=0;i<massive.length;i++)
			System.out.println(massive[i]);
		System.out.println(check(massive));
	}
}
