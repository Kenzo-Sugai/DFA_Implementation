#include <iostream>

using namespace std;

string automato[3][11];

int estado = 0;
int a = 1;
int b = 2;

string erro(string palavra){

    string aux;
    int j = 0;

    palavra.erase(palavra.begin());
 
    while(!palavra.empty()){

      if(automato[estado][palavra.size()] == palavra) return palavra;

      palavra.erase(palavra.begin());

    }

    return "eps";

}

void direcao(string palavra){

    string atual = "", volta;
    int i = 0;

    for(; i < palavra.size(); i++){
        
        if(palavra[i] == 'a'){

            automato[a][i] = automato[estado][i + 1];

            volta = erro(atual + "b");

            automato[b][i] = string(volta);
        
        }
        if(palavra[i] == 'b'){

            automato[b][i] = automato[estado][i + 1];
            

            volta = erro(atual + "a");

            automato[a][i] = string(volta);

        }

        atual += palavra[i];

        cout << automato[estado][i] << " " << automato[a][i] << " " << automato[b][i] << endl;

    }

    automato[a][i] = palavra;
    automato[b][i] = palavra;

    cout << automato[estado][i] << " " << automato[a][i] << " " << automato[b][i] << endl;

}

void criarAutomato(string palavra){

    automato[estado][0] = "";

    for(int i = 0; i < palavra.size(); i++){

        automato[estado][i + 1] = automato[0][i] + palavra[i];

    }

    automato[estado][0] = "eps";

    direcao(palavra);

}

bool verificar(string palavra_teste, string palavra_automato){

    string estado_atual;
    int idx = 0; 

    for(int i = 0; i < palavra_teste.size(); i++){

        if(palavra_teste[i] == 'a') estado_atual = automato[a][idx];
        if(palavra_teste[i] == 'b') estado_atual = automato[b][idx];

        idx = (estado_atual == "eps") ? 0 : estado_atual.size();

        if(estado_atual == palavra_automato) return true;

    }

    return false;

}



int main(){

    string palavra_automato;
    string palavra_teste;
    int testes;

    cin >> palavra_automato;

    criarAutomato(palavra_automato);

    cin >> testes;

    for(int i = 0; i < testes; i++){

        cin >> palavra_teste;

        cout << verificar(palavra_teste, palavra_automato) << endl;

    }

}
