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

int mod_add(int a, int b) {
    return (mod_abs(a) + mod_abs(b)) % MOD;
}

void atualizar_memoria(int &atual, int soma, int nova_altura, int altura_bloco, int &num_combinacoes){
    atual = mod_add(atual, soma);

    //novas solucões
    if(nova_altura < altura_bloco)
        num_combinacoes = mod_add(num_combinacoes, soma);
}

int get_altura_max(int num_blocos, int altura_bloco, int altura_parede){
    
    int temp = num_blocos * (altura_bloco - 1);
    if(temp < altura_parede)
        return temp;

    return altura_parede;    
}

int contar_arco(int num_blocos, int altura_bloco, int altura_parede){
    altura_parede = get_altura_max(num_blocos, altura_bloco, altura_parede - altura_bloco);

    //memoria sobre as iterações anteriores
    std::vector <vector <int> > memoria_alturas_subir (altura_parede + 1, vector<int>(num_blocos));
    std::vector <vector <int> > memoria_alturas_descer (altura_parede + 1, vector<int>(num_blocos));

    //variaveis auxiliares  
    int i = 0, num_combinacoes = 0;
    //primeiro bloco
    
    //iterar os casos possiveis
    for(i = 1; i < altura_bloco; i++){

        //nao ultrapassou a altura maxima
        if(i <= altura_parede){
            memoria_alturas_subir[i][0] = 1;
            num_combinacoes++;
        }
        //altura ultrapassada
        else
            break;
    }

    //blocos restantes
    for(i = 1; i < num_blocos; i++){ 
        //iterar nas alturas anteriores
        for(int k = 1; k <= get_altura_max(i, altura_bloco, altura_parede); k++){
            if(memoria_alturas_subir[k][i - 1] != 0){
                int j = 1;

                //testar o primeiro, caso seja invalido nao vale a pena testar os outros
                if((k + j > altura_parede) || ((k + j - (altura_bloco - 1)) > ((num_blocos - i - 1) * (altura_bloco - 1))))
                    break;

                //valido
                else
                    atualizar_memoria(memoria_alturas_subir[k + j][i], memoria_alturas_subir[k][i - 1], k + 1, altura_bloco, num_combinacoes);

                //fazer todas as combinacoes possiveis
                //subir
                for(j = 2; j < altura_bloco; j++){

                    if((k + j > altura_parede) || ((k + j - (altura_bloco - 1)) > ((num_blocos - i - 1) * (altura_bloco - 1))))
                        break;
                    
                    //valido
                    else
                        atualizar_memoria(memoria_alturas_subir[k + j][i], memoria_alturas_subir[k][i - 1], k + j, altura_bloco, num_combinacoes);
                }
            }
        }

        for(int k = get_altura_max(i, altura_bloco, altura_parede); k >= 1; k--){
            if(memoria_alturas_subir[k][i - 1] != 0){
                int j = -1;

                if(k + j <= 0){
                    break;
                }

                else if((k + j - (altura_bloco - 1)) > ((num_blocos - i - 1) * (altura_bloco - 1))){}

                //valido
                else
                    atualizar_memoria(memoria_alturas_descer[k + j][i], memoria_alturas_subir[k][i - 1], k + j, altura_bloco, num_combinacoes); 

                //fazer todas as combinacoes possiveis
                //descer
                for(j = -2; j > -altura_bloco; j--){
                    if(k + j <= 0){
                        break;
                    }

                    else if((k + j - (altura_bloco - 1)) > ((num_blocos - i - 1) * (altura_bloco - 1))){}

                    //valido
                    else
                        atualizar_memoria(memoria_alturas_descer[k + j][i], memoria_alturas_subir[k][i - 1], k + j, altura_bloco, num_combinacoes);
                }
            }
        }

        //iterar nas alturas anteriores
        for(int k = get_altura_max(i, altura_bloco, altura_parede); k >= 1; k--){
           if(memoria_alturas_descer[k][i - 1] != 0){
                int j = -1;

                if(k + j <= 0){
                    break;
                }

                else if((k + j - (altura_bloco - 1)) > ((num_blocos - i - 1) * (altura_bloco - 1))){}

                //valido
                else
                    atualizar_memoria(memoria_alturas_descer[k + j][i], memoria_alturas_descer[k][i - 1], k + j, altura_bloco, num_combinacoes);

                //fazer todas as combinacoes possiveis
                //descer
                for(int j = -2; j > -altura_bloco; j--){
                    if(k + j <= 0){
                        break;
                    }
                    
                    else if((k + j - (altura_bloco - 1)) > ((num_blocos - i - 1) * (altura_bloco - 1))){}

                    //valido
                    else
                        atualizar_memoria(memoria_alturas_descer[k + j][i], memoria_alturas_descer[k][i - 1], k + j, altura_bloco, num_combinacoes);
                }
            }
        }
    }

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
      cout << contar_arco(num_blocos - 2, altura_bloco, altura_parede) << "\n";
  }

  return 0;
}