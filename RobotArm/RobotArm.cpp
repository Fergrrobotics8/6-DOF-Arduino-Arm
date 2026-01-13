#include <cstdio>
#include <cmath>
#include <vector>
#include <cstddef>

// Helper function for degree to radian conversion
inline float deg2rad(float deg) noexcept {
  return deg * M_PI / 180.0f;
}

class RobotArm
	{
		private: 
		std::vector<std::vector<float>> DH;
    std::vector<std::vector<float>> _DH;
  
		public:
//PRUEBAS

   RobotArm(int dof);
   void initDH(int n, int m);
   void genMat(std::vector<std::vector<float>>& M, int n, int m);
   void matZero(std::vector<std::vector<float>>& A, int n, int m);
   void genQi(std::vector<float>& qi, int n);
   void showVec(const std::vector<float>& qi, int n, char label);
   
//PRUEBAS
   

   void Ai(const std::vector<std::vector<float>>& _DH, std::vector<std::vector<float>>& A, const std::vector<float>& qi, int eje);
   void A0n(const std::vector<std::vector<float>>& _DH, const std::vector<float>& q, int n, std::vector<std::vector<float>>& Aout, std::vector<std::vector<float>>& Atmp2, std::vector<std::vector<float>>& Atmp);
   void A0nForJacob(const std::vector<std::vector<float>>& _DH, const std::vector<float>& q, int n, std::vector<std::vector<float>>& Aout, std::vector<std::vector<float>>& Z, std::vector<std::vector<float>>& P, std::vector<std::vector<float>>& Atmp, std::vector<std::vector<float>>& Atmp2, std::vector<float>& zi, std::vector<float>& pi);
   void Jacob(const std::vector<std::vector<float>>& _DH, const std::vector<float>& q, std::vector<std::vector<float>>& J, std::vector<std::vector<float>>& Aout, std::vector<std::vector<float>>& Atmp, std::vector<std::vector<float>>& Atmp2, std::vector<float>& zi, std::vector<float>& pi, std::vector<float>& jpi, std::vector<float>& p, std::vector<std::vector<float>>& Z, std::vector<std::vector<float>>& P, std::vector<float>& ptmp);
   void eyeMat(std::vector<std::vector<float>>& A, int n);
   void crossVec(const std::vector<float>& zi, const std::vector<float>& ptmp, std::vector<float>& jpi, int n);
   void sub(const std::vector<float>& p, const std::vector<float>& pi, std::vector<float>& ptmp, int n);
   void multMat(const std::vector<std::vector<float>>& A, const std::vector<std::vector<float>>& B, std::vector<std::vector<float>>& C, int n, int m, int l);
   void cpyMat(const std::vector<std::vector<float>>& A, std::vector<std::vector<float>>& B, int n, int m);
   void cpyVec2MatInCols(const std::vector<float>& a, std::vector<std::vector<float>>& A, int n, int row, int col);
   void cpyVec(const std::vector<float>& a, std::vector<float>& b, int n);
   void zeroMat(std::vector<std::vector<float>>& A, int n, int m);
   void zeroVec(std::vector<float>& v, int n);
   void getP(const std::vector<std::vector<float>>& A, std::vector<float>& p);
   void getZ(const std::vector<std::vector<float>>& A, std::vector<float>& z);
   void getVecFromMatInCols(const std::vector<std::vector<float>>& A, int row, int col, int n, std::vector<float>& a);
   void showMatrix(const std::vector<std::vector<float>>& M, int nfilas, int ncol, char label);
			
	};


RobotArm::RobotArm(int dof) {
  this->initDH(dof, 4);
}

void RobotArm::initDH(int n, int m) {
  DH.assign(n, std::vector<float>(m, 0.0f));
  _DH.assign(n, std::vector<float>(m, 0.0f));
}

//PRUEBAS

void RobotArm::showVec(const std::vector<float>& qi, int n, char label) {
  printf("\n%c\n", label);
  for(int i = 0; i < n; i++) {
    printf("%f\n", qi[i]);
  }
}

void RobotArm::genQi(std::vector<float>& qi, int n) {
  // qi n grados
  qi[0] = 90;
  qi[1] = 0;
  qi[2] = 0;
  qi[3] = 0;
  qi[4] = 0;
  qi[5] = 0;
}
void RobotArm::genMat(std::vector<std::vector<float>>& M, int n, int m) {
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      M[i][j] = 3;
    }
  }
}

