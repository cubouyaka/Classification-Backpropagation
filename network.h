#include <fstream>
#include <iostream>
#include "neuron.h"
#include <cstdlib>
#include <ctime>
using namespace std;

class Network {

  Neuron ** network;
  double *** weight;
  int nb_layers;
  int nb_neurons; //the number of neurons per layer

 public : 

  //---------CONSTRUCTORS----------
  Network(int _nb_layers, int _nb_neurons);

  //---------DESTRUCTOR-----------
  ~Network();

  //---------METHODS--------------
  void askInput();
  int weightInputSum(int i, int j);
  int OutputSignal(int i, int j); //is the function f (page 30)


};
