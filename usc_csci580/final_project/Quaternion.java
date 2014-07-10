//****************************************************************************
// Quaternion Class      
//****************************************************************************
// Description: 
//   Support routines for quaternions.
//
// History : 
//   16 Jan 2008 Created by Tai-Peng Tian (tiantp@gmail.com) based on code by
//   Stan Sclaroff (CS480 '06 Assignment 2, quaternion.c)
//


public class Quaternion
{
   public float s;
   public float[] v;

   public static final float EPSILON = 0.0001f;
 
   public Quaternion(float _s, float v0, float v1, float v2)
   {
	 v = new float[3];
     set( _s, v0, v1, v2 );
   }
  
   public Quaternion()
   {
	 v = new float[3];
     set( 1f, 0f, 0f, 0f );
   }

   public void reset()
   {
     set( 1f, 0f, 0f, 0f);
   }

   public void set( float _s, float v0, float v1, float v2 )
   {
     s = _s;
     v[0] = v0;
     v[1] = v1;
     v[2] = v2;
   }

   /* Multiply two quaternions */
   /* Use Eq. A-79 on p. 806 of Hearn and Baker */
   public Quaternion multiply( Quaternion Q)
   {
	 Quaternion outQ = new Quaternion();

     // s = s1*s2 - v1.v2
     outQ.s = s*Q.s-v[0]*Q.v[0]-v[1]*Q.v[1]-v[2]*Q.v[2];

     // v = s1 v2 + s2 v1 + v1 x v2
     outQ.v[0] = v[1]*Q.v[2] - v[2]*Q.v[1]; //Cross product
     outQ.v[1] = v[2]*Q.v[0] - v[0]*Q.v[2];
     outQ.v[2] = v[0]*Q.v[1] - v[1]*Q.v[0];
     
     for(int i=0;i<3;++i) // s1 v2 + s2 v1
       outQ.v[i] += s*Q.v[i]+Q.s*v[i];

     return outQ;
   }

   /* due to accumulating round-off error, it may be necessary to normalize */
   /* this will ensure that the quaternion is truly unit */
   public void normalize()
   {
     float mag = magnitude();

     if(mag > EPSILON)
     {
       s /= mag;
       v[0] /= mag;
       v[1] /= mag;
       v[2] /= mag;
     }
   }

   public float magnitude()
   {
     return (float) Math.sqrt(s*s + v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
   }

     
   /* Use Eq. 5-107 on p. 273 of Hearn and Baker */
   /* be aware that OpenGL uses column major when specifying the matrix */
   public float[] to_matrix()
   {
     float a,b,c;
     float[] M = new float[16];

     a = v[0];
     b = v[1];
     c = v[2];

     // Specify the matrix in column major
     M[0]  = 1 - 2*b*b - 2*c*c;             // M[0][0]
     M[1]  = 2*a*b + 2*s*c;                 // M[1][0]
     M[2]  = 2*a*c - 2*s*b;                 // M[2][0]
     M[3]  = 0.0f;                          // M[3][0]

     M[4]  = 2*a*b - 2*s*c;                 // M[0][1]
     M[5]  = 1 - 2*a*a - 2*c*c;             // M[1][1]
     M[6]  = 2*b*c + 2*s*a;                 // M[2][1]
     M[7]  = 0.0f;                          // M[3][1]

     M[8]  = 2*a*c + 2*s*b;                 // M[0][2]
     M[9]  = 2*b*c - 2*s*a;                 // M[1][2]
     M[10] = 1 - 2*a*a - 2*b*b;             // M[2][2]
     M[11] = 0.0f;                          // M[3][2]

     M[12] = 0.0f;                          // M[0][3]
     M[13] = 0.0f;                          // M[1][3]
     M[14] = 0.0f;                          // M[2][3]
     M[15] = 1.0f;                          // M[3][3] 
     
     

     return M;
   }
        
}
