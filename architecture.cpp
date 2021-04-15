//g++ -std=c++17 -Wall -Wextra -O2 "architecture.cpp" -lm
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;


bool consegue_terminar(int altura_atual, int altura_bloco, int incremento, int blocos_restantes){
  //nao existem blocos suficientes para chegar ao 0
  if(altura_atual + incremento > (blocos_restantes * (altura_bloco - 1))){
    //nao continuar
    return false;
  }

  //existem blocos de mais entao vai acabar a baixo de 0
  else if(0 > altura_atual + incremento - (blocos_restantes)){          
    //nao continuar
    return false;
  }

  return true;
}

int contar_arco(int num_blocos, int altura_bloco, int altura_parede){
  //memoria sobre as iterações anteriores
  map <int, set<int>> memoria_alturas_subir;
  map <int, set<int>> memoria_alturas_descer;

  int num_combinacoes = 0;

  //primeiro bloco
  set<int> lista_alturas = set<int>();
  
  //iterar os casos possiveis
  for(int i = 1; i < altura_bloco; i++){

    //nao ultrapassou a altura maxima
    if(i <= altura_parede){
      //cout << "altura: " << i << " altura parede: " << altura_parede << "\n";
      num_combinacoes++;
      lista_alturas.insert(i);
    }
    //altura ultrapassada
    else
      break;
  }

  memoria_alturas_subir[0] = lista_alturas;
  memoria_alturas_descer[0] = set<int>();

  //blocos restantes
  for(int i = 1; i < num_blocos; i++){
    cout << "i: " << i << "\n";

    //lista atual de alturas
    set<int> lista_alturas_ant_subir = memoria_alturas_subir[i - 1];
    set<int> lista_alturas_ant_descer = memoria_alturas_descer[i - 1];
    
    set<int> lista_alturas_atual_subir = memoria_alturas_subir[i];
    set<int> lista_alturas_atual_descer = memoria_alturas_descer[i];

    //iterar nas alturas anteriores
    for(set<int>:: iterator it = lista_alturas_ant_subir.begin(); it != lista_alturas_ant_subir.end(); it++){
      int altura_atual = *it;
      cout << "altura_atual: " << altura_atual << "\n";

      //fazer todas as combinacoes possiveis
      //subir
      for(int j = 1; j < altura_bloco; j++){
        
        if((altura_atual + j > altura_parede) || !consegue_terminar(altura_atual, altura_bloco, j, num_blocos - 1))
          //nao continuar
          break;
        
        //valido
        else{
          num_combinacoes++;
          lista_alturas_atual_subir.insert(*it + j);
        }
      }
    }

    for(set<int>:: iterator it = lista_alturas_ant_subir.begin(); it != lista_alturas_ant_subir.end(); it++){
      int altura_atual = *it;

      //fazer todas as combinacoes possiveis
      //descer
      for(int j = -1; j > -altura_bloco; j--){
        
        if((altura_atual + j < 0) || !consegue_terminar(altura_atual, altura_parede, j, num_blocos - i))
          //nao continuar
          break;    

        //valido
        else{
          num_combinacoes++;
          lista_alturas_atual_descer.insert(*it + j);
        }
      }
    }

    //iterar nas alturas anteriores
    for(set<int>:: iterator it = lista_alturas_ant_descer.begin(); it != lista_alturas_ant_descer.end(); it++){
      int altura_atual = *it;

      //fazer todas as combinacoes possiveis
      //descer
      for(int j = -1; j > -altura_bloco; j--){
        
        if((altura_atual + j < 0) || !consegue_terminar(altura_atual, altura_bloco, j, num_blocos - i))
          //nao continuar
          break;
        
        //valido
        else{
          num_combinacoes++;
          lista_alturas_atual_descer.insert(*it + j);
        }
      }
    }

    //atualizar memoria
    memoria_alturas_subir[i] = lista_alturas_atual_subir;
    memoria_alturas_descer[i] = lista_alturas_atual_descer;
  
  }

  return num_combinacoes;
}

int resolver(int num_blocos, int altura_bloco, int altura_parede){
  int total = 0;

  for(int i = 3; i <= num_blocos; i++){
      total += contar_arco(i - 2, altura_bloco, altura_parede - altura_bloco);
  }
  return total;
}

int main() {
  int num_casos, num_blocos, altura_bloco, altura_parede;
  cin >> num_casos;

  for(int _ = 0; _ < num_casos; _++){
    cin >> num_blocos >> altura_bloco >> altura_parede;
    if(num_blocos < 3)
      cout << "solucao: 0\n"; 
    else
      cout << "solucao: " << resolver(num_blocos, altura_bloco, altura_parede) << "\n";
  }

  return 0;
}