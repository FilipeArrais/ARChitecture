//g++ -std=c++17 -Wall -Wextra -O2 "nova_formula.cpp" -lm
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

#define MOD 1000000007

int mod_abs(int a) {
 return ((a % MOD) + MOD) % MOD;
}

void atualizar_map(std::map<int, int> &atual, int soma, int nova_altura, int altura_bloco, long &num_combinacoes){
    map <int, int>:: iterator it = atual.find(nova_altura);
    
    if(it != atual.end())
        atual[nova_altura] = soma + it->second;
    
    else
        atual[nova_altura] = soma;

    //novas solucões
    if(nova_altura < altura_bloco)
        num_combinacoes += soma;
}

long contar_arco(int num_blocos, int altura_bloco, int altura_parede){
    //memoria sobre as iterações anteriores
    std::map <int, map <int, int> > memoria_alturas_subir;
    std::map <int, map <int, int> > memoria_alturas_descer;

    //variaveis auxiliares  
    std::map <int, int>:: iterator it;
    std::map <int, int>:: reverse_iterator rit;  
    int altura_atual, i = 0;
    long num_combinacoes = 0;

    //primeiro bloco
    std::map <int, int> lista_alturas = map <int, int>();
    
    //iterar os casos possiveis
    for(i = 1; i < altura_bloco; i++){

        //nao ultrapassou a altura maxima
        if(i <= altura_parede)
            lista_alturas[i] = 1;

        //altura ultrapassada
        else
            break;
    }

    num_combinacoes += lista_alturas.size();

    memoria_alturas_subir[0] = lista_alturas;
    memoria_alturas_descer[0] = std::map <int, int>();

    //blocos restantes
    for(i = 1; i < num_blocos; i++){
        //lista anterior de alturas
        std::map <int, int> lista_alturas_ant_subir = memoria_alturas_subir[i - 1];
        std::map <int, int> lista_alturas_ant_descer = memoria_alturas_descer[i - 1];
        
        //inicializar lista atual de alturas
        std::map <int, int> lista_alturas_atual_subir = std:: map <int, int>();
        std::map <int, int> lista_alturas_atual_descer = std:: map <int, int>();

        //iterar nas alturas anteriores
        for(it = lista_alturas_ant_subir.begin(); it != lista_alturas_ant_subir.end(); it++){
            altura_atual = it->first;

            //testar o primeiro, caso seja invalido nao vale a pena testar os outros
            if((altura_atual + 1 > altura_parede) || ((altura_atual + 1 - (altura_bloco - 1)) > ((num_blocos - i - 1) * (altura_bloco - 1))))
                break;
            
            //valido
            else
                atualizar_map(lista_alturas_atual_subir, it->second, altura_atual + 1, altura_bloco, num_combinacoes);
                
            //fazer todas as combinacoes possiveis
            //subir
            for(int j = 2; j < altura_bloco; j++){
                if((altura_atual + j > altura_parede) || ((altura_atual + j - (altura_bloco - 1)) > ((num_blocos - i - 1) * (altura_bloco - 1))))
                    break;
                
                //valido
                else
                    atualizar_map(lista_alturas_atual_subir, it->second, altura_atual + j, altura_bloco, num_combinacoes);
            }
        }

        for(rit = lista_alturas_ant_subir.rbegin(); rit != lista_alturas_ant_subir.rend(); rit++){
            altura_atual = rit -> first;
            int j = -1;

            if(altura_atual + j <= 0){
                break;
            }

            else if((altura_atual + j - (altura_bloco - 1)) > ((num_blocos - i - 1) * (altura_bloco - 1))){}

            //valido
            else
                atualizar_map(lista_alturas_atual_descer, rit->second, altura_atual + j, altura_bloco, num_combinacoes);
                
            //fazer todas as combinacoes possiveis
            //descer
            for(j = -2; j > -altura_bloco; j--){
                if(altura_atual + j <= 0){
                    break;
                }

                else if((altura_atual + j - (altura_bloco - 1)) > ((num_blocos - i - 1) * (altura_bloco - 1))){}

                //valido
                else
                    atualizar_map(lista_alturas_atual_descer, rit->second, altura_atual + j, altura_bloco, num_combinacoes);
            }
        }

        //iterar nas alturas anteriores
        for(rit = lista_alturas_ant_descer.rbegin(); rit != lista_alturas_ant_descer.rend(); rit++){
            altura_atual = rit -> first;
            int j = -1;

            if(altura_atual + j <= 0){
                break;
            }

            else if((altura_atual + j - (altura_bloco - 1)) > ((num_blocos - i - 1) * (altura_bloco - 1))){}

            //valido
            else
                atualizar_map(lista_alturas_atual_descer, rit->second, altura_atual + j, altura_bloco, num_combinacoes);

            //fazer todas as combinacoes possiveis
            //descer
            for(int j = -2; j > -altura_bloco; j--){
                if(altura_atual + j <= 0){
                    break;
                }
                
                else if((altura_atual + j - (altura_bloco - 1)) > ((num_blocos - i - 1) * (altura_bloco - 1))){}

                //valido
                else
                    atualizar_map(lista_alturas_atual_descer, rit->second, altura_atual + j, altura_bloco, num_combinacoes);
            }
        }

        //atualizar memoria
        memoria_alturas_subir[i] = lista_alturas_atual_subir;
        memoria_alturas_descer[i] = lista_alturas_atual_descer;
    }

    i--;

    return num_combinacoes;
}

int main() {
  int num_casos, num_blocos, altura_bloco, altura_parede;
  cin >> num_casos;

  for(int _ = 0; _ < num_casos; _++){
    cin >> num_blocos >> altura_bloco >> altura_parede;
    if(num_blocos < 3)
      cout << "0\n"; 
    else
      cout << mod_abs(contar_arco(num_blocos - 2, altura_bloco, altura_parede - altura_bloco)) << "\n";
  }

  return 0;
}