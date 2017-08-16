#include<iostream>
#include<ctime>
#include<string>
#include<iomanip>
#include<conio.h>
#include<strstream>
using namespace std;
enum MatrixType{Identity,Random,Zero};
class matrix
{
private:
	int rows;
	int columns;
	float **matptr;
public:
	matrix(int c,int r):rows(r),columns(c)
	{
		cout<<"\nusing first constructor.."<<endl;
		matptr=new float*[rows];
		for(int j=0;j<rows;j++)
			matptr[j]=new float[columns];
		for(int j=0;j<rows;j++)
			for(int i=0;i<columns;i++)
				matptr[j][i]=0;
	}
	matrix(int c,int r,float f):rows(r),columns(c)
	{
		cout<<"\nusing second constructor.."<<endl;
		matptr=new float *[columns];
		for(int j=0;j<rows;j++)
			matptr[j]=new float[rows];
		for(int j=0;j<rows;j++)
			for(int i=0;i<columns;i++)
				matptr[j][i]=f;
	}
	matrix(int c,int r,MatrixType mt):rows(r),columns(c)
	{
		//cout<<"\nusing third constructor.."<<endl;
		matptr=new float*[rows];
		for(int j=0;j<rows;j++)
			matptr[j]=new float[columns];
		if(mt==Identity)
		{
		    for(int j=0;j<rows;j++)
			    for(int i=0;i<columns;i++)
			    {
						matptr[j][i]=0.0;
						if(j==i)matptr[j][i]=1.0;
			     }  
		}
		else if(mt==Zero)
			for(int j=0;j<rows;j++)
			    for(int i=0;i<columns;i++)
					matptr[j][i]=0.0;

		else if(mt==Random)
		{
			srand(time(NULL));float k;
			for(int j=0;j<rows;j++)
			    for(int i=0;i<columns;i++)
				{
				    k=rand()%50;
				    matptr[j][i]=k;
			    }
	    } 
	}      
	matrix(int c,int r,float **arr,int arrR,int arrC):rows(r),columns(c)
	{
		cout<<"\nusing fourth constructor.."<<endl;
		if(rows==arrR &&columns==arrC)
		{
			matptr=new  float*[columns];
		    for(int j=0;j<rows;j++)
			    matptr[j]=new float[rows];
		    for(int j=0;j<rows;j++)
			    for(int i=0;i<columns;i++)
				    matptr[j][i]=arr[j][i];
		}
		else
			cout<<"sorry , the  two matrices aren't of the same dimensions "<<endl;
	}
    matrix& operator +(matrix m)
{
	matrix * temp=new matrix(columns,rows);
	cout<<"\nusing operator + "<<endl;
	for(int j=0;j<rows;j++)
        for(int i=0;i<columns;i++)
		{
        	temp->matptr[j][i]=matptr[j][i]+m.matptr[j][i];
		}
		return *temp;
}
    matrix& operator -(matrix m)
{
	cout<<"\nusing operator - "<<endl;
	matrix *temp=new matrix(columns,rows);
	for(int j=0;j<rows;j++)
	    for(int i=0;i<columns;i++)
		{
        	temp->matptr[j][i]=matptr[j][i]-m.matptr[j][i];
		}
        return *temp;
}
    bool operator==(matrix m)
{
	cout<<"\nusing operator =="<<endl;
	for(int j=0;j<rows;j++)
	    for(int i=0;i<columns;i++)
	    {
       	    if(matptr[j][i]!=m.matptr[j][i])
		    return 0;
	    }
	return 1;
}
    bool operator!=(matrix m)
{
	cout<<"\nusing operator !="<<endl;
	for(int j=0;j<rows;j++)
	    for(int i=0;i<columns;i++)
	    {
       	    if(matptr[j][i]==m.matptr[j][i])
		    return 0;
	    }
	return 1;
}
    matrix& operator *(matrix m)
{
	//cout<<"\nusing operator *"<<endl;
	if(columns=m.rows)
	{
		matrix *temp=new matrix(m.columns,rows,Zero);
	    for(int k=0;k<m.columns;k++)
        {
			for(int j=0;j<rows;j++)
	        {
			    for(int i=0;i<columns;i++)
			        temp->matptr[j][k]+=matptr[j][i]*m.matptr[i][k];
			
	        }
	    }
	return *temp;
	}

}
    matrix& operator *(float f)
{
	for(int j=0;j<rows;j++)
	    for(int i=0;i<columns;i++)
			matptr[j][i]*=f;
	return *this;
}
    matrix& operator /(float f)
{
	for(int j=0;j<rows;j++)
		for(int i=0;i<columns;i++)
			matptr[j][i]/=f;
	return *this;
}
    matrix& operator /(matrix m)
{
	if(columns == rows)
	{
		matrix mat(2*columns,rows);
		for(int j=0;j<rows;j++)
	      for(int i=0;i<columns;i++)
				mat.matptr[j][i]=m.matptr[j][i];
		for(int j=0;j<rows;j++)
		   for(int i=columns;i<columns*2;i++)
				   {
						mat.matptr[j][i]=0.0;
						if(i==j+rows)mat.matptr[j][i]=1.0;
				   }
		for(int k=0;k<columns;k++)
		{
		     float p=mat.matptr[k][k];
			 for(int i=0;i<2*columns;i++)
		          mat.matptr[k][i]/=p;
                  for(int j=k+1;j<rows;j++)
			      {
				     float p=mat.matptr[j][k];
		             for(int i=0;i<2*columns;i++)
	                 mat.matptr[j][i]=mat.matptr[j][i]-p*mat.matptr[k][i];
			      }
                 for(int j=k-1;j>=0;j--)
			     {
				     float p=mat.matptr[j][k];
		             for(int i=0;i<2*columns;i++)
	                     mat.matptr[j][i]=mat.matptr[j][i]-p*mat.matptr[k][i];
			     }
	    	}
		
		matrix *inv=new matrix(columns,rows);
		for(int j=0;j<rows;j++)
	       for(int i=0;i<columns;i++)
               inv->matptr[j][i]=mat.matptr[j][i+rows];
		matrix *div=new matrix(columns,rows); 
		*div=(*this)*(*inv);
		return *div;
	}
	else return *this;
}


