//g++ -std=c++17 -Wall -Wextra -O2 "architecture.cpp" -lm
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

#define MOD 1000000007

int mod_abs(int a) {
 return ((a % MOD) + MOD) % MOD;
}

bool consegue_terminar(int altura_atual, int altura_bloco, int incremento, int blocos_restantes, bool descer){
  //cout << altura_atual << " " << altura_bloco << " " << incremento << " " << blocos_restantes << "\n";

  //nao existem blocos suficientes para chegar ao 0
  if(altura_atual + incremento - altura_bloco > (blocos_restantes * altura_bloco)){
    //cout << "false1\n";
    //nao continuar
    return false;
  }

  //existem blocos de mais entao vai acabar a baixo de 0
  if(descer && (altura_atual + incremento - blocos_restantes <= 0)){   
    //cout << "false2\n";       
    //nao continuar
    return false;
  }

  return true;
}

void atualizar_map(std::map<int, int> &ant, std::map<int, int> &atual, int altura_atual, int incremento){
  //cout << "atualizar map: " << altura_atual << " " << incremento << " " << atual.size() << "\n";
  map <int, int>:: iterator it;
  int soma = ant[altura_atual];

  it = atual.find(altura_atual + incremento);
  if(it != atual.end()){
    atual[altura_atual + incremento] = soma + it->second;
   // cout << "existe: " << soma << " " << it->second << "\n";
  }
  else{
    atual[altura_atual + incremento] = soma;
  //  cout << "nao existe: " << soma << "\n";
  }

}

long contar_arco(int num_blocos, int altura_bloco, int altura_parede){
  //memoria sobre as iterações anteriores
  std::map <int, map <int, int> > memoria_alturas_subir;
  std::map <int, map <int, int> > memoria_alturas_descer;

  //cout << "num_blocos: " << num_blocos << "\n";
  //int num_combinacoes = 0;
  int altura_atual, i = 0;
  std::map <int, int>:: iterator it;

  //primeiro bloco
  std::map <int, int> lista_alturas = map <int, int>();
  
  //iterar os casos possiveis
  for(int ii = 1; ii < altura_bloco; ii++){

    //nao ultrapassou a altura maxima
    if(ii <= altura_parede){
      //cout << "altura: " << ii << " altura parede: " << altura_parede << "\n";
      //num_combinacoes++;
      lista_alturas[ii] = 1;
    }
    //altura ultrapassada
    else
      break;
  }

  memoria_alturas_subir[0] = lista_alturas;
  memoria_alturas_descer[0] = std::map <int, int>();

/*
  cout << "tamanho 0 (inicio): " << lista_alturas.size() << "\n";
  for(it = lista_alturas.begin(); it != lista_alturas.end(); it++){
    cout << it->first << " ";
  }
  cout << "\n";
  */

  //blocos restantes
  for(i = 1; i < num_blocos; i++){
    //cout << "i: " << i << "\n";

    //lista atual de alturas
    std::map <int, int> lista_alturas_ant_subir = memoria_alturas_subir[i - 1];
    std::map <int, int> lista_alturas_ant_descer = memoria_alturas_descer[i - 1];
    
    std::map <int, int> lista_alturas_atual_subir = std:: map <int, int>();
    std::map <int, int> lista_alturas_atual_descer = std:: map <int, int>();

    //iterar nas alturas anteriores
    for(it = lista_alturas_ant_subir.begin(); it != lista_alturas_ant_subir.end(); it++){
      altura_atual = it->first;
      //cout << "subir: altura_atual: " << altura_atual << "\n";

      //fazer todas as combinacoes possiveis
      //subir
      for(int j = 1; j < altura_bloco; j++){
        //cout << "j1: " << j << "\n";        
        if((altura_atual + j > altura_parede) || !consegue_terminar(altura_atual, altura_bloco - 1, j, num_blocos - i - 1, false)){}
          //nao continuar
        
        //valido
        else{
          atualizar_map(lista_alturas_ant_subir, lista_alturas_atual_subir, altura_atual, j);
        }
        //cout << "j1: valido\n";
      }
    }

    for(it = lista_alturas_ant_subir.begin(); it != lista_alturas_ant_subir.end(); it++){
      altura_atual = it -> first;
      //cout << "descer1: altura_atual: " << altura_atual << "\n";

      //fazer todas as combinacoes possiveis
      //descer
      for(int j = -1; j > -altura_bloco; j--){
        //cout << "j2: " << j << "\n";  
        if((altura_atual + j < 0) || !consegue_terminar(altura_atual, altura_bloco - 1, j, num_blocos - i - 1, true)){}

        //valido
        else{
          atualizar_map(lista_alturas_ant_subir, lista_alturas_atual_descer, altura_atual, j);
        }
        //cout << "j2: valido\n";        
      }
    }

    //iterar nas alturas anteriores
    for(it = lista_alturas_ant_descer.begin(); it != lista_alturas_ant_descer.end(); it++){
      altura_atual = it -> first;
      //cout << "descer2: altura_atual: " << altura_atual << "\n";

      //fazer todas as combinacoes possiveis
      //descer
      for(int j = -1; j > -altura_bloco; j--){
        //cout << "j3: " << j << "\n";  
        if((altura_atual + j < 0) || !consegue_terminar(altura_atual, altura_bloco - 1, j, num_blocos - i - 1, true)){}
        
        //valido
        else{
          atualizar_map(lista_alturas_ant_descer, lista_alturas_atual_descer, altura_atual, j);
        }
        //cout << "j3: valido\n";
      }
    }

    //atualizar memoria
    memoria_alturas_subir[i] = lista_alturas_atual_subir;
    memoria_alturas_descer[i] = lista_alturas_atual_descer;

    /*
    cout << "tamanho 1: " << lista_alturas_atual_subir.size() << "\n";
    for(it = lista_alturas_atual_subir.begin(); it != lista_alturas_atual_subir.end(); it++){
      cout << it->first << " ";
    }
    cout << "\ntamanho 2: " << lista_alturas_atual_descer.size() << "\n";
    for(it = lista_alturas_atual_descer.begin(); it != lista_alturas_atual_descer.end(); it++){
      cout << it->first << " ";
    }
    cout << "\n";
    */
    
  }

  i--;

  //somar num_combinacoes
  long num_combinacoes = 0;
  //cout << "\ntamanho 3: " << i << " " << memoria_alturas_subir[i].size() << "\n";
  for(it = memoria_alturas_subir[i].begin(); it != memoria_alturas_subir[i].end(); it++){
      num_combinacoes += it->second;
  }
  //cout << "tamanho 4: " << i << " " << memoria_alturas_descer[i].size() << "\n";
  for(it = memoria_alturas_descer[i].begin(); it != memoria_alturas_descer[i].end(); it++){
      num_combinacoes += it->second;
  }

  //cout << "num_combinacoes: " << num_combinacoes << "\n";
  return num_combinacoes;
}

long resolver(int num_blocos, int altura_bloco, int altura_parede){
  long total = 0;

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
    else{
      int s = resolver(num_blocos, altura_bloco, altura_parede);
      cout << "solucao: " << mod_abs(s) << "\n";
    }
  }

  return 0;
}