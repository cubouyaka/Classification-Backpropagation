#include "network.h"

int main(){
  
  int nb_layers = 3;
  int nb_neurons = 4;
  
  
  Network network(nb_layers,nb_neurons);
  network.askInput();
  cout << network.weightInputSum(1,0);
    
  return 0;
}
