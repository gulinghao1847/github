//************************************************************************

//   Generate Triangle Mesh Approximation to a Cylinder using Opengl
//************************************************************************
// Comments :
//   For a cylinder whose base is at (tx,ty,tz), with given radius and
//   height, this function generates an OpenGL triangle mesh approximation to
//   the cylinder (with normals).
//
// History :
//   30 Jan 2008. Translated from c code by Tai-Peng Tian (tiantp@gmail.com).
//   Original C code by Stan Sclaroff


import javax.media.opengl.*;
import com.jogamp.opengl.util.*;
import java.util.*;

public class SolidCylinder
{
  private int DL; // display list
  private double z_top, z_bottom; // z coords of the cylinder top and btm
  private ArrayList<Coord> circle2D; 
  private ArrayList<Coord> circle2D_normal;

  public SolidCylinder( double tx, double ty, double tz, double radius, 
            double height, int n_subdivision_steps )
  {

    circle2D = new ArrayList<Coord> ();
    circle2D_normal = new ArrayList<Coord> ();

     // Cylinder is centered at (0,0,0) and aligned along Z-axis
    z_top = tz + height;
    z_bottom = tz;

    // Approximation of the 2D circle with polyline 
    double d_theta = 2*3.1415926/n_subdivision_steps;
    double theta = 0; 
    for (int i = 0; i < n_subdivision_steps; ++i)
    {
      Coord normal = new Coord( radius*Math.cos(theta), 
                           radius*Math.sin(theta), 0);
      circle2D_normal.add( normal ); 
      circle2D.add( new Coord ( normal.x + tx, normal.y + ty, 1));
      theta += d_theta;
    }

 }

  public void init( GL2 gl )
  {
    // Create the display list
    DL = gl.glGenLists(1);
    Coord n, p; // temp variables to store retrieved obj from ArrayList

    gl.glNewList( DL, GL2.GL_COMPILE );

      // Quad strip for cylinder sides
      gl.glBegin( GL.GL_TRIANGLE_STRIP);
      for (int i = 0; i < circle2D.size(); i++)
      {
        n = circle2D_normal.get(i);
        p = circle2D.get(i);

        gl.glNormal3d( n.x, n.y, 0 );
        gl.glVertex3d( p.x, p.y, z_bottom );
        gl.glNormal3d( n.x, n.y, 0 );
        gl.glVertex3d( p.x, p.y, z_top );
      }
   
      n = circle2D_normal.get(0);
      p = circle2D.get(0);
      gl.glNormal3d( n.x, n.y, 0 );
      gl.glVertex3d( p.x, p.y, z_bottom );
      gl.glNormal3d( n.x, n.y, 0 );
      gl.glVertex3d( p.x, p.y, z_top );
      
      gl.glEnd(); // gl.glBegin(GL_TRIANGLE_STRIP)

      // Top end cap polygon
      gl.glBegin( GL2.GL_POLYGON );
      for (int i = 0; i< circle2D.size(); i++ )
      {
        p = circle2D.get(i);
        gl.glVertex3d( p.x, p.y, z_top );
        gl.glNormal3d( 0,   0,   1     );
      }
      p = circle2D.get(0);
      gl.glVertex3d( p.x, p.y, z_top );
      gl.glNormal3d( 0,   0,   1     );

      gl.glEnd(); // gl.glBegin(GL.GL_POLYGON);

      // Bottom end cap polygon
      gl.glBegin( GL2.GL_POLYGON );
      for (int i = 0; i< circle2D.size(); i++ )
      {
        p = circle2D.get(i);
        gl.glVertex3d( p.x, p.y, z_bottom );
        gl.glNormal3d( 0,   0,   1     );
      }
      p = circle2D.get(0);
      gl.glVertex3d( p.x, p.y, z_bottom );
      gl.glNormal3d( 0,   0,   1     );

      gl.glEnd(); // gl.glBegin(GL.GL_POLYGON);

    gl.glEndList();
  }


  public void draw( GL2 gl )
  {
    gl.glCallList( DL );
  }
}

