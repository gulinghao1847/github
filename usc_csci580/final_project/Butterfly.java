//************************************************************************
//  Buttefly Class.
//     This class animates a buttefly.
//************************************************************************
//


import com.jogamp.opengl.util.*;
import javax.media.opengl.*;
import javax.media.opengl.glu.*;
import java.util.*;
import java.io.IOException;


public class Butterfly 
{
  private int butterfly_obj, left_wing, right_wing, body;
  private int texture;
  private float x,y,z; // position
  private GLU glu = new GLU();
  
  private float dir_x, dir_y, dir_z;
  private float speed;
  
  private float angle;
  private float rot_dir;
  private float rot_speed;
  private int nextmove;
  public BoundingSphere myBS;
  private int prevcollide=0;
  private boolean cancollide =true;
  

  
  public Butterfly(float xx, float yy, float zz )
  {
    x=xx;
    y=yy;
    z=zz;
    nextmove=1;
    
    butterfly_obj = left_wing = right_wing= body= 0;
    dir_x=1;
    dir_y=0;
    dir_z=0;
    speed=.05f;
    
    angle=0;
    rot_speed=2;
    rot_dir=1;
    
  }

  public void init( GL2 gl )
  {
    try {
        texture = load_texture( gl, "Butterfly1.bmp" );
    } catch (IOException e) {
        System.out.println("Unable to load textures,Bailing!");
        throw new RuntimeException(e);
    } 

    create_left_wing( gl, texture );
    create_right_wing( gl, texture );
    create_body(gl);
    
     myBS = new BoundingSphere(x,y,z, .25f);

    butterfly_obj = gl.glGenLists(1);

    gl.glNewList( butterfly_obj, GL2.GL_COMPILE );
    construct_disp_list( gl ); 
    gl.glEndList();
  }
  public void findfood()
  {
	  
	  
	  
	  float xx= Vivarium.myfood.getx();
	  float yy= Vivarium.myfood.gety();
	  float zz = Vivarium.myfood.getz();
	  
	  float distance = (float)Math.sqrt( Math.pow( (double)this.x-xx, 2) +  Math.pow( (double)this.y-yy, 2) +  Math.pow( (double)this.z-zz, 2) );
	  
	  if (distance<2f)
	  {
		  dir_x= xx-this.x;
		  dir_y= yy-this.y;
		  dir_z= zz-this.z;
		  
	  }
	  
	  
  }
  
  public void choosemovement()
  {
	  

	
	  //Choose a new random movement
	  Random rn = new Random();
	  dir_x=rn.nextFloat();
	  dir_y=rn.nextFloat();
	  dir_z=rn.nextFloat();

	 
	  
	  
	  
  }
  public void collide()
  {	
	  if (cancollide)
  {
	  if (prevcollide>2)
	  {	
		  choosemovement();
		  cancollide=false;
		  prevcollide=6;
	  }
	 
	  else if (prevcollide==0)
	  {
		  Random rn = new Random();
		  dir_x=rn.nextFloat();
		  dir_y=-dir_y;
		  dir_z=-dir_z;
	  }
	  prevcollide+=2;
	  
  }
	  
  }
  
  public void update( GL2 gl )
  {	

	if (prevcollide==0)
		  cancollide=true;
	else
		prevcollide--;
	
	if (nextmove==1)
	{
		choosemovement();
		nextmove--;
	}
	  
	if (Vivarium.hasfood==true)
	{
		findfood();  
		  
	}
  	
	translate();
	flap_wings();
	
    gl.glNewList( butterfly_obj, GL2.GL_COMPILE );
    construct_disp_list( gl ); 
    gl.glEndList();
  }

  public void draw( GL2 gl )
  {
    gl.glPushMatrix();
    gl.glCallList( butterfly_obj );
    gl.glPopMatrix();
  }

  /////////////////// /////////////////  Private Functions 
  private void construct_disp_list( GL2 gl)
  { 
	gl.glTranslatef(x, y, z);
    gl.glBindTexture(GL.GL_TEXTURE_2D, texture);
    
    gl.glPushMatrix();
    if (dir_x>0 && dir_y>0)
    gl.glRotatef(angle, 1, 1, 0);
    else if (dir_x<0 && dir_y>0)
    {	
    	gl.glRotatef(180, 0, 1, 0);
    	gl.glRotatef(angle, 1, 1, 0);
    	
    }
    else if (dir_x<0 && dir_y<0)
    {
    	gl.glRotatef(180, 0, 0, 1);
    	gl.glRotatef(angle, 1, 1, 0);
    }
    else
    {
    	gl.glRotatef(180, 1, 0, 0);
    	gl.glRotatef(angle, 1, 1, 0);
    	
    }

    gl.glCallList( left_wing );
    
    gl.glPopMatrix();
    
    gl.glPushMatrix();
    if (dir_x>0 && dir_y>0)
    gl.glRotatef(-angle, 1, 1, 0);
    else if (dir_x<0 && dir_y>0)
    {	
    	gl.glRotatef(-180, 0, 1, 0);
    	gl.glRotatef(-angle, 1, 1, 0);
    	
    }
    else if (dir_x<0 && dir_y<0)
    {
    	gl.glRotatef(-180, 0, 0, 1);
    	gl.glRotatef(-angle, 1, 1, 0);
    }
    else
    {
    	gl.glRotatef(-180, 1, 0, 0);
    	gl.glRotatef(-angle, 1, 1, 0);
    	
    }
    	
    gl.glCallList( right_wing );
    gl.glPopMatrix();
    
    
    gl.glPushMatrix();
    gl.glCallList(body);
    gl.glPopMatrix();
  }

