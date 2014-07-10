//************************************************************************
// Coordinate Class
//
// Comments :
//   Stores the 3D coordinate (x,y,z)
//
// History :
//   30 Jan 2008. Created by Tai-Peng Tian (tiantp@gmail.com)
//   


public class Coord
{
  public double x, y, z;

  public Coord()
  {
    x = y = z = 0.0;
  }

  public Coord( double _x, double _y , double _z)
  {
    x = _x; 
    y = _y;
    z = _z;
  }
}
