#include <iostream>
#include <fstream>
#include <string>
#include <speechapi_cxx.h>
#include <locale.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <windows.h>

/*
Para as Linhas 17 à 40 e 3009 à 3013 foram utilizados os exemplos
disponibilizados em: https://github.com/icei-pucminas/Sistemas-Inteligentes
*/

using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;

auto autenticacao = SpeechConfig::FromSubscription("958fde7d42b84849b0f2536db51ba545", "brazilsouth"); // DECLARAÇÃO DA AUTENTICAÇÃO DO RECURSO
auto requisicao_textofala = SpeechSynthesizer::FromConfig(autenticacao); // DECLARAÇÃO DO OBJETO DE REQUISIÇÃO DE TEXTO EM FALA DO RECURSO
auto audio_config = AudioConfig::FromDefaultMicrophoneInput(); // DECLARAÇÃO DA ENTRADA DO MICROFONE
auto requisicao_falatexto = SpeechRecognizer::FromConfig(autenticacao, audio_config); // DECLARAÇÃO DO OBJETO DE REQUISIÇÃO DE FALA EM TEXTO DO RECURSO

// PROCEDIMENTO QUE REQUISITA DA API A TRANSFORMAÇÃO DE UM TEXTO EM FALA
void texto_em_fala(string Texto)
{
    setlocale(LC_ALL, "portuguese");
    cout << Texto + "\n";
    requisicao_textofala->SpeakTextAsync(Texto).get(); // REQUISIÇÃO DA SINTETIZAÇÃO DE TEXTO EM FALA
}

// FUNÇÃO QUE REQUISITA DA API O RECONHECIMENTO DE UMA FALA E A TRANSFORMAÇÃO DESSA FALA EM UM TEXTO
string fala_em_texto() {
    setlocale(LC_ALL, "portuguese");
    auto resultado = requisicao_falatexto->RecognizeOnceAsync().get(); // REQUISIÇÃO DO RECONHEIMENTO DE FALA EM TEXTO
    cout << resultado->Text + "\n";
    return resultado->Text; //CONVERSÃO DO RESULTADO DO RECONHECIMENTO EM TEXTO
}




//Função p/ limpar o console/tela
void apaga() {

    system("CLS");
}