  private void flap_wings()
  {	
	
	 if (angle>50)
		 rot_dir=-1;
	 if (angle<-50)
		 rot_dir=1;
	 

	 angle+= rot_dir*rot_speed;
  }
  
  private void translate()
  {
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

  private int load_texture( GL gl, String filename) 
    throws IOException 
  {
    TextureReader.Texture texture =TextureReader.readTexture( filename );
    int[] texture_id = new int[1];
    gl.glGenTextures(1, texture_id, 0);

		    
    //Create Linear Filtered Texture
    gl.glBindTexture(GL.GL_TEXTURE_2D, texture_id[0]);
    //gl.glTexParameteri(GL.GL_TEXTURE_2D, 
    //    GL.GL_TEXTURE_MAG_FILTER, GL.GL_LINEAR);
	gl.glTexParameteri(GL.GL_TEXTURE_2D, 
	GL.GL_TEXTURE_MIN_FILTER, GL.GL_LINEAR);

	gl.glTexImage2D(GL.GL_TEXTURE_2D,
	   0,
	   3,
	   texture.getWidth(),
	   texture.getHeight(),
	   0,
	   GL.GL_RGB,
	   GL.GL_UNSIGNED_BYTE,
	   texture.getPixels());


       return texture_id[0];
  }

  private void create_left_wing( GL2 gl, int texture)
  {
    left_wing = gl.glGenLists(1);
    
    gl.glNewList( left_wing, GL2.GL_COMPILE);
    gl.glPushMatrix();
   
    gl.glEnable( GL.GL_TEXTURE_2D);
    gl.glPolygonMode( GL.GL_FRONT, GL2.GL_FILL);
    gl.glPolygonMode( GL.GL_BACK, GL2.GL_FILL);
    gl.glScalef(0.5f,0.5f,0.5f);
    gl.glTranslatef(-0.5f, -0.5f, 0);
    //gl.glRotatef(90,1,0,0);
    //gl.glRotatef(-45, 0, 0, 1);
    gl.glBegin( GL.GL_TRIANGLES );	  
      gl.glTexCoord2f(1.0f,1.0f); 
      gl.glVertex3f( 1f, 1f, 0f); //1 1 0
      gl.glTexCoord2f(0.0f,1.0f); 
      gl.glVertex3f( 0f, 1f, 0f); //0 1 0
      gl.glTexCoord2f(0.0f,0.0f); 
      gl.glVertex3f( 0.0f, 0.0f, 0.0f);
    gl.glEnd();
    gl.glDisable( GL.GL_TEXTURE_2D );

    gl.glPopMatrix();
    gl.glEndList();
  }

  private void create_right_wing( GL2 gl, int texture )
  {
    right_wing = gl.glGenLists(1);

    gl.glNewList( right_wing, GL2.GL_COMPILE);
    gl.glPushMatrix();
    gl.glEnable( GL.GL_TEXTURE_2D );
    gl.glPolygonMode( GL.GL_FRONT, GL2.GL_FILL);
    gl.glPolygonMode( GL.GL_BACK, GL2.GL_FILL);
    gl.glScalef(0.5f,0.5f,0.5f);
    gl.glTranslatef(-0.5f, -0.5f, 0);
    //gl.glRotatef(90,1,0,0);
    //gl.glRotatef(-45, 0, 0, 1);
    gl.glBegin( GL.GL_TRIANGLES );
      gl.glTexCoord2f(1.0f,1.0f); 
      gl.glVertex3f( 1.0f, 1.0f, 0.0f);
      gl.glTexCoord2f(0.0f,0.0f); 
      gl.glVertex3f( 0.0f, 0.0f, 0.0f);
      gl.glTexCoord2f(1.0f,0.0f); 
      gl.glVertex3f( 1.0f, 0.0f, 0.0f);
    gl.glEnd();
    gl.glDisable( GL.GL_TEXTURE_2D );
 
    gl.glPopMatrix();
    gl.glEndList();
  }
  
  
  private void create_body( GL2 gl)
  {
    body = gl.glGenLists(1);
    gl.glNewList( body, GL2.GL_COMPILE);

    
    gl.glPushMatrix();
    
    GLUquadric qobj0 = glu.gluNewQuadric();
    glu.gluQuadricDrawStyle( qobj0, GLU.GLU_FILL );
    glu.gluQuadricNormals( qobj0, GLU.GLU_SMOOTH );

    

   
    gl.glColor4f( .2f, .2f, 0f, 1f );
    glu.gluSphere(qobj0,.25f,20,20);
    
    gl.glPopMatrix();
    gl.glEndList();
    glu.gluDeleteQuadric(qobj0);
    }

}
