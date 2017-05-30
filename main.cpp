#include "network.h"

int main(){
  /* 
  int nb_layers = 3;
  int nb_neurons = 4;  
  Network network(nb_layers,nb_neurons);
*/

  Network network;

  network.askInput(); //ask the input file and start the algorithm
  /*cout << network.weightInputSum(1,0);
  cout << endl;
  cout << network.outputSignal(1,0);
  */
  return 0;
}
