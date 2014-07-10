import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;


public class ArrayOfInterval {
	  public ArrayList<interval> ballListX = new ArrayList<interval>();
	  public ArrayList<interval> ballListY = new ArrayList<interval>();
	  public ArrayList<interval> ballListZ = new ArrayList<interval>();
	  
	  /*
	  public float[] startPointsX;
	  public float[] startPointsY;
	  public float[] startPointsZ;
	  */
	  
	  public void sortIntervalArray(){
		  insertionSort(ballListX);
		  //insertionSort(ballListY);
		  //insertionSort(ballListZ);
	  }

	  public ArrayList<int[]> sweepAndPrune(ArrayList<Fish> creatureList){
		  sortIntervalArray();
		  return checkOverlap(creatureList);
	  }

	  
	public ArrayList<int[]> checkOverlap(ArrayList<Fish> creatureList)
	{	// O(n^2) in worst case
		ArrayList<int[]> overlapList = new ArrayList<>();
		for(int i=0;i<ballListX.size();i++)
		{
			for(int j=i+1;j<ballListX.size();j++)
			{
				if(ballListX.get(i).endPoint>ballListX.get(j).startPoint)
				{
					int id1 = ballListX.get(i).id;
					int id2 = ballListX.get(j).id;
					float d = Math.abs(ballListX.get(i).startPoint-ballListX.get(i).endPoint);
					Fish fish1 = creatureList.get(id1);
					Fish fish2 = creatureList.get(id2);

					
					if(isOverlap(fish1.y, fish2.y, fish1.radius) || isOverlap(fish2.y, fish1.y, fish1.radius))
					{
						if(isOverlap(fish1.z, fish2.z, fish1.radius) || isOverlap(fish2.z, fish1.z, fish1.radius))
						{
							int[] a = new int[2];
							a[0]=id1;
							a[1]=id2;
							overlapList.add(a);
						}
					}
				}
				else
					break;
			}
		}
		return overlapList;
	}

	public void insertionSort(ArrayList<interval> list)
	{
		int i, j;
		float midPoint, startPoint, endPoint;
		int id;
		for (i = 1; i < list.size(); i++)
		{
    	  	midPoint = (list.get(i).startPoint + list.get(i).endPoint)/2;
    	  	startPoint = list.get(i).startPoint;
    	  	endPoint = list.get(i).endPoint;
    	  	id =  list.get(i).id;
			j = i;
			while (j > 0 && (list.get(j - 1).startPoint + list.get(j - 1).endPoint) / 2 > midPoint)
			{
				list.get(j).startPoint = list.get(j-1).startPoint;
				list.get(j).endPoint = list.get(j-1).endPoint;
				list.get(j).id = list.get(j-1).id;
				j--;
			}
			list.get(j).startPoint = startPoint;
			list.get(j).endPoint = endPoint;
			list.get(j).id = id;
	    }
	}
	
	public boolean isOverlap(float a, float b,float radius){
		if(a + radius > b - radius && Math.abs(a - b)  <= 2 * radius) return true;
		else return false;
	}
}
