
public class Vec 
{
public float x, y, z;

public Vec(float xx, float yy, float zz)
{
x= xx;
y=yy;
z=zz;
}

public Vec()
{
	x = y = z = 0;
}


public void norm()
{
	float mag = (float)  Math.sqrt( x * x + y * y + z * z);
	x = x/mag;
	y = y/mag;
	z= z/mag;
	
}

public Vec mult (float k)
{
	Vec result = new Vec();
	result.x = x*k;
	result.y = y*k;
	result.z= z*k;
	return result;
	
}

public Vec sub (Vec v2)
{
	Vec result = new Vec();
	result.x = x- v2.x;
	result.y = y-v2.y;
	result.z= z-v2.z;
	return result;
	
}

public Vec add(Vec v2)
{
	Vec result = new Vec();
	result.x = x+v2.x;
	result.y = y+v2.y;
	result.z= z+v2.z;
	return result;
	
}
}


