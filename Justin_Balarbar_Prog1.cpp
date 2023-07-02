// Justin Balarbar
// Oct 10 2022
// CS2308.005

// Library declarations
#include <cstring>
#include <fstream>
#include <iostream>
#include <tgmath.h>
#include <cstdlib>

using namespace std;

// Global arrays declared for the maximum number of questions possible in the
// game
string questions[50][6];
char answers[50];

// Function prototype declarations
int read_questions(char *argv[]);
int read_answers(char *argv[]);
void show_question(int random_question, int attempts, char player_answer, string player_name, int question_count);
char player_try();
void play_game(int num_of_questions, char *argv[]);
void sort_score(string player_name, double player_score);

int main(int argc, char *argv[]) {
  // Variable declarations for user input to replay the game without exiting the
  // program
  char input, play;
	int argv_three;

  // Error handling. If user does not use 4 as the seed
  if (argc != 4) {
    cout
        << "Incorrect usage. The correct way is: program.name file 1 file2 seed"
        << endl;
    return -1;
  }  

  // Variable declarations to catch the return of the read question and read
  // answers functions
  int num_of_questions = read_questions(argv);
  int num_of_answers = read_answers(argv);

  // Error handling if questions file is empty
  if (num_of_questions == 0) {
    cout << "Questions file is empty. Exiting Program" << endl;
    return -1;
  }
	
  // Error handling if answers file is empty
  if (num_of_answers == 0) {
    cout << "Answers file is empty. Exiting Program" << endl;
    return -1;
  }

  // Error handling if the number of questions do not match the number of answers
  if (num_of_questions != num_of_answers) {
    cout << "Target files do not match. Exiting Program" << endl;
    return -1;
  }

	argv_three = atoi(argv[3]);
	if (argv_three != num_of_questions && argv_three != num_of_questions){
		cout << "Entered seed does not match number of questions and answers. Exiting Program" << endl;
		return -1;
	}
	
  // Begin playing game
  play_game(num_of_questions, argv);

  return 0;
}

// Read Questions function
// Reads questions.txt file and inputs questions into 2D array
// Parameters: argv[1]
// Returns: Number of questions in the file
// Side effects: Exits program is questions file is empy or number of questions
// do not match number of answers.
int read_questions(char *argv[]) {

  // Declaring question file stream
  // Variable declarations to store information from questions file into 2D
  // array
  ifstream fin_q;
  string temp_q, question;
  int counter_q = 0;
	bool blank_line = true;

  // Opening questions txt file
  fin_q.open(argv[1]);

  // Error handling for if question file does not open
  if (!fin_q) {
    cout << "File could not be opened" << endl;
    return -1;
  }

  // Storing questions into 2D array
  // First dimention of the array is question number
  // Second dimention of the array is the question information from the file
  // Using string concatination to add question and answer headers to
  // information from the question file
  while (!fin_q.eof()) {
    for (int j = 0; j < 6; j++) {
      getline(fin_q, temp_q);
      if (temp_q.length() != 0 && temp_q.length() != 1) {
        switch (j) {
        case 0:
          temp_q = temp_q;
          break;
        case 1:
          temp_q = "A: " + temp_q;
          break;
        case 2:
          temp_q = "B: " + temp_q;
          break;
        case 3:
          temp_q = "C: " + temp_q;
          break;
        case 4:
          temp_q = "D: " + temp_q;
          break;
        default:
          break;
        }
				questions[counter_q][j] = temp_q;
      }
			else {
        break;
      }
    }
			// Increments counter of number of questions if and ony if the question and all of the answer choices were stored in the array
			if(questions[counter_q][0].length() > 1 && questions[counter_q][1].length() > 1 && questions[counter_q][2].length() > 1 && questions[counter_q][3].length() > 1 && questions[counter_q][4].length() > 1){
				counter_q++;
			}
    }
  

  // Closing questions file stream
  fin_q.close();

  return counter_q;
}

// Read Answers function
// Reads answers file and inputs into 1D array
// Parameters: Argv[2]
// Returns: Number of answers in the answers file
// Side effects: Exits program is questions file is empy or number of questions
// do not match number of answers.
int read_answers(char *argv[]) {

  // Declaring answer file stream
  // Variable declarations to store information from answers file into 1D array
  ifstream fin_a;
  bool end_of_file = false;
  char temp_a;
  int counter_a = 0;

  // Opening answers txt file
  fin_a.open(argv[2]);

  // Error handling if answers txt file does not open
  if (!fin_a) {
    cout << "File could not be opened" << endl;
    return -1;
  }

  // Storing answer file information into 1D array
  // Only one dimention, therefore the answer number corresponds to the index of
  // the array
  while (!fin_a.eof()){
    fin_a >> temp_a;
		if (fin_a.eof()){
			break;
		}
		answers[counter_a] = temp_a;
		counter_a++;
  }
	
  // Closing answers file stream
  fin_a.close();

  return counter_a;
}

