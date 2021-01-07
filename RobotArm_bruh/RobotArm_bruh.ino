#include <stdio.h>
#include <math.h>


  
  class RobotArm
  {
    private: 
    float **DH;
    float **_DH;
  
    public:
//PRUEBAS

   RobotArm(int dof);
   void initDH(int n, int m);
   void genMat(float **M, int n, int m);
   void matZero(float** A, int n, int m);
   void genVec(float *qi, int n);
   void showVec(float *qi, int n, char label);
   
//PRUEBAS
   

   void Ai(float** _DH, float** A, float* qi, int eje);
   void A0n(float **_DH, float *q, int n, float **Aout, float** Atmp2, float** Atmp);
   void A0nForJacob(float **_DH, float *q,int n,float **Aout, float **Z, float** P, float **Atmp, float **Atmp2, float* zi, float*pi);
   void Jacob(float **_DH, float *q, float **J, float **Aout, float **Atmp, float **Atmp2, float *zi, float *pi, float *jpi, float *p, float **Z, float **P, float *ptmp);
   void eyeMat(float **A, int n);
   void crossVec(float *zi, float *ptmp, float *jpi, int n);
   void sub(float* p, float* pi, float* ptmp, int n);
   void multMat(float **A, float **B, float **C,int n, int m, int l);
   void cpyMat(float **A, float **B, int n, int m);
   void cpyVec2MatInCols(float *a, float **A, int n, int row, int col);
   void cpyVec(float *a, float *b, int n);
   void zeroMat(float **A, int n, int m);
   void zeroVec(float *v, int n);
   void getP(float **A,float *p);
   void getZ(float **A,float *z);
   void getVecFromMatInCols(float **A,int row, int col, int n, float *a);
   void showMatrix(float **M, int nfilas, int ncol, char label);
      
  };
  
#include <stdio.h>
#include <math.h>
//#include <Arduino.h>
#include <stdlib.h>


#define M_PI 3.14159265358979323846


RobotArm::RobotArm(int dof)
{
  this->initDH(dof,4); 
}

void RobotArm::initDH(int n, int m)
{
  DH=(float**)malloc(n*sizeof(float*));
  for(int i=0; i<n; i++) {
    DH[i] = (float*) malloc(m*sizeof(float));
  }
  
}

//PRUEBAS

  void RobotArm::showVec(float *qi, int n, char label)
  {
    //NO CAMBIADO POR PRINTS F//
    Serial.println();
    Serial.print(label);
    Serial.println();
    
    for(int i=0; i<n; i++)
    {
      
      
      Serial.print(qi[i]);
      
      Serial.println();
    }
  }

void RobotArm::genQi(float *qi, int n)
{
  //qi n grados
  
  qi[0]=90;
  qi[1]=0;
  qi[2]=0;
  qi[3]=0;
  qi[4]=0;
  qi[5]=0;
   /*
    for(int i=0;i<n;i++)
        {
            
            qi[i]=180;
        }
        */
      
}
void RobotArm::genMat(float **M, int n, int m)
{
   
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++){
            M[i][j]=3;
        }
    }
}

void RobotArm::matZero(float** A, int n, int m)
{
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<m;j++)
    {
      A[i][j]=0;
    }
  }
}