void RobotArm::matZero(std::vector<std::vector<float>>& A, int n, int m) {
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      A[i][j] = 0;
    }
  }
}


//PRUEBAS



void RobotArm::Ai(const std::vector<std::vector<float>>& _DH, std::vector<std::vector<float>>& A, const std::vector<float>& qi, int eje) {
  // Computes DH transformation matrix for joint eje
  float theta = deg2rad(_DH[eje][0] + qi[eje]);
  float ctheta = std::cos(theta);
  float stheta = std::sin(theta);
  
  float alpha = deg2rad(_DH[eje][3]);
  float calpha = std::cos(alpha);
  float salpha = std::sin(alpha);
  
  float a = _DH[eje][2];
  float d = _DH[eje][1];

  A[0][0] = ctheta;
  A[0][1] = -calpha * stheta;
  A[0][2] = salpha * stheta;
  A[0][3] = a * ctheta;
  
  A[1][0] = stheta;
  A[1][1] = calpha * ctheta;
  A[1][2] = -salpha * ctheta;
  A[1][3] = a * stheta;
  
  A[2][0] = 0;
  A[2][1] = salpha;
  A[2][2] = calpha;
  A[2][3] = d;
  
  A[3][0] = 0;
  A[3][1] = 0;
  A[3][2] = 0;
  A[3][3] = 1;
}
 
void RobotArm::A0n(const std::vector<std::vector<float>>& _DH, const std::vector<float>& q, int n, std::vector<std::vector<float>>& Aout, std::vector<std::vector<float>>& Atmp2, std::vector<std::vector<float>>& Atmp) {
  // Multiplies identity matrix by consecutive transformation matrices
  eyeMat(Atmp2, 4);
  for(int i = 0; i < n; i++) {
    Ai(_DH, Atmp, q, i);
    multMat(Atmp2, Atmp, Aout, 4, 4, 4);
    cpyMat(Aout, Atmp2, 4, 4);
  }
}


  
 
	
void RobotArm::eyeMat(std::vector<std::vector<float>>& A, int n) {
  // Creates an identity matrix
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      A[i][j] = (i == j) ? 1.0f : 0.0f;
    }
  }
}
	
	

void RobotArm::crossVec(const std::vector<float>& zi, const std::vector<float>& ptmp, std::vector<float>& jpi, int n) {
  // Element-wise multiplication for jacobian computation
  for(int i = 0; i < n; i++) {
    jpi[i] = zi[i] * ptmp[i];
  }
}
	
void RobotArm::sub(const std::vector<float>& p, const std::vector<float>& pi, std::vector<float>& ptmp, int n) {
  for (int i = 0; i < n; i++) {
    ptmp[i] = p[i] - pi[i];
  }
}

	
void RobotArm::multMat(const std::vector<std::vector<float>>& A, const std::vector<std::vector<float>>& B, std::vector<std::vector<float>>& C, int n, int m, int l) {
  // Multiplies A (n x m) by B (m x l) and stores result in C
  for (int i = 0; i < n; i++) {
    for (int k = 0; k < l; k++) {
      float tmp = 0;
      for (int j = 0; j < m; j++) {
        tmp += A[i][j] * B[j][k];
      }
      C[i][k] = tmp;
    }
  }
}
	
void RobotArm::cpyMat(const std::vector<std::vector<float>>& A, std::vector<std::vector<float>>& B, int n, int m) {
  // Copies matrix A into matrix B
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      B[i][j] = A[i][j];
    }
  }
}
	
void RobotArm::cpyVec2MatInCols(const std::vector<float>& a, std::vector<std::vector<float>>& A, int n, int row, int col) {
  // Copies vector a into a column of matrix A
  for (int i = 0; i < n; i++) {
    A[i + row][col] = a[i];
  }
}
	
void RobotArm::cpyVec(const std::vector<float>& a, std::vector<float>& b, int n) {
  // Copies vector a into vector b
  for (int i = 0; i < n; i++) {
    b[i] = a[i];
  }
}
	
void RobotArm::zeroMat(std::vector<std::vector<float>>& A, int n, int m) {
  // Creates a zero matrix
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      A[i][j] = 0;
    }
  }
}
	