// Show Questions function
// Displays questions and answer choices stored in the 2D array of questions
// Parameters: The index of the randomly generated question in the 2D array, the
// number of attempts the player has made on the question, and the players
// answers 
// Returns: Nothing 
// Side effects: None. Only displays information to console
void show_question(int random_question, int attempts, char player_answer, string player_name , int question_count) {

  // Displays question after 0 attempts
  if (attempts == 0) {
		cout << player_name << "  Here is Question " << question_count << endl;
    cout << questions[random_question][0] << endl;
    cout << questions[random_question][1] << endl;
    cout << questions[random_question][2] << endl;
    cout << questions[random_question][3] << endl;
    cout << questions[random_question][4] << endl;
  }

  // Displays question again if answered incorrectly with the incorrect answer
  // removed from the displayed answer choices
  if (attempts == 1) {
    switch (player_answer) {
    case 'A': {
      cout << questions[random_question][0] << endl;
			cout << endl;
      cout << questions[random_question][2] << endl;
      cout << questions[random_question][3] << endl;
      cout << questions[random_question][4] << endl;
      break;
    }
    case 'B': {
      cout << questions[random_question][0] << endl;
      cout << questions[random_question][1] << endl;
			cout << endl;
      cout << questions[random_question][3] << endl;
      cout << questions[random_question][4] << endl;
      break;
    }
    case 'C': {
      cout << questions[random_question][0] << endl;
      cout << questions[random_question][1] << endl;
      cout << questions[random_question][2] << endl;
			cout << endl;
      cout << questions[random_question][4] << endl;
      break;
    }
    case 'D': {
      cout << questions[random_question][0] << endl;
      cout << questions[random_question][1] << endl;
      cout << questions[random_question][2] << endl;
      cout << questions[random_question][3] << endl;
			cout << endl;
      break;
    }
    default:
      break;
    }
  }
}

// Player Try function
// Allows user input from user to answer the question displayed. Converts all
// user input into upper case. Verifies if user input is valid before returning.
// If input is not valid, user can reinput. 
// Parameters: None Returns: The user's input as a character
// Side effects: Return is compared to the 1D array of answers
char player_try() {

  // Variable declarations to process user input
  char player_input, player_answer;
  bool valid_answer = true;

  // Loop takes input from the user, converts it to upper case then, verifies if
  // input was valid
  do {
    cout << "Your Choice? ";
    cin >> player_input;
    cout << endl;
    player_answer = toupper(player_input);

    // Only inputs that are listed in the switch are valid inputs
    switch (player_answer) {
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'S':
      return player_answer;
      break;

      // If user input is defaulted, user input is invalid. User is prompted to
      // reinput
    default:
      cout << "Invalid input. Try again." << endl;
      valid_answer = false;
      break;
    };
  } while (!valid_answer);
}

