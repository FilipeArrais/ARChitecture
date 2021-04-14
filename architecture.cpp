#include <iostream>
#include <map>
#include <set>
using namespace std;

int contar_arco(int num_blocos, int altura_bloco, int altura_parede){
  map <int, set<int>> altura_atual;
  int num_combinacoes = 0;
  bool acabou = false;

  for(int i = 0; num_blocos; i++){
    altura_atual.insert(pair<int, set<int>> (i, set<int>()));
    if(i == 0){
      for(int j = 0; j < (altura_bloco - 1) * 2; j++){
        
        if(altura_atual > altura_parede){
        }

        else if(((num_blocos - i) * (altura_bloco - 1)) >= altura_atual){
        }

        else if(((num_blocos - i) * (altura_bloco - 1)) < 0){
        }

        if(i == num_blocos - 1){
        }

        else{
          num_combinacoes++;
        }
      }
    }
    else{
      set<int>:: iterator it = altura_atual.find(i).begin();
      for(int k: altura_atual.find(i)){

      }
    }
  }

  return num_combinacoes;
}

int resolver(int num_blocos, int altura_bloco, int altura_parede){
  int total = 0;

  for(int i = 3; i <= num_blocos; i++){
      total += contar_arco(i - 2, altura_bloco, altura_parede);
  }

  return total;
}

int main() {
  int num_casos, num_blocos, altura_bloco, altura_parede;
  cin >> num_casos;

  for(int _ = 0; _ < num_casos; _++){
    cin >> num_blocos >> altura_bloco >> altura_parede;
    cout << resolver(num_blocos, altura_bloco, altura_parede);  
  }

  return 0;
}