void RobotArm::zeroVec(std::vector<float>& v, int n) {
  // Creates a zero vector
  for (int i = 0; i < n; i++) {
    v[i] = 0;
  }
}
	
void RobotArm::getP(const std::vector<std::vector<float>>& A, std::vector<float>& p) {
  // Extracts position vector P (3x1) from transformation matrix A
  p[0] = A[0][3];
  p[1] = A[1][3];
  p[2] = A[2][3];
}
	
void RobotArm::getZ(const std::vector<std::vector<float>>& A, std::vector<float>& z) {
  // Extracts z-axis vector (3x1) from transformation matrix A
  z[0] = A[0][2];
  z[1] = A[1][2];
  z[2] = A[2][2];
}
	
void RobotArm::getVecFromMatInCols(const std::vector<std::vector<float>>& A, int row, int col, int n, std::vector<float>& a) {
  for (int i = 0; i < n; i++) {
    a[i] = A[i + row][col];
  }
}
	
	
void RobotArm::showMatrix(const std::vector<std::vector<float>>& M, int nfilas, int ncol, char label) {
  printf("\n%c\n", label);
  for(int i = 0; i < nfilas; i++) {
    for(int j = 0; j < ncol; j++) {
      printf("%f ", M[i][j]);
    }
    printf("\n");
  }
}

RobotArm robot(6);

int main() {
  // Initialize matrices and vectors with modern C++ containers
  int n = 6;
  int m = 4;
  
  std::vector<std::vector<float>> DH(n, std::vector<float>(m, 0.0f));
  std::vector<std::vector<float>> _DH(n, std::vector<float>(m, 0.0f));
  
  std::vector<std::vector<float>> A(n, std::vector<float>(m, 0.0f));
  std::vector<std::vector<float>> B(n, std::vector<float>(m, 0.0f));
  std::vector<std::vector<float>> C(n, std::vector<float>(n, 0.0f));
  std::vector<std::vector<float>> D(n, std::vector<float>(n, 0.0f));
  
  std::vector<std::vector<float>> Z(n, std::vector<float>(n, 0.0f));
  std::vector<std::vector<float>> P(6, std::vector<float>(6, 0.0f));
  std::vector<std::vector<float>> J(n, std::vector<float>(n, 0.0f));
  
  // Individual transformation matrices
  std::vector<std::vector<float>> A1(4, std::vector<float>(4, 0.0f));
  std::vector<std::vector<float>> A2(4, std::vector<float>(4, 0.0f));
  std::vector<std::vector<float>> A3(4, std::vector<float>(4, 0.0f));
  std::vector<std::vector<float>> A4(4, std::vector<float>(4, 0.0f));
  std::vector<std::vector<float>> A5(4, std::vector<float>(4, 0.0f));
  std::vector<std::vector<float>> A6(4, std::vector<float>(4, 0.0f));
  
  // Joint angles and vectors
  std::vector<float> qi(n, 0.0f);
  std::vector<float> zi(n, 0.0f);
  std::vector<float> pi(n, 0.0f);
  std::vector<float> jpi(n, 0.0f);
  std::vector<float> z(n, 0.0f);
  std::vector<float> p(n, 0.0f);
  std::vector<float> ptmp(n, 0.0f);

    


    
    
    
    //hasta aqui

    




  float a2 = 6;
  float d4 = 7;
  float d6 = 8;


  // Set DH parameters
  DH[0] = {0,  d1, 0, 90};
  DH[1] = {90, 0,  a2, 0};
  DH[2] = {-90, 0, 0, -90};
  DH[3] = {0,  d4, 0, 90};
  DH[4] = {0,  0,  0, -90};
  DH[5] = {0,  d6, 0, 0};

  // Test: Copy DH parameters and display
  robot.cpyMat(DH, _DH, n, m);
  robot.showMatrix(_DH, n, m, 'H');

  // Generate joint angles and display
  robot.genQi(qi, n);
  robot.showVec(qi, n, 'q');

  // Compute first transformation matrix A1
  robot.Ai(_DH, A1, qi, 0);
  robot.showMatrix(A1, 4, 4, '1');
  
  // Compute cumulative transformation A0n
  robot.A0n(_DH, qi, 6, A, B, D);
  robot.showMatrix(A, m, m, '0');

  return 0;
}



void loop()
{
  while(1);
}
