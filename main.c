#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//This variable will store the difficulty that the user has selected
int difficulty;

//Boolean variable used for breaking while loops
bool correct = true;

//This variable keeps a count of how many questions are in the program
int line_count;

//Keeps track of the round that the user is on
int round_count = 0;

//Keeps track of how many games have been played
int game_count = 0;

//Correct answer count
int correct_count;

//Struct containing questions and answers
struct q_a {
    char question[255];
    char answer[255];
    char user_ans[255];
    char user_correct[255];
};

//Creates a struct with a max amount of lines at 100
struct q_a ques_ans[512];

//struct answers ans[500];

//------------------------------------------------------------------------

int main()
{
    readFile();
    chooseDifficulty();
    playGame();
}
//------------------------------------------------------------------------

readFile()
{
    //file_name variable with a size of window's max file name length, assuming the program is run on windows OS.
    char file_name[255];

    //prompt user to input file name.
    printf("\nPlease input the name of the file to be processed: ");
    scanf("%s", file_name);

    //opens the file with the "r" parameter which means the program can only read it's contents as we do not need to edit the file.
    FILE *Qfile = fopen(file_name, "r");

    //if the file does not exist, the program will print an error message.
    if (Qfile == NULL) {
        printf("The file does not exist. Please try again (make sure to include the file extension!).");
        readFile();
    }
    else{
        //here we define a line count and a temporary char to store the line.
        char temp[512];

        //this is the point at which to split the string.

        while(fgets(temp, 512, Qfile)) {

            line_count++;

            //Assings the split string to their appropriate variables
            char * ques = strtok(temp, "?");
            char * ans = strtok(NULL, "? ");

            //Remove the space from the ending of the ans
            ans[strlen(ans)-1] = 0;

            //Append a question mark onto the end of the question
            strncat(ques, "?", 1);

            //Add all variables to the structure
            strcpy(ques_ans[line_count].question, ques);
            strcpy(ques_ans[line_count].answer, ans);
        }
        printf("Total questions: ");
        printf("%d\n", line_count);
    }
}

//------------------------------------------------------------------------

chooseDifficulty()
{
    while(correct){
        printf("Please choose your difficulty (Integer between 1 and 6):  ");
        scanf("%d", &difficulty);
        fflush(stdin);
        switch(difficulty){
            case 1:
                printf("You choose diffuculty: 1\n");
                correct = false;
                break;
            case 2:
                printf("You choose diffuculty: 2\n");
                correct = false;
                break;
            case 3:
                printf("You choose diffuculty: 3\n");
                correct = false;
                break;
            case 4:
                printf("You choose diffuculty: 4\n");
                correct = false;
                break;
            case 5:
                printf("You choose diffuculty: 5\n");
                correct = false;
                break;
            case 6:
                printf("You choose diffuculty: 6\n");
                correct = false;
                break;
            case 0:
                printf("Please enter an interger, not a character...\n");
                //I encountered a problem where my program would infinately loop if a char was provided as in input. This whiole loop
                //clears the input buffer so that the program can continue to run properly.
                while ((difficulty = getchar()) != '\n'){}
                break;
            default:
                printf("Please enter a valid input...\n");
                break;
        }
    }
}

//------------------------------------------------------------------------

//Function that will run the game, I am awake that I did not need the switch and there is a lot of extra code but I simply did not have time to fix it
void playGame()
{
    round_count = 0;
    switch(difficulty){
        case 1: //No clue is given
            while(round_count <= line_count){
                round_count++;
                printf(ques_ans[round_count].question);
                cluePicker(difficulty);
                char answer[255];
                scanf("%s", answer);
                checkAnswer(answer, round_count);
            }
            printStats();
            writeToFile();
            break;

        case 2: //Blank dashes showing the length of the word appear
            while(round_count <= line_count){
                round_count++;
                printf(ques_ans[round_count].question);
                cluePicker(difficulty);
                char answer[255];
                scanf("%s", answer);
                checkAnswer(answer, round_count);
            }
            printStats();
            writeToFile();
            break;

        case 3: //First and last letters are shown
            while(round_count <= line_count){
                round_count++;
                printf(ques_ans[round_count].question);
                cluePicker(difficulty);
                char answer[255];
                scanf("%s", answer);
                checkAnswer(answer, round_count);
            }
            printStats();
            writeToFile();
            break;

        case 4: //Two random letters are visible
            while(round_count <= line_count){
                round_count++;
                printf(ques_ans[round_count].question);
                cluePicker(difficulty);
                char answer[255];
                scanf("%s", answer);
                checkAnswer(answer, round_count);
            }
            printStats();
            writeToFile();
            break;

        case 5: //All letters are shown in random order
            while(round_count <= line_count){
                round_count++;
                printf(ques_ans[round_count].question);
                cluePicker(difficulty);
                char answer[255];
                scanf("%s", answer);
                checkAnswer(answer, round_count);
            }
            printStats();
            writeToFile();
            break;

        case 6: //Type of clue is chosen at random
            while(round_count <= line_count){
                round_count++;
                printf(ques_ans[round_count].question);
                int min = 0;
                int max = 4;
                int random_number = rand() % (max + 1 - min);
                cluePicker(random_number);
                char answer[255];
                scanf("%s", answer);
                checkAnswer(answer, round_count);
            }
            printStats();
            writeToFile();
            break;

    }
}

