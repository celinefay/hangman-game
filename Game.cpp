
#include <iostream>
#include <fstream> // we can read and write files in
#include <ctime> // any random general
#include <string> // to use words

//using namespace std;


int main() {


  // start of screen
  char start{};


  std::cout << "\nHangman!\n\n";
  std::cout << "by Celine & Hernane\n";
  std::cout << "_____________   \n";
  std::cout << "|     |         \n";
  std::cout << "|     O         \n";
  std::cout << "|     |         \n";
  std::cout << "|   / | \\       \n";
  std::cout << "|  /  |  \\      \n";
  std::cout << "|    / \\        \n";
  std::cout << "|   /   \\       \n";
  std::cout << "|_____________   \n";
  std::cout << "\n press key to start\n";
  std::cin >> start;

  // start of the game
  // set variables to use in game :

  int attempts{ 6 }; //how many times it takes to guess correctly
  char guess;
  bool correctGuess = false;
  char previousGuess[7]; // array of guess > user can guess
  previousGuess[0] = '\0';

  for(int i = 0; i < 6; i++){
    previousGuess[i] = '-';
  }
  previousGuess[6] = '\0';
  std::string word;  // word players guesses
  std::string wordList[99]; // array 100 strings


  // get a random word
  srand(time(NULL)); // get any random word
  std::ifstream RandomWord; // file reads variable ofstream
  RandomWord.open("word.txt"); //reads from file


  for(int i = 0; i < 99; i++){
    RandomWord >> wordList[i];
  //  std::cout << "wordList[i]" <<std::endl; //TEST
  }

  int randomNum = rand() % 100;
  word = wordList[randomNum];
  std::cout << word << std::endl; // TEST
  RandomWord.close();

  // word mystry
  std::string MystryWord(word.length(), '*');
  //std::cout << MystryWord << std::endl;

  while(attempts >= 0){

    // reset bool
    correctGuess = false;


     // this loop will keep on running until the statement is true.

     // display info related to word

    std::cout << "the word you have to guess \n\n";
    std::cout << MystryWord << std::endl;
    std::cout << "there are : " << MystryWord.length() << " letters in the word \n";  std::cout << "you have : " << attempts << " guesses left\n";

    if(previousGuess [0] == '\0'){

      std::cout << std::endl;
    }
    else{
      std::cout << "you guessed: " << previousGuess << std::endl;
    }

    std::cout << "\nguess a letter: ";
    std::cin >> guess;
    system("CLS");//flag p/ limpar a tela

    // is guess correct
    for(int i = 0; i < MystryWord.length(); i++){
        if(word[i] == guess) // does word = guess
        {
          MystryWord[i] = guess;
          correctGuess = true;
        }
    }

    if(word == MystryWord){
      std::cout << "\n\ncongrats your word is correct " << MystryWord;
      break;
    }

    if(correctGuess == false)
    {
      attempts--;
      std::cout << "sorry " << guess << " is not part of the word";
    }
    else{
      std::cout << "congrats " << guess << " is on of the letters!";
    }

    switch(attempts){
      case 6:
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
      case 5:
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
      if (correctGuess  == false){
        previousGuess[0] = guess;
      }
        break;
      }
      case 4:
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
      if (correctGuess  == false){
        previousGuess[1] = guess;
      }
        break;
      }
      case 3:
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
      if (correctGuess  == false){
        previousGuess[2] = guess;
      }
        break;
      }
      case 2:
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
      if (correctGuess  == false){
        previousGuess[3] = guess;
      }
        break;
      }
      case 1:
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
      if (correctGuess  == false){
        previousGuess[4] = guess;
      }
        break;
      }
      case 0:
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
        std::cout <<"\n GAME OVER";
        attempts--;
        // attempts = - 1;
        break;
      }
      default:
        std::cout << "error";
    }

  }
  return 0;
}