// Play Game function
// Primary function of the game. Generates random numbers to display random
// questions from the 2D array of questions. Accepts input for player name.
// Increments player score as the user plays the game. 
// Parameters: Number of questions returned from read questions function, argv[3] 
// Returns: Nothing
// Side effects: Function calls sort score function to pass player score and player name
void play_game(int num_of_questions, char *argv[]) {
  cout << "Welcome to the QUIZ SHOW! Lets Play!" << endl << endl;

  // Variable declaration and initializations
  int seed = atoi(argv[3]);
	int question_count = 1;
  string player_name;
  double player_score = 0;
	double previous_round_worth = 0;
  int random_question;
  bool check[num_of_questions];
  int attempts = 0;
  char player_answer;
	bool is_space = false;
	double question_worth = 10;

  // Initializing a 1D array of boolean values to use to prevent asking 		 repeat
  // questions
  for (int i = 0; i < num_of_questions ; i++) {
    check[i] = false;
  }

  // Primary loop for the operation of the game
  do {

		is_space = false;
    // Taking user input for thier player name
    cout << "Enter player name (No spaces): " << endl;
    getline(cin, player_name);
    cout << endl;

    // Verifying if player name is valid input, if not, player is prompted to re-enter

		for(int i = 0; i < player_name.length(); i++){
			if(player_name.at(i) == ' '){
				cout << "Not a valid Player Name. Try again " << endl;
				is_space = true;
				break;
			}
		}
  } while (is_space);

  // Loop to ensure game terminates after asking 6 questions
  while (question_count < 6) {
    for (int i = 0; i < num_of_questions; i++) {
      // Generating random numbers to use as the index to display questions from
      // the 2D array of questions
      srand(seed);
      random_question = rand() % num_of_questions;

      // If the number genrated is corresponds to a question that was already
      // displayed, generates a new number
      while (check[random_question] == true) {
        random_question = rand() % num_of_questions;
      }

      // Updates the 1D boolean array to true when question is displayed.
      // Ensures that a question is not displayed twice
      check[random_question] = true;

      // function call to display randomly selected question to the console
      show_question(random_question, attempts, player_answer, player_name, question_count);
      
			// Variable declaration to catch the return of Player Try function
      player_answer = player_try();

      // If player gets the question right, increments player score, applies 10X
      // multiplyer to question value for the next question. Displays player's
      // current score.
      if (player_answer == answers[random_question]) {
        cout << "Correct!" << endl;
				player_score = player_score + question_worth;
				question_worth = question_worth*10;
        cout << "Your score: " << player_score << endl << endl;
      }

      // Skip question option after 0 attempts. Applies no score value
      // multipliers, does not increment player score as not points were earned
      else if (player_answer == 'S') {
        cout << "Skipped, no points awarded" << endl;
				cout << "Your score: " << player_score << endl << endl;
      }

      // If player gets question wrong on first attempt, allows player to answer
      // again, applies 0.5X multiplier to current question value
      else if (player_answer != answers[random_question]) {
        cout << "Incorrect. Try again for 1/2 points? (S to skip) " << endl;
        question_worth = question_worth / 2;
        attempts++;
        show_question(random_question, attempts, player_answer, player_name, question_count);
        player_answer = player_try();

        // If player gets question right on second attempt, increments player
        // score, and applies 10X multiplier to the question value for the next
        // question.
        if (player_answer == answers[random_question]) {
          cout << "Correct!" << endl;
					player_score = player_score + question_worth;
					question_worth = question_worth * 10;
          cout << "Your score: " << player_score << endl << endl;
        }

        // Skip question option after 1 attempt. Applies 10X multiplier for next round, does not increment player score as not points were earned
        else if (player_answer == 'S') {
          cout << "Skipped, no points awarded" << endl;
					question_worth = question_worth * 10;
						cout << "Your score: " << player_score << endl << endl;
					}

        // If player gets question wrong on second attempt, score is set to zero. Exits game.
        else if (player_answer != answers[random_question]) {
          cout << "Incorrect. Study more and try again!" << endl;
          cout << "Your score: " << player_score << endl << endl;
					player_score = 0;
					question_count = 7;
					break;
        }
      }
      attempts = 0;
			question_count++;
			if (question_count >= 7){
				break;
			}
    }
		
  }

  // Prompts user when all questions are displayed
  cout << "Game Over!" << endl << endl;

  // Displays final score after playing game
  cout << "Final Score: " << player_score << endl << endl;

  // Function call Sort Score function to update scoreboard and display score
  // board of all past players and current player
  sort_score(player_name, player_score);

	cout << "Thanks for playing, we hope you'll send all your friends to play." << endl;
}

// Sort Score function
// Takes the player and player score and inputs into summary file titled
// "summary_file.txt". Then reads summary file and sorts players based on score
// in decending order. Displays Leaderboard of sorted players to Console
// Parameters: Player name and player score determined from play game function
// Returns: Nothing
// Side effects: Appends player name and score to scorebard summary file
void sort_score(string player_name, double player_score) {

  // File stream declarations
  ofstream fout_l;
  ifstream fin_l;

  // 1D array declarations for sorting player scores
  string players[1000];
  double scores[1000];

  // Variable declarations and initializations
  string scoreboard = "summary_file.txt";
  string temp_p;
  double temp_s;
  int counter_l = 0;
  bool end_file = false;

  // Opens summary_file.txt in append mode
  fout_l.open(scoreboard.c_str(), ios::app);

  // Error handling if summary_file.txt is not able to open
  if (!fout_l) {
    cout << "Cannot write to target file. Exiting program" << endl;
    return;
  }

  // Saving player information to summary file
  fout_l << player_name << " " << player_score << endl;

  // Closing summary file
  fout_l.close();

  // Opening summary file to read information to store in 1D arrays
  fin_l.open(scoreboard.c_str());

  // Error handling if summary file is not able to be opened
  if (!fin_l) {
    cout << "Cannot open target file. Exiting Program" << endl;
    return;
  }

  // 1D array processing. Storing player name in 1D array of strings, and player
  // score in 1D array of doubles
  while (!end_file) {
    if (fin_l.eof()) {
      end_file = true;
      counter_l--;
      break;
    }
    fin_l >> temp_p;
    fin_l >> temp_s;

    players[counter_l] = temp_p;
    scores[counter_l] = temp_s;

    counter_l++;
  };

  // Selection sort agorithm. Sorts 1D arry of scores and 1D array of player
  // names at the same time to ensure players are matched with their respective
  // scores.
  for (int i = 0; i < counter_l - 1; i++) {
    int max = i;

    for (int j = i; j < counter_l; j++) {

      if (scores[max] < scores[j]) {
        max = j;
      }
    }
    temp_s = scores[i];
    temp_p = players[i];

    scores[i] = scores[max];
    players[i] = players[max];

    scores[max] = temp_s;
    players[max] = temp_p;
  }

  // Display leaderboard of highest player and current player rank
  cout << "-- Leaderboard --" << endl;

	cout << "Current Record Holder is " << players[0] << " with " << scores[0] << endl;

	for(int i = 0; i < counter_l; i++){
		if(player_name == players[i]){
			cout << player_name << " has achived rank " << i + 1 << " with score of " << scores[i];
			break;
		}
	}
	
  cout << endl << endl;
}
