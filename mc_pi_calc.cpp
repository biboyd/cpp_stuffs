#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;


float CalcPi(int &n_steps){

  srand(static_cast <unsigned> (time(0)));
  float r [n_steps];
  int in_circle = 0;

  for(int i = 0; i < n_steps; ++i){
    float r_x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float r_y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    if (r_x*r_x + r_y*r_y < 1.0){
      in_circle++;
    }
  }

  float pi_approx = 4 * in_circle / static_cast<float>(n_steps);
  return pi_approx;
}

int main(){

  int gamma = static_cast<int>(1e6);

  float pi_approx = CalcPi(gamma);
  cout << pi_approx << endl;

  return 1;
}
