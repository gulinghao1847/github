import com.jogamp.opengl.util.*;
import javax.media.opengl.*;
import javax.media.opengl.glu.*;

import java.util.*;
import java.io.IOException;
//Creates a new fish object (small red fish). These fish are capable of bumping into each other and choosing a new direction,
//They will also move towards food when the food is dropped into the tank
public class bfish {
	
	public float x, y,z;
	private GLU glu = new GLU();
	private int fish_obj, body, tail, colorchange;
	  
	public float dir_x, dir_y, dir_z;
	private float speed;
	  
	private float angle;
	private float rot_dir;
	private float rot_speed;
	private int nextmove;
	private int prevcollide=0;
	private boolean cancollide =true;
	
	private float reallign;
	public BoundingSphere myBS;
	public boolean alive;
	
	public float radius = 0.15f;
	public int id;
	
	
	
	  public bfish(float xx, float yy, float zz, int newId)
	  {	//position
	    x=xx;
	    y=yy;
	    z=zz;
	    
	    
	    fish_obj=body=tail=0;
	    Random rn = new Random();
	    
	    dir_x=1;
	    dir_y=0;
	    dir_z=0;
	    speed=.01f;
	    nextmove=1;
	    
	    
	    alive=true;
	    angle=0;
	    rot_speed=5;
	    rot_dir=1;
	    
	    id = newId;
	  }
	  
	  public void init( GL2 gl )
	  {
	  
	    //Creates the bounding sphere which collisions are based off of
	    myBS = new BoundingSphere(x,y,z, .15f);
	    
	    create_body(gl);
	    //create_tail(gl);
	    
	    fish_obj = gl.glGenLists(1);

	    gl.glNewList( fish_obj, GL2.GL_COMPILE );
	    construct_disp_list( gl ); 
	    gl.glEndList();
	  }
	  
	  
	  
	  
	  public void update( GL2 gl )
	  {	
		if (alive==true)
		  {	//only collide with other fish if this flag is true
			//if (prevcollide==0)
			//	cancollide=true;
			//else
			//	prevcollide--;
		
			if (nextmove==1)
			{	//if first move choose random movement
				choosemovement();
				nextmove--;
			}
		
		//Always be aware of the predator!!!
			//float xx= Vivarium.mybfish.x;
			//float yy= Vivarium.mybfish.y;
			//float zz= Vivarium.mybfish.z;
			//Get the distance of preadator
			//float distance = (float)Math.sqrt( Math.pow( (double)this.x-xx, 2) +  Math.pow( (double)this.y-yy, 2) +  Math.pow( (double)this.z-zz, 2) );
			
			//if the red fish is sufficiently far from a wall (to avoid getting stuck)
			//if (Math.abs(x)<1.8 && Math.abs(y)<1.8 && Math.abs(z)<1.8)
			//{	//if the predator is close then evade
				//if (distance<1f)
					//evade();
				//Otherwise look for food
			//	 if (Vivarium.hasfood==true)
				//{
					//findfood();  
				//}
			//}
		
	  	
			translate();
			//flap_tail();
		
			gl.glNewList( fish_obj, GL2.GL_COMPILE );
			construct_disp_list( gl ); 
			gl.glEndList();
		  	}
	  }
	  

	  
	  public void draw( GL2 gl )
	  {
	    gl.glPushMatrix();
	    gl.glCallList( fish_obj );
	    gl.glPopMatrix();
	  }
	
	  
	  private void construct_disp_list( GL2 gl)
	  { 	float myangle;
		  	gl.glTranslatef(x, y, z);
		  
		    gl.glPushMatrix();
		    //allignfish();
		    //gl.glRotatef(180+reallign, 0, 1, 0);
		    gl.glCallList(body);
		    gl.glPopMatrix();
		    
		  //  gl.glPushMatrix();
		   /// allignfish();
		   // gl.glRotatef(180+reallign, 0, 1, 0);
		    //gl.glRotatef(angle, 0, 1, 0);
		   // gl.glCallList(tail);
		   
		   // gl.glPopMatrix();
		
	    
	  }
	  private void translate()
	  {
		  //move the fish
		  if (x>2)
			  dir_x=-1;
		  
		  if (x<-2)
			  dir_x=1;
		  
		  if (y>2)
			  dir_y=-1;
		  
		  if (y<-2)
			  dir_y=1;
		  
		  if (z>2)
			  dir_z=-1;
		  
		  if (z<-2)
			  dir_z=1;
			 
		
		  x+= dir_x*speed;
		  y+= dir_y*speed;
		  z+= dir_z*speed;
		  
		  myBS.setpos(x, y, z);
	  }
	  private void allignfish()
	  {
		  //allign the fish in the direction he is facing
		  
		  double mag = Math.sqrt(Math.pow(dir_x, 2)+Math.pow(dir_z,2));
	  
		  if(dir_x == 0)	 
			  reallign = 0; 
		  //tan =oppositie/adjacent
		  else if(dir_x>0)
			  reallign = (float)Math.toDegrees(Math.atan( (dir_z/dir_x)/mag ));
		  else
		  {
			  reallign = 180+(float)Math.toDegrees(Math.atan( (dir_z/dir_x)/mag) );
		  }
	  
		  reallign*= -1;
	 
	  }
	  private void flap_tail()
	  {
		//quickly swish the backtail back and forth
		 if (angle>10)
			 rot_dir=-1;
		 if (angle<-10)
			 rot_dir=1;
		 

		 angle+= rot_dir*rot_speed;
	  }
	  

	  
	  //handles collision with other red fish
	  public void collide(Vec vf)
	  {	//only coollide if both fish are alive
		  //if (cancollide && alive)
	//  {
		  //if (prevcollide>2)
		  //{	//if you have just collided then pick a random direction and move that way without changing direction
			//  choosemovement();
			  //cancollide=false;
			 // prevcollide=6;
		  //}
		 
		 // else if (prevcollide==0)
		  //{		
			
			  dir_x=vf.x;
			  dir_y=vf.y;
			  dir_z=vf.z;
		 // }
		  //prevcollide+=2;
		  
	  //}
		  
	  }
	  
	  
	  public void choosemovement()
	  {
		  

		
		  //Choose a new random movement
		  Random rn = new Random();
		  //random direction between -1 and 1
		  dir_x=rn.nextFloat() * 2 + -1 ;
		  dir_y=rn.nextFloat() * 2 + -1;
		  dir_z=rn.nextFloat() * 2 +-1;
  
		  
	  }
	  
