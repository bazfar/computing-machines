#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <xmmintrin.h>
#include <dvec.h>


int main(void) {
  char qw1[8] = { 1, 1, 1, 1, 1, 1, 1, 1 };
  char qw2[8] = { 2, 2, 2, 2, 2, 2, 2, 2 };

  char qw3[8] = { 6, 6, 5, 5, 9, 8, 7, 7 };
  char qw4[8] = { 2, 2, 2, 2, 2, 2, 2, 2 };


  char w1[8] = { 1, 1, 1, 1, 1, 1, 1, 1 };
  char w2[8] = { 1, 1, 1, 1, 1, 1, 1, 1 };

  char a = 1;
  char b = 2;
  char res[8] = { 10, 10, 10, 10, 10, 10, 10, 10 };
  float c[4] = { 1, 2, 3, 4 };
  float d[4] = { 5, 6, 7, 8 };

  float cc[4] = { 1, 2, 3, 4 };
  float dd[4] = { 5, 6, 7, 8 };
  float f[3] = { 16, 4, 16};
  float g[3] = { 4, 2, 4 };
  float h[3] = { 0, 0, 0 };

  char a128[8] = { -1, 18, 3, 19, 5, 21, 7, 23 };//, 9, 25, 11, 27, 13, 29, 15, 31};
  char b128[8] = { 17, 2, 19, 4, 21, 6, 23, 8 };//, 25, 10, 27, 12, 29, 14, 31, 16};
  char c128[8];




  __m128 r;


  std::cout << "MMX VICHITANIE" << std::endl;

  _asm {
    //mmx
    movq	mm0, qw3
    movq	mm1, qw4
    psubb	mm0, mm1
    movq	qw3, mm0
  }

  for (int i = 0; i < 8; i++)
  {
    printf("%d ", qw3[i]);
  }

  printf("\n");


  _asm {
    //mmx
    movq	mm0, qw1
    movq	mm1, qw2
    paddb	mm0, mm1
    movq	qw1, mm0
  }
  std::cout << "MMX SLOJENIE" << std::endl;

  for (int i = 0; i < 8; i++)
  {
    printf("%d ", qw1[i]);
  }

  printf("\n");

  _asm {
    //sse
    movups	xmm0, c
    movups	xmm1, d
    addps	xmm0, xmm1
    movups	c, xmm0
  }
  printf("%s\n", "VECTORNOE(sse) SLOJENIE :\n");
  for (int i = 0; i < 4; i++)
  {
    printf("%f ", c[i]);
  }
  std::cout << std::endl;



  std::cout << "OSOBAY" << std::endl;

  float c4[4] = { 1, 2, 3, 4 };
  float d4[4] = { 5, 6, 7, 8 };


  _asm {
    //sse
    movups	xmm0, c4
    movups	xmm1, d4
    paddsb	xmm0, xmm1
    movups	c4, xmm0
  }

  for (int i = 0; i < 4; i++)
  {
    printf("%f ", c4[i]);
  }
  std::cout << std::endl;

  std::cout << "Vtoray ocobay" << std::endl;


  float e1[4] = { 1, 2, 3, 4 };
  float e2[4] = { 5, 6, 7, 8 };

  _asm {
    //sse
    movups	xmm0, e1
    movups	xmm1, e2
    haddps	xmm0, xmm1
    movups	e1, xmm0
  }

  for (int i = 0; i < 4; i++)
  {
    printf("%f ", e1[i]);
  }
  std::cout << std::endl;




  std::cout << "VECTORNOE(sse) VICHITANIE" << std::endl;
  _asm { //sse  
    movups xmm0, f
    movups xmm1, g
    subps xmm0, xmm1
    movups f, xmm0
  }

  for (int i = 0; i < 3; i++)
  {
    printf("%f ", f[i]);
    //std::cout << f[i] << " ";
  }
  //std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "AVX" << std::endl;

  _asm {
    lea edx, qw1
    lea esi, qw2
    vmovups	ymm0, [esi]
    vmulpd	ymm0, ymm0, [edx]
    vmovups[edi], ymm0
  }

  printf("%s\n", "Summing elements of vectors c + d :\n");
  for (int i = 0; i < 4; i++)
  {
    printf("%f ", c[i]);
  }
  std::cout << std::endl;

  //---------------------------------------------------------------5---------------------------------------------------------------------------------------/

  //---DVECCCCCCCC////
  std::cout << "F64VEC8: " <<std::endl;
  F64vec4 A[25], B[25], C[25];
  for (size_t i = 0; i < 25; i++)
  {
    C[i] = A[i] * B[i];
    printf("%f ", c[i]);
  }

  _asm {
    movups	xmm0, a128
    movups	xmm1, b128
    pminub	xmm0, xmm1
    movups	a128, xmm0
  }

  /*printf("\n%s\n", "Comparing elements :");
  for (int i = 0; i < 16; i++)
  {
    printf("( %d , %d) ; ", a128[i], b128[i]);
  }*/

  printf("\n%s\n", "Minimum elements :");
  for (int i = 0; i < 16; i++)
  {
    printf("%d ", a128[i]);
  }
  std::cout << std::endl;

  std::cout << "_mm_add_pi8" << std::endl;

  char* qw6;
  __m64* p1 = (__m64*) qw1;
  __m64* p2 = (__m64*) qw2;
  __m64* p3;
  p3 = &(_mm_add_pi8(*(__m64*) qw1, *(__m64*) qw2));
  qw6 = (char*)(p3);
  for (int i = 0; i < 8; i++)
  {
    std::cout << qw6[i] << " ";
  }

  std::cout << std::endl;

  std::cout << "__mm128:" << std::endl;

  float temp1[]  = { 1.1,1.2,1.3,14.5,3.1,5.2,2.3,3.4 };
  float temp2[]  = { 1.2,2.3,3.4,3.5,1.2,2.3,4.2,2.2 };
  float temp3[8];
  __m128 m, *m_result;
  __m128 arr1 = _mm_load_ps(temp1);
  __m128 arr2 = _mm_load_ps(temp2);

  m = _mm_mul_ps(arr1, arr2); //umnojenie
  _mm_store_ps(temp3, m);
  for (int i = 0; i < 4; i++)
  {
    std::cout << temp3[i] << std::endl;
  }

  
  std::cout << "__mm256:" << std::endl;

  __m256 ymm0, ymm1, ymm3;
    ymm0 = _mm256_set_ps(1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0, -1.0);
  ymm1 = _mm256_set_ps(1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 13.0, 15.0);

  ymm3 = _mm256_add_ps(ymm0, ymm1);

  _mm256_storeu_ps(temp3, ymm3);
  for (int i = 0; i < 8; i++)
  {
    std::cout << temp3[i] << std::endl;
  }
  

  








  system("pause");

  return 0;
}