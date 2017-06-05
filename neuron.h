class Neuron {

 public:

  double state;
  double output;
  int threshold;

  //---------CONSTRUCTORS----------
  Neuron(){
    state = 0;
    output = 0;
    threshold = 0;
  } //default constructor
  
  Neuron(double _state,double _output, int _threshold) {
    state = _state;
    output = _output;
    threshold = _threshold;
  } 

  //---------DESTRUCTOR-----------
  ~Neuron(){}

  //---------METHODS--------------
};
