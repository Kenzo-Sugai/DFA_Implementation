#include <iostream>

struct direction {

    int a, b;

};

class DFA {

    public:

        std::string *states;
        direction *automato;
        std::string word;

        DFA(std::string word);
        bool checkWord(std::string word);
        int getLast(std::string proximo, int i);
};

DFA::DFA(std::string word){

    this->word = word;

    int n = word.size();

    this->states = new std::string[n+1];
    this->automato = new direction[n+1];

    std::string anterior = "eps";
    std::string proximo = "";
    std::string back = "";

    for(int i = 0; i < n; i++){

        states[i] = anterior;
        proximo += word[i];
        back = proximo;

        if(word[i] == 'a'){

            back += 'b';

            automato[i] = {i+1, getLast(back, i)};

        }
        if(word[i] == 'b'){

            back += 'a';

            automato[i] = {getLast(back, i), i+1};

        }

        if(i == n - 1){

            automato[i+1] = {i+1, i+1};
            states[i+1] = word; 

        }

        anterior = proximo;

    }

}

int DFA::getLast(std::string error, int n){

    int i = 0;

    std::string aux = ""; 
    
    aux += error.back();
    error.pop_back();

    while(aux == this->states[i+1] && i <= n){
        aux = error.back() + aux;
        error.pop_back(); 
        i++;
    }

    return i;

}

bool DFA::checkWord(std::string str){

    int state = 0;

    for(int i = 0; i < str.size(); i++){

        if(str[i] == 'a') state = this->automato[state].a;
        if(str[i] == 'b') state = this->automato[state].b;

    }

    return (this->states[state] == this->word);

}

int main(){

    std::string word, str;
    int testes, a, b;

    std::cin >> word;

    std::cin >> testes;

    DFA *turing = new DFA(word);

    for(int i = 0; i <= word.size(); i++){
        a = turing->automato[i].a;
        b = turing->automato[i].b;
        std::cout << turing->states[i] << " ";
        std::cout << turing->states[a] << " ";
        std::cout << turing->states[b] << std::endl;
    }

    while(testes--){

        std::cin >> str;
        std::cout << turing->checkWord(str) << std::endl;

    }

}
