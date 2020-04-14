#include <omp.h>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <list>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <time.h>
//#include <windows.h>
using namespace std;

void func()
{
  for (int i = 0; i < 1000000; i++)
    rand();
}

void someFunc(int i) {

  std::cout << "someFunc" << i << std::endl;
}

void someFunc2(int i) {
  std::cout << "someFunc2:" << i << std::endl;
 
}


int main()
{
  const int LEN = 1000;
  list <int> l1;
  list <int> l2;
  vector <int> mass1, mass2, mass3;
  omp_set_num_threads(2);
  cout << omp_get_num_procs() << endl;
  int i = 0;

  //std::cout << "100 chisel" << std::endl;


  omp_lock_t my_lock;
  omp_init_lock(&my_lock);

#pragma omp parallel num_threads(2)
  {
    int tid = omp_get_thread_num();

    while (!omp_test_lock(&my_lock))
      printf_s("Thread %d - failed to acquire simple_lock\n",
        tid);

    printf_s("Thread %d - acquired simple_lock\n", tid);

    printf_s("Thread %d - released simple_lock\n", tid);
    omp_unset_lock(&my_lock);
  }

  omp_destroy_lock(&my_lock);

  omp_destroy_lock(&my_lock);





  //------------------------------------------single and barrier-----------------------------------------------//

#pragma omp parallel
  {
    int n = 1000;
    for (int i = 0; i < n; i++) {
      someFunc(i);
    }

    //Исполнение кода заблокируется до тех пор, пока все нити не пройдут цикл
#pragma omp barrier 
#pragma omp single //ubrat' dlya demonstracii (esli uberem to budut 2 delat', a tak 1)

    std::cout << std::endl;
    for (int i = 0; i < 100; i++) {
      someFunc2(i);
    }

  }





#pragma omp parallel
  while (i < 100)
  {

    int tid = omp_get_thread_num();

    i++;     
    cout << "Nomer potoka: "<< tid << "     " << i << std::endl;
    func();
  }
  float t = clock();
  std::cout << std::endl;


#pragma omp parallel sections
  {
#pragma omp section
    {
      for (int i = 0; i < LEN / 2; i++)
      {
        l1.push_front(i);
      }
    }
#pragma omp section
    {
      for (int i = LEN / 2; i < LEN; i++)
      {
        l2.push_front(i);
      }
    }
  }



#pragma omp parallel for
  for (int i = 0; i < LEN; i++)
  {
    l1.push_back(i);
  }
  mass1.resize(2 * LEN);

#pragma omp parallel for
    for (int i = 0; i < LEN; i++)
    {
      mass1[i] = 2 * i;
    }

  //  std::cout << "1000 chisel" << std::endl;
    
/*#pragma omp parallel for
    for (int i = 0; i < LEN; i++)
    {
#pragma omp critical
      {

      int tid = omp_get_thread_num();
    cout << "Nomer potoka: "<< tid << "     " << mass1[i] << std::endl;
        func();
      }
    }*/
    std::cout << std::endl;



  


  inplace_merge(mass1.begin(), mass1.begin() + LEN, mass1.end());
  cout << endl << (clock() - t) / CLOCKS_PER_SEC << endl;
  _getch();
}
