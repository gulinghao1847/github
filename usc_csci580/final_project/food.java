import javax.media.opengl.glu.GLU;
import javax.media.opengl.glu.GLUquadric;
import com.jogamp.opengl.util.*;
import javax.media.opengl.*;
import javax.media.opengl.glu.*;
import java.util.*;

public class food {

	private float radius;
	private GLU glu = new GLU();
	private float x,y,z; // position
	private int myobj, foodobj;
	private float fallspeed;
	private boolean foodready;
	public BoundingSphere bs;
	private int scaling=1;
	
	  
	public food (float xx, float yy)
	{
		
		Random rn = new Random();
		//food falls to bottom of the tank
		fallspeed=.02f;
		//food is placed in a rnadom tank location
		float myrn=rn.nextFloat();
		x=4f*rn.nextFloat()-2;
		y=4f*rn.nextFloat()-2;
		z=myrn*4f-2;
		
		radius=.1f;
		bs=new BoundingSphere(x,y,z, radius);
	}
	
	public void init(GL2 gl)
	{		//create food body
		    foodcreation(gl);
		    //turn into food obj and display
		    foodobj=gl.glGenLists(1);
		   
		    gl.glNewList( foodobj, GL2.GL_COMPILE );
		    construct_disp_list( gl ); 
		    gl.glEndList();
		   
	}
	
	private void foodcreation(GL2 gl)
	{	//create the food body object
		myobj=gl.glGenLists(1);
		gl.glNewList( myobj, GL2.GL_COMPILE);

	   	gl.glPushMatrix();
	    
	    GLUquadric myquad = glu.gluNewQuadric();
	    glu.gluQuadricDrawStyle( myquad, GLU.GLU_FILL );
	    glu.gluQuadricNormals( myquad, GLU.GLU_SMOOTH );

	    gl.glColor3f( 0f, 1f, 0f );
	    glu.gluSphere(myquad,.1f,20,20);
	    gl.glPopMatrix();
	 
	    
	    gl.glEndList();
	    glu.gluDeleteQuadric(myquad);
		
	}
	  private void construct_disp_list( GL2 gl)
	  { 
		gl.glTranslatef(x, y, z);
	      
	    gl.glPushMatrix();
	    gl.glCallList(myobj);
	    gl.glPopMatrix();
	  }
	
	  public void draw( GL2 gl )
	  {
	    gl.glPushMatrix();
	    gl.glCallList(foodobj);
	    gl.glPopMatrix();
	  }
	  
	  public void update( GL2 gl )
	  {	
		//let the food fall to the bottom of the tank
		y=y-fallspeed;
		
		if (y<-1.8f)
		{
			y=-1.8f;
			fallspeed=0;
			
		} 
		
		bs.setpos(x,y,z);
	    gl.glNewList( foodobj, GL2.GL_COMPILE );
	    construct_disp_list( gl ); 
	    gl.glEndList();
	  }
	  
	  public float getx()
	  {
		  return x;
	  }
	  
	  public float gety()
	  {
		  return y;
	  }
	  
	  public float getz()
	  {
		  return z;
	  }
	  

}
