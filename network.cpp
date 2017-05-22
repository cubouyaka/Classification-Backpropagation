#include "network.h"


Network::Network(int _nb_layers, int _nb_neurons) {

  nb_layers = _nb_layers;
  nb_neurons = _nb_neurons;
  network = new Neuron*[nb_layers];
  for(int x = 0; x < nb_layers; x++) {
    network[x] = new Neuron[nb_neurons];
    for(int y = 0; y < nb_neurons; y++)
      network[x][y].state = 0;
  }
  weight = new int**[nb_layers];
  for(int i = 0; i < nb_layers; i++){
    weight[i] = new int*[nb_neurons];
    for(int j = 0; j < nb_neurons; j++){
      weight[i][j] = new int[nb_neurons];
      for(int l = 0; l < nb_neurons; l++)
	weight[i][j][l] = 0;
    }
  }
}

Network::~Network(){
  for (int i = 0; i < nb_layers; i++)
    delete[] network[i];
  delete[] network;
}

void Network::askInput(){
  for(int i = 0; i < nb_layers; i++){
    cout << "State value of neuron n-"<<i<<" :\n";
    cin >> network[0][i].state;
    network[0][i].output = network[0][i].state;
    cout <<endl;
  }
}

//calcul the weight input sum of i-th neuron in the l-th layer
int Network::weightInputSum(int l, int i){
  int result = 0;
  for(int j = 0; j < nb_neurons; j++)
    result += (weight[l-1][j][i] * network[l-1][j].output);
  
  return result;
}

//calcul the output signal of i-th neuron in the l-th layer
int Network::OutputSignal(int l, int i){
  int result = 0;
  
  return result;
}
