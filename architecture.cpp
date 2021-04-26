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

int mod_add(int a, int b) {
    return (mod_abs(a) + mod_abs(b)) % MOD;
}

int mod_sub(int a, int b) {
  return mod_add(a, -b);
}

int get_altura_max(int num_blocos, int altura_bloco, int altura_parede){
    
    int temp = num_blocos * (altura_bloco - 1);
    if(temp < altura_parede)
        return temp;

    return altura_parede;    
}

int get_largura_max(int num_blocos,int altura_parede){

    if(num_blocos > altura_parede * 2 ){
        return altura_parede*2;
    }

    return num_blocos;
}

int contar_arco(int num_blocos, int altura_bloco, int altura_parede){
    altura_parede = get_altura_max(num_blocos, altura_bloco, altura_parede - altura_bloco);
    num_blocos = get_largura_max(num_blocos, altura_parede);

    //memoria sobre as iterações anteriores
    std::vector <vector <int> > memoria_alturas_subir (altura_parede + 1, vector<int>(num_blocos));
    std::vector <vector <int> > memoria_alturas_descer (altura_parede + 1, vector<int>(num_blocos));

    //variaveis auxiliares  
    int i = 0, altura, soma, num_combinacoes = 0;
    //primeiro bloco
    
    for(i = 1; i < altura_bloco; i++){

        //nao ultrapassou a altura maxima
        if(i <= altura_parede){
            memoria_alturas_subir[i][0] = 1;
            num_combinacoes++;
        }
        //altura ultrapassada
        else{
            break;
        }
            
    }

    //blocos restantes
    for(i = 1; i < num_blocos; i++){ 
        soma = 0;

        //iterar nas alturas anteriores
        for(int k = 1; k <= get_altura_max(i + 1, altura_bloco, altura_parede); k++){

            //testar o primeiro, caso seja invalido nao vale a pena testar os outros
            if((k + 1 > altura_parede) || ((k + 1 - (altura_bloco - 1)) > ((num_blocos - i - 1) * (altura_bloco - 1))))
                break;

            if(k  + 1 < altura_bloco){
                soma = mod_add(soma, memoria_alturas_subir[k][i - 1]);
                num_combinacoes = mod_add(num_combinacoes, soma);
            }
            else
                soma = mod_add(soma, mod_sub(memoria_alturas_subir[k][i - 1], memoria_alturas_subir[k - (altura_bloco - 1) ][i - 1]));

            memoria_alturas_subir[k + 1][i] = soma;                
        }

        soma = 0;
        altura = get_altura_max(i + 1, altura_bloco, altura_parede);
        
        for(int k = altura; k > 1; k--){
            if(altura - k < altura_bloco - 1){
                soma = mod_add(soma, memoria_alturas_subir[k][i - 1]);
                soma = mod_add(soma, memoria_alturas_descer[k][i - 1]);
            }    
            else{
                soma = mod_add(soma, mod_sub(memoria_alturas_subir[k][i - 1], memoria_alturas_subir[k + (altura_bloco - 1) ][i - 1]));
                soma = mod_add(soma, mod_sub(memoria_alturas_descer[k][i - 1], memoria_alturas_descer[k + (altura_bloco - 1) ][i - 1]));
            }
            
            memoria_alturas_descer[k - 1][i] = soma;

            if(k - 1 < altura_bloco)
                num_combinacoes = mod_add(num_combinacoes, soma);
        
        }
    }

    return num_combinacoes;
}

int main() {
    
    ios_base::sync_with_stdio(0);
    cin.tie(0);

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