//função que contem toda a operação logica do jogo
int jogo() {

char start{};

    std::cout << "\n\t\tThe Hangman!\n\n";
    std::cout << "\t\tby Celine & Hernane\n";
    std::cout << "\t\t_____________    \n";
    std::cout << "\t\t|     |          \n";
    std::cout << "\t\t|     O          \n";
    std::cout << "\t\t|     |          \n";
    std::cout << "\t\t|   / | \\       \n";
    std::cout << "\t\t|  /  |  \\      \n";
    std::cout << "\t\t|    / \\        \n";
    std::cout << "\t\t|   /   \\       \n";
    std::cout << "\t\t|_____________   \n";


    //chamada da integração da função com a API para conversão de texto em fala
    texto_em_fala("\n\n\t\t\tDigite uma letra e pressione enter para iniciar\n\t\t\t");

    // start of the game
    std::cin >> start;

    // set variables to use in game :
    apaga();

    //chamada da integração da função com a API para conversão de texto em fala
    texto_em_fala("\n\n\n\n\n\n\n\n\t\tCarregando o Jogo");
    apaga();


    int attempts{ 6 }; //how many times it takes to guess correctly
    bool correctGuess = false;

    char previousGuess[7]; // array of guess > user can guess
    previousGuess[0] = '\0';


    for (int i = 0; i < 6; i++) {
        previousGuess[i] = '-';
    }
    previousGuess[6] = '\0';
    std::string word;  // word players guesses
    std::string wordList[99]; // array 100 strings


    //utilizando SRAND para selecionar uma palavra aleatoria dentre as 99 disponiveis.
    srand(time(NULL)); // get any random word
    std::ifstream RandomWord; // file reads variable ofstream
    RandomWord.open("word.txt"); //reads from file


    for (int i = 0; i < 99; i++) {
        RandomWord >> wordList[i];
    }

    int randomNum = rand() % 100;
    word = wordList[randomNum];
    //std::cout << word << std::endl;
    //Mostra a Palavra a ser advinhada pelo usuário. Manter com comentário. Usar para testes
    RandomWord.close();

    // word mystry
    std::string MystryWord(word.length(), '*');
    //std::cout << MystryWord << std::endl;

    texto_em_fala("\n\nPARTIDA INICIADA\n\n"); //chamada da integração da função com a API para conversão de texto em fala
    apaga();

    while (attempts >= 0) {
        // reset bool
        correctGuess = false;


        // this loop will keep on running until the statement is true.
        //o loop continuará em execução até que a declaração seja verdadeira.


        //mascará p/ palavra | morango = ******* conforme o usuário acerta, ela remove um * = m*r*ng*.
        std::cout << "\n\n\nPalavra Secreta: ";
        std::cout << MystryWord << std::endl;
        std::cout << "\n\nHa : " << MystryWord.length() << " letras na palavra \n";  std::cout << "voce tem: " << attempts << " tentativas\n";

        //apresentando na letra a letra falada
        if (previousGuess[0] == '\0') {

            std::cout << std::endl;
        }
        else {
            std::cout << "Voce disse " << previousGuess << std::endl;
        }
        texto_em_fala("Fale uma letra");    //chamada da integração da função com a API para conversão de texto em fala
        char oie = fala_em_texto().at(0);
        /*
        chamada da integração da função com a API para conversão de fala em texto
        char oi seleciona o caracter na posição 0 e então armazena na memoria
        */
        texto_em_fala("Analisando..."); //chamada da integração da função com a API para conversão de texto em fala
        char guess;
        guess = oie; // guess irá receber o caracter armazenado em oie para verificar se ele pertence a palavra
        system("CLS");

        //estrutura de repetição que apos validar o caracteres revela a palavra secreta
        for (int i = 0; i < MystryWord.length(); i++) {// is guess correct
            if (word[i] == guess) // does word = guess
            {
                MystryWord[i] = guess;
                correctGuess = true;
            }
        }

        if (word == MystryWord) {
            texto_em_fala("\n\n\tParabens! Voce descobriu a palavra!!!\n");//é apresentado na tela apos descobrir a palavra
            apaga();
            texto_em_fala("A palavra é: " + MystryWord); // API irá falar a palavra secreta
            break;
        }

        if (correctGuess == false)
        {
            /*
            Condição que verifica quando o usuário disser uma letra que não pertence a palavra será alertado e uma tentativa será elimidada
            do contrário, as tentativas permanece sem alteração e avisa ao usuário que ele acertou uma letra
            */
            attempts--;
            texto_em_fala("\n\n\tOps! Essa letra nao faz parte da palavra.\n");

        }
        else {
            texto_em_fala("\n\n\tVoce acertou!\n");

        }

        switch (attempts) {
        case 6://se nenhum erro, nada é feito
        {
            std::cout << "\n_____________   \n";
            std::cout << "|     |           \n";
            std::cout << "|                 \n";
            std::cout << "|                 \n";
            std::cout << "|                 \n";
            std::cout << "|                 \n";
            std::cout << "|                 \n";
            std::cout << "|                 \n";
            std::cout << "|_____________    \n";

            break;
        }
        case 5://1º erro = desenha a "cabeça"
        {
            std::cout << "\n_____________   \n";
            std::cout << "|     |           \n";
            std::cout << "|     O           \n";
            std::cout << "|                 \n";
            std::cout << "|                 \n";
            std::cout << "|                 \n";
            std::cout << "|                 \n";
            std::cout << "|                 \n";
            std::cout << "|_____________    \n";
            if (correctGuess == false) {
                previousGuess[0] = guess;
            }
            break;
        }
        case 4: //2º erro = nada desenha a "cabeça" + "tronco"
        {
            std::cout << "\n_____________   \n";
            std::cout << "|     |           \n";
            std::cout << "|     O           \n";
            std::cout << "|     |           \n";
            std::cout << "|     |           \n";
            std::cout << "|     |           \n";
            std::cout << "|                 \n";
            std::cout << "|                 \n";
            std::cout << "|_____________    \n";
            if (correctGuess == false) {
                previousGuess[1] = guess;
            }
            break;
        }
        case 3: //3º erro = desenha a "cabeça" + "tronco" + "braço direito"
        {
            std::cout << "\n_____________   \n";
            std::cout << "|     |           \n";
            std::cout << "|     O           \n";
            std::cout << "|     |           \n";
            std::cout << "|   / |           \n";
            std::cout << "|  /  |           \n";
            std::cout << "|                 \n";
            std::cout << "|                 \n";
            std::cout << "|_____________    \n";
            if (correctGuess == false) {
                previousGuess[2] = guess;
            }
            break;
        }
        case 2: //4º erro = desenha a "cabeça" + "tronco" + "braço direito e esquerdo"
        {
            std::cout << "\n_____________   \n";
            std::cout << "|     |           \n";
            std::cout << "|     O           \n";
            std::cout << "|     |           \n";
            std::cout << "|   / | \\        \n";
            std::cout << "|  /  |  \\       \n";
            std::cout << "|                 \n";
            std::cout << "|                 \n";
            std::cout << "|_____________    \n";
            if (correctGuess == false) {
                previousGuess[3] = guess;
            }
            break;
        }
        case 1: //5º erro = desenha a "cabeça" + "tronco" + "braço direito e esquerdo" + "perna direita
        {
            std::cout << "\n_____________   \n";
            std::cout << "|     |           \n";
            std::cout << "|     O           \n";
            std::cout << "|     |           \n";
            std::cout << "|   / | \\        \n";
            std::cout << "|  /  |  \\       \n";
            std::cout << "|    /            \n";
            std::cout << "|   /             \n";
            std::cout << "|_____________    \n";
            if (correctGuess == false) {
                previousGuess[4] = guess;
            }
            break;
        }
        case 0: //6º erro = desenha a "cabeça" + "tronco" + "braço direito e esquerdo" + "perna direita e esquerda" e anuncia o fim.
        {
            std::cout << "\n_____________   \n";
            std::cout << "|     |           \n";
            std::cout << "|     O           \n";
            std::cout << "|     |           \n";
            std::cout << "|   / | \\        \n";
            std::cout << "|  /  |  \\       \n";
            std::cout << "|    / \\         \n";
            std::cout << "|   /   \\        \n";
            std::cout << "|_____________    \n";
            std::cout << "\n GAME OVER";
            attempts--;
            // attempts = - 1;
            break;
        }
        default:
            std::cout << "error";
        }

    }

}

