//#include"mat.cpp"
double linklength=60;
enum status{ACC,DEC,CONST};
#define PI 3.1415926535897932384626433832795
bool toconst=0;
struct angles
{
	double th1;
	double th2;
	double th3;
};
struct cartesian
{
	double x;
	double y;
	double z;
};
cartesian ToCartesian(angles a)
{
	cartesian Cartesian;
	double th=180-a.th2-(180-a.th3)/2;
	th*=(PI/180);
	double n=2*linklength*sin((a.th3/2)*(PI/180));
	Cartesian.y=n*sin(th);
	double Z=n*cos(th)+linklength;
	Cartesian.z=Z*cos(a.th1*(PI/180));
	Cartesian.x=Cartesian.z*tan(a.th1*(PI/180));
	
	return Cartesian;
	
}
angles ToAngles(cartesian c)
{
	angles Angles;
	Angles.th1=atan(c.x/c.z)*(180/PI);
	double th=90-abs(Angles.th1);
	double zz=c.z*cos(Angles.th1*(PI/180))+abs(c.x)*cos(th*(PI/180));
	double n=sqrt(pow(zz-linklength,2)+pow(c.y,2));
	Angles.th3=2*asin(n/(2*linklength))*(180/PI);
	Angles.th2=180-acos((zz-linklength)/n)*(180/PI)-(180-Angles.th3)/2;
	
	return Angles;
}
enum Type{Line,GoTo};
enum Target{MaxLinearity,MaxSpeed};

bool plus_minus(double val,double tar)
{
	double tol =0.001;
	if(val>=tar-tol && val<=tar+tol)
		return 1;
	else return 0;
}


int main()
{
	double n=15; // assuming constant speed ..
	double dx=20;
	double dy=40;
	double dz=0;
	cartesian cart;
	cart.x=0;
	cart.y=40;
	cart.z=70;
	angles tempang=ToAngles(cart);
	cartesian tempcar1=cart;
	cartesian tempcar2;
	double dxbydth1=0;
	double dybydth1=0;
	double dzbydth1=0;
	double dxbydth2=0;
	double dybydth2=0;
	double dzbydth2=0;
	double dxbydth3=0;
	double dybydth3=0;
	double dzbydth3=0;
	tempang.th1+=0.1;
	tempcar2=ToCartesian(tempang);
	dxbydth1=tempcar2.x-tempcar1.x;
	dybydth1=tempcar2.y-tempcar1.y;
	dzbydth1=tempcar2.z-tempcar1.z;
	tempang.th1-=0.1;
	tempang.th2+=0.1;
	tempcar2=ToCartesian(tempang);
	dxbydth2=tempcar2.x-tempcar1.x;
	dybydth2=tempcar2.y-tempcar1.y;
	dzbydth2=tempcar2.z-tempcar1.z;
	tempang.th2-=0.1;
	tempang.th3+=0.1;
	tempcar2=ToCartesian(tempang);
	dxbydth3=tempcar2.x-tempcar1.x;
	dybydth3=tempcar2.y-tempcar1.y;
	dzbydth3=tempcar2.z-tempcar1.z;
	tempang.th3-=0.1;

	matrix A(3,3);
	A.set(0,0,dxbydth1);
	A.set(0,1,dxbydth2);
	A.set(0,2,dxbydth3);
	A.set(1,0,dybydth1);
	A.set(1,1,dybydth2);
	A.set(1,2,dybydth3);
	A.set(2,0,dzbydth1);
	A.set(2,1,dzbydth2);
	A.set(2,2,dzbydth3);

	matrix B(3,1);
	B.set(0,0,0);
	B.set(1,0,0);
	B.set(2,0,4);

	matrix C(3,1);
	C.set(0,0,0);
	C.set(1,0,0);
	C.set(2,0,0);

	for(float j=0 ;j<4.0; j+=0.0005)
		for( float i=0 ;i<4.0; i+=0.0005)
		{
			B.set(0,0,j);
			B.set(0,1,i);
			C=A*B;
			double t1=C.get(1,0)*(dx/dy);
			double t2=C.get(1,0)*(dz/dy);
			if(plus_minus(C.get(0,0),t1) && plus_minus(C.get(2,0),t2))
				break;
		}
	
		C.ShowMat();
		cart.x+=C.get(0,0);
		cart.y+=C.get(1,0);
		cart.z+=C.get(2,0);
		cout<<" ("<<cart.x<<" , "<<cart.y<<" , "<<cart.z<<" )"<<endl;
		return 0;
}