//PRUEBAS



  void RobotArm::Ai(float** _DH, float** A, float* qi, int eje) //rellena la matriz Ai con los valores correspondientes de DH y la guarda en A//
  {
    //TRABAJA EN RADIANES!!!//
    
    float ctheta=cos((_DH[eje][0]+qi[eje])*M_PI/180);
    float stheta=sin((_DH[eje][0]+qi[eje])*M_PI/180);
    float calpha=cos(_DH[eje][3]*M_PI/180);
    float salpha=sin(_DH[eje][3]*M_PI/180);
    float a=_DH[eje][2];
    float d=_DH[eje][1];

    A[0][0]=ctheta;
    A[0][1]=-calpha*stheta;
    A[0][2]=salpha*stheta;
    A[0][3]=a*ctheta;
    
    A[1][0]=stheta;
    A[1][1]=calpha*ctheta;
    A[1][2]=-salpha*ctheta;
    A[1][3]=a*stheta;
    
    A[2][0]=0;
    A[2][1]=salpha;
    A[2][2]=calpha;
    A[2][3]=d;
    
    A[3][0]=0;
    A[3][1]=0;
    A[3][2]=0;
    A[3][3]=1;
   
    
  }
 
 void RobotArm::A0n(float **_DH, float *q, int n, float **Aout, float** Atmp2, float** Atmp) //multiplica la matriz identidad por las consecutivas An//
  {
    eyeMat(Atmp2,4);
    for(int i=0;i<n;i++)
    {
    Ai(_DH, Atmp, q, i);
    multMat(Atmp2,Atmp,Aout,4,4,4);
    cpyMat(Aout,Atmp2,4,4);
    }
    
  }


  
 
  
  void RobotArm::eyeMat(float **A, int n) //crea una matriz identidad//
  {
    for (int i=0;i<n;i++)
    {
      for (int j=0;j<n;j++)
      {
        if (i==j)
          A[i][j]=1;
        else
          A[i][j]=0;
      }
    }
  }
  
  

  void RobotArm::crossVec(float *zi, float *ptmp, float *jpi, int n)  //multiplica el vector zi por ptmp y lo guarda en zi//
  {
    for(int i=0;i<n;i++)
    {
      jpi[i]=zi[i]*ptmp[i];
    }
  }
  
  void RobotArm::sub(float* p, float* pi, float* ptmp, int n)
  {
    for (int i=0;i<n;i++)
    {
      ptmp[i]=p[i]-pi[i];
    }
  }

  
  void RobotArm::multMat(float **A, float **B, float **C,int n, int m, int l) //Multiplica A por B y lo guarda en C//
  {
    for (int i=0;i<n;i++)
    {
      for (int k=0;k<l;k++)
      {
        float tmp=0;
        for (int j=0;j<m;j++)
        {
          tmp+=A[i][j]*B[j][k];
        }
        C[i][k]=tmp;
      }
    }
  }
  
  void RobotArm::cpyMat(float **A, float **B, int n, int m) //funcion para copiar una matriz A en una B//
  {
    for (int i=0;i<n;i++)
    {
      for (int j=0;j<m;j++)
      {
        B[i][j]=A[i][j];
      }
    }
  }
  
  void RobotArm::cpyVec2MatInCols(float *a, float **A, int n, int row, int col) //coge el vector a y lo pone en columnas en la matriz A//
  {
    for (int i=0;i<n;i++)
    {
         A[i+row][col]=a[i];
        
    }
  }
  
  void RobotArm::cpyVec(float *a, float *b, int n)  //copia el vector a en el b//
  {
    for (int i=0;i<n;i++)
    {
      b[i]=a[i];
    }
  }
  
  void RobotArm::zeroMat(float **A, int n, int m) //crea una matriz de ceros//
  {
    for (int i=0;i<n;i++)
    {
      for (int j=0;j<m;j++)
      {
        A[i][j]=0;
      }
    }
  }
  
  void RobotArm::zeroVec(float *v, int n) //crea un vector de ceros//
  {
    for (int i=0;i<n;i++)
    {
      v[i]=0;
    }
  }
  
  void RobotArm::getP(float **A,float *p) //saca el vector P (3x1) de la matriz A//
  {
    p[0]=A[0][3];
    p[1]=A[1][3];
    p[2]=A[2][3];
  }
  
  void RobotArm::getZ(float **A,float *z) //saca el vector Z (3x1) de la matriz A//
  {
    z[0]=A[0][2];
    z[1]=A[1][2];
    z[2]=A[2][2];
  }
  
  void RobotArm::getVecFromMatInCols(float **A,int row, int col, int n, float *a)
  {
    for (int i=0;i<n;i++)
    {
      a[i]=A[i+row][col];
    }
  }
  
  
  void RobotArm::showMatrix(float **M, int nfilas, int ncol, char label)
  {

    //SERIALS NO CAMBIADOS POR PRINTF
    Serial.println();
    Serial.print(label);
    Serial.println();
    
    for(int i=0; i<nfilas; i++)
    {
      for(int j=0; j<ncol; j++)
      {
        Serial.print(M[i][j]);
        Serial.print(" ");
      }
      Serial.println("");
    }
  }

