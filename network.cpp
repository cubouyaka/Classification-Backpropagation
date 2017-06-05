#include "network.h"


Network::Network() {
  nb_layers = 0;
  nb_neurons = 0;
  learning_coeff = 1;
  slope = 1;
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
  int nb_input = 306;
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
  while(nb_input > 0){
    loadInput(&file);
    this->training(expected_class);
    expected_class ++;
    nb_input --;
  }

  file.close();
  bool b = true;
  while(b)
    b=askUser();

  /* ASK MANUAL
     for(int i = 0; i < nb_layers; i++){
     cout << "State value of neuron n-"<<i<<" :\n";
     cin >> network[0][i].state;
     network[0][i].output = network[0][i].state;
     }
  */
}

bool Network::askUser(){
  double tmp;
  char answer[10];// = "no";
  for(int i = 0; i < nb_neurons; i++){
    cout << "Enter "<<i<<"-th value of the vector\n";
    cin >> tmp;
    network[0][i].state = tmp;
    network[0][i].output = tmp;
  }
  cout << "Which class do you expect ?\n";
  cin >> tmp;
  this->training(tmp);
  cout << "Belongs to the class number "<<indexClass()<<endl;
  cout << "Do you want to continue ?\n";
  cin >> answer;
  if(!strcmp(answer,"yes") || !strcmp(answer,"y"))
    return true;
  else
    return false;
}

void Network::loadInput(ifstream * file){
  int c = 0;
  int value = 0;
  char delimiter = ',';
  //cout <<right<<std::setw(5)<<"\033[0;32m"<<"--INPUT VALUES--\n";
  cout <<"--INPUT VALUES--\n";
  /*
    while((delimiter == ',')){// && (*file >> value >> delimiter)){
    (*file >> value >> delimiter);
    cout << "delim " << delimiter<<" - value " <<'|'<< value <<'|'<< endl;
    network[0][c].state = value;
    cout << network[0][c].state << " - ";
    c++;
  }
  */
  while(c < nb_neurons-1){
    (*file >> value);
    network[0][c].state = value;
    network[0][c].output = value;
    (*file >> delimiter);
    cout << network[0][c].state << " - ";
    c++;
  }
  (*file >> value);  
  network[0][c].state = value;
  network[0][c].output = value;
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
  return (1 / (1+exp(-(weightInputSum(l,i) - network[l][i].threshold)/slope)));
}

void Network::training(int e_class){
  int i,j,l;
  for(i = 1; i < nb_layers; i++){
    for(j = 0; j < nb_neurons; j++){
      //cout << "i "<<i<<" j "<<j<<endl;
      network[i][j].output = outputSignal(i,j);
      //cout << network[i][j].output << endl;
    }
  }
  /*
  cout << network[nb_layers-1][0].output << " - ";
  cout << network[nb_layers-1][1].output << " - ";
  cout << network[nb_layers-1][2].output << " - ";
  cout << network[nb_layers-1][3].output << " - ";
  cout << indexClass()<<endl;
  */

  if(indexClass() != e_class){
    for(l = nb_layers-1; l > 0; l--){
      for(i = 0; i < nb_neurons; i++){
	for(j = 0; j < nb_neurons; j++){
	  //cout << "avant : l "<<l<<" i "<<i<<" j "<<j<<endl;
	  weight[l][j][i] += learning_coeff*network[l-1][i].output*d(l,j,e_class);
	}
      }
    }
  }
}

double Network::d(int i_layer, int i, int e_class){
  double result = 0;
  if(i_layer == nb_layers-1){ //for element in output layer
    if(i == e_class)
      result = (1-network[i_layer][i].output)*f_prime(i_layer,i);
    else
      result = (-network[i_layer][i].output)*f_prime(i_layer,i);
  }else{ //for element in hidden layer
    double sum = 0;
    for(int j = 0; j < nb_neurons ; j++)
      sum += d(i_layer+1,j,e_class)*weight[i_layer+1][i][j];
    result = (1/slope)*network[i_layer][i].output*(1-network[i_layer][i].output)*sum;
  }
  return result;
}

double Network::f_prime(int i_layer, int i){
  double k = 1/slope;
  return k*network[i_layer][i].output*(1-network[i_layer][i].output);
}

int Network::indexClass(){
  int j = 0;
  double tmp = 0;
  for(int i = 0; i < nb_neurons; i++){
    if(network[nb_layers-1][i].output > tmp){
      tmp = network[nb_layers-1][i].output;
      j = i;
    }
  }
  return j;
}