    bool IsIdentity()
{  
	cout<<"\nchecking the case of Identity matrix";
    if(rows==columns)
	{
        for(int j=0;j<rows;j++)
		    for(int i=0;i<columns;i++)
			{  
				if(i==j && matptr[j][i]!=1.0)
					return 0;
				else if(i!=j && matptr[j][i]!=0.0)
					return 0;
		    }
		return 1;
	}
	return 0;
}
    bool Isidempotent()
{ 
	if(rows==columns)
	{
	    matrix temp(columns,rows);
	    temp=*this * *this; 
		if (temp ==*this)
		{
			delete temp.matptr; 
			return 1;
		}
		else
		{
			delete temp.matptr;
			return 0;
		}
	}
	return 0;
}
    bool IsSquare()
{
	if(rows==columns)return 1;
	else return 0;
}
    bool IsSymmetric()
{   if(columns==rows)
	{
		for(int j=0;j<rows;j++)
	        for(int i=0;i<columns;i++)
	            if(i!=j && matptr[j][i]!=matptr[i][j])
					return 0;
				else return 1;
    }
    return 0;
}
    bool IsSkewSymmetric()
{   
	if(columns==rows)
	{
		for(int j=0;j<rows;j++)
	        for(int i=0;i<columns;i++)
	        {
				if(i!=j && matptr[j][i]!=-matptr[i][j])
				    return 0;
			    if(i==j && matptr[j][i]!=0.0)
				    return 0;
		    }
	    return 1;
    }
    return 0;
}
    bool IsUpperTriangle()
{
	if(rows==columns)
	{
		for(int j=0;j<rows;j++)
			for(int i=0;i<columns;i++)
		        if(i>j && matptr[j][i]==0.0)
			       return 0;
		return 1;
	}
	return 0;
}
    bool IslowerTriangle()
{
	if(rows==columns)
	{
		for(int j=0;j<rows;j++)
			for(int i=0;i<columns;i++)
		        if(i<j && matptr[j][i]==0.0)
			       return 0;
		return 1;
	}
	return 0;
}
    bool IsVector()
{
	if(rows==1)return 1;
	else return 0;
}
    bool IsColumn()
{
	if(columns==1)return 1;
	else return 0;
}
    bool IsInvertible()
{
	if(this->determinate()!=0.0)return 1;
	else return 0;
}