//------------------------------------------------------------------------
//Function that will change the case of a provided input to lowercase
changeCase(char word[255]){
    //count for loop
    int x;
    char new_word[255];
    for(x = 0;x<=strlen(word);x++){
        if(word[x]>=65&&word[x]<=90){
            word[x]=word[x]+32;
        }
    }
    return word;
}

//------------------------------------------------------------------------
//Compares answers
checkAnswer(char answer[255], int round){
    int result;
    result = strncmp(changeCase(ques_ans[round_count].answer), changeCase(answer), strlen(ques_ans[round_count].answer));
    if(result == 0){
        strcpy(ques_ans[round].user_correct, "Correct!");
        strcpy(ques_ans[round].user_ans, answer);
        correct_count++;
        printf("Correct answer!\n\n");}
    else{printf("incorrect answer :( ...\n\n");}
        strcpy(ques_ans[round].user_correct, "Incorrect :(");
        strcpy(ques_ans[round].user_ans, answer);
}

//------------------------------------------------------------------------

cluePicker(int clue){
    int x;
    switch(clue){
    case 1:
        printf("\n Answer ---> ");
        break;

    case 2:
        printf("\n");
        for(x = 0;x<strlen(ques_ans[round_count].answer);x++){
            printf("- ");
        }
        printf("    ---> ");
        break;

    case 3:
        printf("\n");
        printf("%c ", ques_ans[round_count].answer[0]);
        for(x = 0;x<strlen(ques_ans[round_count].answer) - 2;x++){
            printf("- ");
        }
        printf("%c ", ques_ans[round_count].answer[strlen(ques_ans[round_count].answer) - 1]);
        printf("   ---> ");
        break;

    case 4:
        printf("\n");
        int min = 0;
        int max = strlen(ques_ans[round_count].answer);
        int first_letter = rand() % (max + 1 - min);
        int second_letter = rand() % (max + 1 - min);
        int third_letter = rand() % (max + 1 - min);
        for(x = 0;x<strlen(ques_ans[round_count].answer);x++){
            if(x == second_letter || x == third_letter){printf("%c ", ques_ans[round_count].answer[x]);}
            else{printf("- ");}
        }
        printf("   ---> ");
        break;

    case 5:
        ;// An attempt at randomising the letters but I did not have time to fix it.
        char temp[255];
        strcpy(ques_ans[round_count].answer, temp);
        char new_word[255];
        for(x = strlen(ques_ans[round_count].answer);x<strlen(ques_ans[round_count].answer);x--){
            int random_number = rand() % (x + 1 - 0);
            strcat(new_word, temp[random_number]);
            memmove(&temp[x], &temp[x + 1], strlen(temp) - x);
            puts(temp);
            printf("%s", temp);
        }
        printf("%s", new_word);
        break;
    }
}

//------------------------------------------------------------------------
//Prints all stats from the game
printStats(){
    int x;
    for(x = 0; x <= line_count; x++){
        printf("\nQuestion: %s\n", ques_ans[x].question);
        printf("Your Answer: %s\n", ques_ans[x].user_ans);
        printf("Your result: %s\n", ques_ans[x].user_correct);
        printf("Correct Answer: %s\n\n", ques_ans[x].answer);
    }
    printf("Correct count: %d", correct_count);
}

//------------------------------------------------------------------------

writeToFile(){
    char filename[255];
    printf("\nPlease input the name of the file to be written to: ");
    scanf("%s", filename);
    FILE *Qfile = fopen(filename, "a");

    //if the file does not exist, the program will print an error message.
    if (Qfile == NULL) {
        printf("The file does not exist. Please try again (make sure to include the file extension!).");
        writeToFile();
    }
    int x;
    for(x = 0; x < line_count; x++){
        fprintf(filename, "Question: ");
        fprintf(filename, ques_ans[x].question);
        fprintf(filename, "\n");
        fprintf(filename, "Yours Answer: ");
        fprintf(filename, ques_ans[x].user_ans);
        fprintf(filename, "\n");
        fprintf(filename, "Your result: ");
        fprintf(filename, ques_ans[x].user_correct);
        fprintf(filename, "\n");
        fprintf(filename, "Correct Answer: ");
        fprintf(filename, ques_ans[x].answer);
        fprintf(filename, "\n\n");
    }
    fclose(filename);
}


//I would please ask that you understand how difficult the last few months have been. I did not complete my last assingment before due date and need to do well in this.
//This project was completed roughly in 6 or 7 hours as it was all the time I could get. Thanks