	  private void create_body( GL2 gl)
	  {	//generate a sphere and scale it to make it look like a fish body
	    body = gl.glGenLists(1);
	    
	    gl.glNewList( body, GL2.GL_COMPILE);
	    gl.glPushMatrix();
	   
	 
	   
	    
	    GLUquadric myquad = glu.gluNewQuadric();
	    glu.gluQuadricDrawStyle( myquad, GLU.GLU_FILL );
	    glu.gluQuadricNormals( myquad, GLU.GLU_SMOOTH );

	    gl.glColor3f( 0f, 1f, 0f );
	    glu.gluSphere(myquad,.15f,20,20);
	   
	    
	    gl.glPopMatrix();
	    gl.glEndList();
	    
	  }
	  
	  


	  private void create_tail( GL2 gl)
	  {	//generate a sphere for the tail and scale it to make it look realistic
	    tail = gl.glGenLists(1);
	    
	    gl.glNewList( tail, GL2.GL_COMPILE);
	    gl.glPushMatrix();
	   
	    gl.glTranslatef(.2f, 0, 0);
	    gl.glRotatef(90, 0, 1, 0);
	    
	    GLUquadric myquad = glu.gluNewQuadric();
	    glu.gluQuadricDrawStyle( myquad, GLU.GLU_FILL );
	    glu.gluQuadricNormals( myquad, GLU.GLU_SMOOTH );

	    gl.glColor3f( 1f, 0f, 0f );
	    gl.glScalef(.2f,1f,0.4f);
	    
	    
	    glu.gluSphere(myquad,.15f,20,20);
	    
	    
	    gl.glPopMatrix();
	    gl.glEndList();
	    
	  }
	  
	  
}