    void Fill(float f)
{
	for(int j=0;j<rows;j++)
			for(int i=0;i<columns;i++)
				matptr[j][i]=f;
}
    void set(int c,int r,float n)
{
	matptr[c][r]=n;
}
    float get(int c,int r)
{
	return matptr[c][r];
}
    int Column()
{
	return columns;
}
    int Row()
{
	return rows;
}
    matrix& transpose()
{
	matrix *temp=new matrix(rows,columns);
	for(int j=0;j<rows;j++)
		for(int i=0;i<columns;i++)
			temp->matptr[i][j]=matptr[j][i];
	return *temp;
}    
  
	float MaxElement()
{
	float old=matptr[0][0];float ans;
	for(int j=0;j<rows;j++)
		for(int i=0;i<columns;i++)
		{
			ans=matptr[j][i];
			if(ans>old){old=ans;}

		}
	return ans;
}
    float MinElement()
{
	float old=matptr[0][0];float ans;
	for(int j=0;j<rows;j++)
		for(int i=0;i<columns;i++)
		{
			ans=matptr[j][i];
			if(ans<old){old=ans;}

		}
	return ans;
}
    float TriDeterminant()
{
	if(rows==columns)
	{
		float ans=1.0;
		for(int j=0;j<rows;j++)
		    ans*=matptr[j][j];
		return ans;
	}
	else return 0;
}
    float determinate()
{
	if(rows==columns &&columns!=2)
	{
		float det=1.0,val=0.0;
		int i,j;
		for(j=0;j<rows;j++)
		{
		     for(i=0;i<columns;i++)
			{
				det*=matptr[i][i+j];
				if((i+j)==columns-1) break;
		    }
				for(int k=0;k<columns-1;k++)
				{
					i++;
					if(i!=columns)
					    det*=matptr[i][k];
					else break;
				}
		   val+=det;
		   det=1.0;
		}
		for(j=0;j<rows;j++)
		{
		     for(i=0;i<columns;i++)
			 {
				det*=matptr[columns-1-i][i+j];
				if((i+j)==columns-1) break;
		     }
				for(int k=0;k<columns-1;k++)
				{
					i++;
					if(i!=columns)
                        det*=matptr[columns-1-i][k];
					else break;
				}
		   val-=det;
		   det=1.0;
		}
		return val;
    }
	else if(columns==2)
	{
		float det=matptr[0][0]*matptr[1][1]-matptr[0][1]*matptr[1][0];
		return det;
	}
}
	void ShowMat()
	{
		for(int j=0;j<rows;j++)
		{
			for(int i=0;i<columns;i++)
				cout<<setiosflags(ios::fixed)
				<<setiosflags(ios::showpoint)
				<<setprecision(2)
				<<matptr[j][i]<<"\t\t";
			cout<<endl;
		}
	}
    string ToString()
	{
		string sp="               ";
		strstream ss;
		for(int j=0;j<rows;j++)
		{ 
			for(int i=0;i<columns;i++)
				ss<<matptr[j][i]<<sp;
		    ss<<'\n';
		}
		ss<<'\0';
		return ss.str();
	}
	
};
/*int main()
{

	
		matrix mat1(3,3,Identity);
		if(mat1.IsIdentity())
			cout<<"\nIdentity"<<endl;
		float det=mat1.determinate();
		if(mat1.Isidempotent())
			cout<<"\nIs idempotent"<<endl;
		cout<<det;
		matrix mat2(3,3);
		mat2.set(0,0,2.0);
		mat2.set(0,1,4.0);
		mat2.set(0,2,5.0);
		mat2.set(1,0,6.0);
		mat2.set(1,1,7.0);
		mat2.set(1,2,3.0);
		mat2.set(2,0,8.0);
		mat2.set(2,1,9.0);
		mat2.set(2,2,1.0);
		det=mat2.determinate();
		cout<<endl<<det;
		matrix mat3(3,3);
		mat3.set(0,0,2.0);
		mat3.set(0,1,4.0);
		mat3.set(0,2,5.0);
		mat3.set(1,0,6.0);
		mat3.set(1,1,7.0);
		mat3.set(1,2,3.0);
		mat3.set(2,0,8.0);
		mat3.set(2,1,9.0);
		mat3.set(2,2,1.0);
		matrix mat4(3,3);
		mat4=mat2/mat3;
		mat4.ShowMat();
		//getche();
		matrix mat10(4,4,Random);

		mat10.ShowMat();
		matrix mat7(3,3);

		mat4.ShowMat();
		mat7=mat4.transpose();
		mat7.ShowMat();
		matrix mat5(4,4,3.5);
		mat5.ShowMat();
		if(!mat4.IsColumn())
			cout<<"\nNot column"<<endl;
		matrix mat6(3,3);
		mat6.set(0,0,2.0);
		mat6.set(0,1,4.0);
		mat6.set(0,2,5.0);
		mat6.set(1,0,0.0);
		mat6.set(1,1,7.0);
		mat6.set(1,2,3.0);
		mat6.set(2,0,0.0);
		mat6.set(2,1,0.0);
		mat6.set(2,2,6.0);
		mat6.ShowMat();
		if(mat6.IsUpperTriangle())
			cout<<"\nIs upper triangle"<<endl;
		if(!mat6.IslowerTriangle())
			cout<<"Not lower triangle"<<endl;
		string strmat=mat6.ToString();
		cout<<strmat;

		det=mat6.determinate();
		cout<<endl<<det;
		mat4=mat2/mat6;
		mat4.ShowMat();
		float tri=mat2.TriDeterminant();
		cout<<endl<<tri;






		getch();
		return 0;
}

*/


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

