#include <iostream>
#include <vector>
#include <map>
#include <string>

typedef std::pair<std::string, std::string> direction; // typedef do automato

class DFA {

    public:

        std::string accepted; // estado de aceitacao
        std::map<std::string, direction> automato; // map de estados

        DFA(std::string word); // construtor
        bool verifyAutomato(std::string word); // verificador de palavra
        std::string getLast(std::string last); // retonar o estado
};

std::string DFA::getLast(std::string last){

    std::string proximo = "";
    std::string anterior = "";

    // pegar o ultima letra a ser inserida

    proximo += last.back();
    last.pop_back();
    
    // enquanto o estado existir, continue procurando até não achar mais

    while(this->automato.find(proximo) != this->automato.end()){

        anterior = proximo;
        proximo = last.back() + proximo;
        last.pop_back();

    }


    if(anterior == "") return "eps"; // se não achar estados, retone oa primeiro

    return anterior; // retornar o estado mais próximo

}

DFA::DFA(std::string word){

    this->accepted = word;
    
    std::string anterior = "eps";
    std::string proximo = "";
    std::string temp = "";
    std::string last =  "";

    for(int i = 0; i < word.size(); i++){
        
        proximo += word[i];

        if(word[i] == 'a'){ // letra a para continuar

            temp = anterior;
            temp += "b";

            this->automato[anterior] = {proximo, ""}; // setando estado

            last = getLast(temp); // pegando estado anterior mais proximo

            this->automato[anterior] = {proximo, last}; // atualizando estado

        }
        if(word[i] == 'b'){ // letra b para continuar

            temp = anterior;
            temp += "a";

            this->automato[anterior] = {"", proximo}; // setando estado

            last = getLast(temp); // pegando estado anterior mais proximo

            this->automato[anterior] = {last, proximo}; // atualizando estado

        }

        std::cout << anterior << " " << min(proximo, last) << " " << max(proximo, last) << std::endl; // output

        // Se for o ultimo input, ele será infinito

        if(i == word.size() - 1){ 
            
            this->automato[proximo] = {proximo, proximo};

            std::cout << proximo << " " << proximo << " " << proximo << std::endl; // output

        }

        anterior = proximo; // troca os parametros de estado

    }

}

bool DFA::verifyAutomato(std::string word){

    std::string state = "eps"; // estado comeca no eps

    // percorrer a string em complexidade linear

    for(int i = 0; i < word.size(); i++){

        if(word[i] == 'a') state = this->automato[state].first; // se for a, ir para o estado "a"
        if(word[i] == 'b') state = this->automato[state].second; // se for b, ir para o estado "b"

    }

    // retorne os casos

    if(state == this->accepted) return true;

    return false;


}

int main(){

    // declaracao de variaveis

    std::string automato, check;
    int qntTeste;

    // inputs

    std::cin >> automato;
    std::cin >> qntTeste;

    // instanciar a classe DFA

    DFA *gramatica = new DFA(automato);

    // laco para verificar todos os casos

    while(qntTeste--){

        std::cin >> check;

        std::cout << gramatica->verifyAutomato(check) << std::endl;

    }

}
