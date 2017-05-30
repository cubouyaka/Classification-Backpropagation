#include "network.h"


Network::Network() {
  nb_layers = 0;
  nb_neurons = 0;
}

Network::~Network(){
  for (int i = 0; i < nb_layers; i++)
    delete[] network[i];
  delete[] network;
}

void Network::initialize() {

  srand (static_cast <unsigned> (time(0)));
  double a = 0.3;

  network = new Neuron*[nb_layers];
  for(int x = 0; x < nb_layers; x++) {
    network[x] = new Neuron[nb_neurons];
    for(int y = 0; y < nb_neurons; y++)
      network[x][y].state = 0;
  }
  weight = new double**[nb_layers];
  for(int i = 0; i < nb_layers; i++){
    weight[i] = new double*[nb_neurons];
    for(int j = 0; j < nb_neurons; j++){
      weight[i][j] = new double[nb_neurons];
      for(int l = 0; l < nb_neurons; l++)
	weight[i][j][l] = -a + ((double)rand() / RAND_MAX)*(2*a);
    }
  }
}

bool Network::exist(char * name){
  ifstream file(name);
  if(file.good()){
    file.close();
    return true;
  }else{
    cout << "\""<< name << "\"" << " doesn't exist, retry !" << endl;
    return false;
  }
}

void Network::askInput(){
  //ASK FILE
  char f[100];
  ifstream file;
  int expected_class = 0;
  //while the input file is not correct, we ask the user to choose one
  do {
    cout << "Choose a correct input file in the current folder : " << endl;
    cin >> f;
  }while(!exist(f));
  file.open(f, ios::in);
  
  file >> nb_layers; //set the number of layers
  cout << "Number of layers : " << nb_layers<<endl;
  file >> nb_neurons; //set the number of neurons as input
  cout << "Number of Neurons : " << nb_neurons<<endl<<endl;

  this->initialize();

  loadInput(&file);
  this->training(expected_class);

  expected_class ++;

  file.close();
  /* ASK MANUAL
     for(int i = 0; i < nb_layers; i++){
     cout << "State value of neuron n-"<<i<<" :\n";
     cin >> network[0][i].state;
     network[0][i].output = network[0][i].state;
     }
  */
}

void Network::loadInput(ifstream * file){
  int c = 0;
  int value = 0;
  char delimiter;
  cout <<right<<std::setw(5)<<"\033[0;32m"<<"--INPUT VALUES--\n";
  while((*file >> value >> delimiter) && (delimiter == ',')){
    network[0][c].state = value;
    cout << network[0][c].state<<" - ";
    c++;
  }
  network[0][c].state = value;
  cout << network[0][c].state << endl;
}

//calcul the weight input sum of i-th neuron in the l-th layer
double Network::weightInputSum(int l, int i){
  double result = 0;
  for(int j = 0; j < nb_neurons; j++)
    result += (weight[l-1][j][i] * network[l-1][j].output);
  
  return result;
}

//calcul the output signal of i-th neuron in the l-th layer
double Network::outputSignal(int l, int i){
  double slope = 1;
  return (1 / (1+exp(-(weightInputSum(l,i) - network[l][i].threshold)/slope)));
}

void Network::training(int e_c){
  //TODO
}