bool plus_minus(double val,double tar)
{
	double tol =0.01;
	if(val>=tar-tol && val<=tar+tol)
		return 1;
	else return 0;
}


int main()
{
	/*double n=15; // assuming constant speed ..
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
	A.set(1,0,dxbydth2);
	A.set(2,0,dxbydth3);
	A.set(0,1,dybydth1);
	A.set(1,1,dybydth2);
	A.set(2,1,dybydth3);
	A.set(0,2,dzbydth1);
	A.set(1,2,dzbydth2);
	A.set(2,2,dzbydth3);

	matrix B(1,3);
	B.set(0,0,0);
	B.set(0,1,0);
	B.set(0,2,4);

	matrix C(1,3);
	C.set(0,0,0);
	C.set(0,1,0);
	C.set(0,2,0);

	for(float j=0 ;j<4.0; j+=0.005)
		for( float i=0 ;i<4.0; i+=0.005)
		{
			B.set(0,0,j);
			B.set(0,1,i);
			C=A*B;
			double t1=C.get(0,1)*(dx/dy);
			double t2=C.get(0,1)*(dz/dy);
			if(plus_minus(C.get(0,0),t1) && plus_minus(C.get(0,2),t2) )
				break;
		}
	   // cout<<C.get(0,1)<<endl;
		C.ShowMat();
		cart.x+=C.get(0,0);
		cart.y+=C.get(0,1);
		cart.z+=C.get(0,2);
		cout<<" ("<<cart.x<<" , "<<cart.y<<" , "<<cart.z<<" )"<<endl;
		return 0;*/
	matrix a1(3,3,Random);
	cout<<" a1 : "<<endl;a1.ShowMat();
	matrix id(3,3,Identity);
	matrix inva1(3,3);
	inva1=id/a1;
	cout<<"inva1 : "<<endl;inva1.ShowMat();
	a1=id/inva1;
	cout<<" a1 : "<<endl;a1.ShowMat();

	return 0;
	
}