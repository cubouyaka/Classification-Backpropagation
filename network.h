#include <fstream>
#include <iostream>
#include "neuron.h"
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <iomanip>
#include <cstring>

using namespace std;

class Network {

  Neuron ** network;
  double *** weight;
  int nb_layers;
  int nb_neurons; //the number of neurons per layer
  double learning_coeff;
  double slope;

 public : 

  //---------CONSTRUCTORS----------
  Network();

  //---------DESTRUCTOR-----------
  ~Network();

  //---------METHODS--------------
  void initialize();
  void askInput();
  void loadInput(ifstream * file); //load the next input
  bool exist(char * name);

  double weightInputSum(int i, int j);
  double outputSignal(int i, int j); //is the function f (page 30)
  void training(int expected_class);
  double d(int i_layer, int i, int expected_class);
  double f_prime(int i_layer, int i);
  int indexClass();
  bool askUser();


};
