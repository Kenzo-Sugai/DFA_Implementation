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
        int getLast(std::string proximo);
};

DFA::DFA(std::string word){

    this->word = word; // setar palavra na classe

    int n = word.size(); // setar tamanho da palavra

    this->states = new std::string[n+1]; // redimensionar arranjo de estados (vertices)
    this->automato = new direction[n+1]; // redimensionar arranjo de direcoes (arestas)

    std::string anterior = "eps"; // primeiro estado sendo eps
    std::string proximo = ""; // primeiro estado ainda nao captado
    std::string error = ""; // estado errado

    // prenchimento dos arranjos

    for(int i = 0; i < n; i++){

        states[i] = anterior; // estado no indice i sera o passado, ja que arr[0] = "eps"
        error = proximo; // pegar o estado passado para ocorrer o input errado
        proximo += word[i]; // pegar a letra correta para o proximo estado

        // caso a letra correta seja "a"

        if(word[i] == 'a'){

            error += 'b'; // colocar o estado errado como input "b"

            // setar as direcoes como:
            // first => "a" (incrementa indice)
            // second => "b" (chamar metodo para retornar indice)

            automato[i].a = i+1;
            automato[i].b = getLast(error);

        }

        // caso a letra correta seja "b"

        if(word[i] == 'b'){

            error += 'a'; // colocar o estado errado como input "a"

            // setar as direcoes como:
            // first => "a" (chamar metodo para retornar indice)
            // second => "b" (incrementa indice)

            automato[i].a = getLast(error);
            automato[i].b = i+1;

        }

        // ultimo estado sempre sera infito

        if(i == n - 1){

            automato[i+1].a = automato[i+1].b = i+1;
            states[i+1] = word; 

        }

        // seta o anterior igual ao proximo para a proxima iteracao

        anterior = proximo;

    }

}

int DFA::getLast(std::string error){
    
    int n = error.size(); // setar tamanho do estado errado

    std::string errorStates[n+1]; // criar vetor com todos os estados errados 

    errorStates[0] = "eps"; // primeiro estado sendo o vazio
    errorStates[1] = error[n - 1]; // segundo estado sendo o input errado
    
    // programacao dinamica para pegar todos os estados

    for(int i = 2; i <= n; i++){ 
        errorStates[i] = error[n - i] + errorStates[i - 1]; 
    }

    int i = n; // setar iterador como tamanho n

    // percorrer os estados originais e os errados ate encontrar um compativel para o retorno

    for(; errorStates[i] != this->states[i] && i >= 0; i--);
    
    return i; // retornar index do caso de retorno

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
