//************************************************************************
//  Teapot Class.
//     This class draws a spinning teapot.
//************************************************************************
//


import javax.media.opengl.*;
import com.jogamp.opengl.util.*;
import java.util.*;
import com.jogamp.opengl.util.gl2.GLUT;//for new version of gl

public class Teapot
{
  private int teapot_object;
  private float scale;
  private float angle;

  public Teapot( float scale_)
  {
    scale = scale_;
    angle = 0;
  }

  public void init( GL2 gl )
  {

    teapot_object = gl.glGenLists(1);
    gl.glNewList( teapot_object, GL2.GL_COMPILE );

    // due to a bug in glutSolidTeapot, triangle vertices are in CW order 
    gl.glFrontFace( GL.GL_CW ); 
  
    // create the teapot triangles 
    GLUT glut = new GLUT();
    glut.glutSolidTeapot( scale );
  
    // return to regular CCW order 
    gl.glFrontFace( GL.GL_CCW );
    gl.glEndList();

  }

  public void update( GL2 gl )
  {
    angle += 5;
  }

  public void draw( GL2 gl )
  {
    gl.glPushMatrix();
    gl.glPushAttrib( GL2.GL_CURRENT_BIT );
    gl.glRotatef( angle, 1.0f, 0f, 0.0f );
    gl.glColor3f( 0.85f, 0.55f, 0.20f); // Orange
    gl.glCallList( teapot_object );
    gl.glPopAttrib();
    gl.glPopMatrix();
  }
}