#include <stdio.h>
#include <math.h>
#include <stdlib.h>


RobotArm robot(6);


//void setup no cambiado por int main(){return 0;}
void setup()
{
  Serial.begin(9600);
    
    //inicializar matrices
    int n , m;
    
    n=6;
    m=4;
        
    float **DH = new float*[n];
    for (int i = 0; i < n; ++i)
    {
      DH[i] = new float[m];
    }
        
        
    float **_DH = new float*[n];
    for (int i = 0; i < n; ++i)
    {
        _DH[i] = new float[m];
    }

    
    float** A = new float*[n];
    for (int i = 0; i < n; ++i)
    {
        A[i] = new float[m];
    }
        
    float** B = new float*[n];
    for (int i = 0; i < n; ++i)
    {
        B[i] = new float[m];
    }
            
    float** C = new float*[n];
    for (int i = 0; i < n; ++i)
    {
        C[i] = new float[n];
    }
    
    float** D = new float*[n];
    for (int i = 0; i < n; ++i)
    {
        D[i] = new float[n];
    }
    
    
    float** Z = new float*[n];
    for (int i = 0; i < n; ++i)
    {
        Z[i] = new float[n];
    }
    
    float **P=new float*[6];
    for(int i=0;i<6;i++)
    {
      P[i]=new float [6];
    }
   
    float** J = new float*[n];
    for (int i = 0; i < n; ++i)
    {
        J[i] = new float[n];
    }

    //borrar
    float** A1 = new float*[4];
    for (int i = 0; i < 4; ++i)
    {
        A1[i] = new float[4];
    }
    float** A2 = new float*[4];
    for (int i = 0; i < 4; ++i)
    {
        A2[i] = new float[4];
    }
    float** A3 = new float*[4];
    for (int i = 0; i < 4; ++i)
    {
        A3[i] = new float[4];
    }
    float** A4 = new float*[4];
    for (int i = 0; i < 4; ++i)
    {
        A4[i] = new float[4];
    }
    float** A5 = new float*[4];
    for (int i = 0; i < 4; ++i)
    {
        A5[i] = new float[4];
    }
    float** A6 = new float*[4];
    for (int i = 0; i < 4; ++i)
    {
        A6[i] = new float[4];
    }

    //borrar

   
    float *qi = (float*)malloc(n * sizeof(float));
    float *zi = (float*)malloc(n * sizeof(float));    
    float *pi = (float*)malloc(n * sizeof(float));
    float *jpi = (float*)malloc(n * sizeof(float));
    float *z = (float*)malloc(n * sizeof(float));
    float *p = (float*)malloc(n * sizeof(float));
    float *ptmp = (float*)malloc(n * sizeof(float));

    


    
    
    
    //hasta aqui

    




float d1=5;
float a2=6;
float d4=7;
float d6=8;


DH[0][0]=0;
DH[0][1]=d1;
DH[0][2]=0;
DH[0][3]=90;

DH[1][0]=90;
DH[1][1]=0;
DH[1][2]=a2;
DH[1][3]=0;

DH[2][0]=-90;
DH[2][1]=0;
DH[2][2]=0;
DH[2][3]=-90;

DH[3][0]=0;
DH[3][1]=d4;
DH[3][2]=0;
DH[3][3]=90;

DH[4][0]=0;
DH[4][1]=0;
DH[4][2]=0;
DH[4][3]=-90;

DH[5][0]=0;
DH[5][1]=d6;
DH[5][2]=0;
DH[5][3]=0;


    robot.cpyMat(DH,_DH,n,m);
    robot.showMatrix(_DH,n,m, 'H');

    robot.genQi(qi,n);
    robot.showVec(qi, n, 'q');


    robot.Ai(_DH,A1,qi,0);
    robot.showMatrix(A1,4,4, '1');
    
    robot.A0n(_DH,qi, 6, A,B,D);
    robot.showMatrix(A,m,m, '0');


    
    

  
  
}



void loop()
{
  while(1);
}
