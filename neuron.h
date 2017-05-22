class Neuron {

 public:

  int state;
  int output;

  //---------CONSTRUCTORS----------
  Neuron(){
    state = 0;
    output = 0;
  } //default constructor
  
  Neuron(int _state,int _output) {
    state = _state;
    output = _output;
  } 

  //---------DESTRUCTOR-----------
  ~Neuron(){}

  //---------METHODS--------------
};
