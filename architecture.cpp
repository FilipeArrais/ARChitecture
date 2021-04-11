#include <iostream>
using namespace std;

void resolver(int n, int h, int H){
  //do something
  int b = 2;
  cout << "resolvido";
}

int main() {
  int num_casos, num_blocos, altura_bloco, altura_parede;
  cin >> num_casos;

  for(int _ = 0; _ < num_casos; _++){
    cin >> num_blocos >> altura_bloco >> altura_parede;
    resolver(num_blocos, altura_bloco, altura_parede);  
  }

  return 0;
}