int main()
{
    setlocale(LC_ALL, "portuguese");
    //Chamadas das funções de autenticação
    autenticacao->SetSpeechRecognitionLanguage("pt-BR");                //  CONFIGURAÇÃO DA AUTENTICAÇÃO PARA O RECONHECIMENTO DE FALA EM PORTUGUÊS
    autenticacao->SetSpeechSynthesisLanguage("pt-BR");                  //  CONFIGURAÇÃO DA AUTENTICAÇÃO PARA A SINTETIZAÇÃO DE FALA EM PORTUGUÊS
    autenticacao->SetSpeechSynthesisVoiceName("pt-BR-FranciscaNeural"); //pt-BR-Daniel  // CONFIGURAÇÃO DA AUTENTICAÇÃO COM UMA VOZ ESPECÍFICA
    requisicao_textofala = SpeechSynthesizer::FromConfig(autenticacao); //  REDEFINIÇÃO DO OBJETO REQUISICAO_TEXTOFALA COM AS NOVAS CONFIGURAÇÕES
    requisicao_falatexto = SpeechRecognizer::FromConfig(autenticacao, audio_config); //  REDEFINIÇÃO DO OBJETO REQUISICAO_FALATEXTO COM AS NOVAS CONFIGURAÇÕES


    jogo();             //chamada da logica do jogo


    std::cout << "\n\n\n";
    system("pause");
    //return 0;
}
