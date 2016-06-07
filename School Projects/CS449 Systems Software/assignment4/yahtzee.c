#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 
 */
void create_dice();
void yahtzee();
void roll();
void reroll();
void show_roll();
char random();
void new_turn();
void upper_selection();
void low_selection();
void show_score();
void show_board();
void swap();
void *to_String();

int multiple_rolls[5];
char number[5];
int upper_section[6];
int lower_section[7];
int bonus;

int main(int argc, char** argv) {
    
    
    int i;
    int j;
    
    create_dice();
    
    for(i = 0; i < 6 ; i++){
        upper_section[i] = -1;
    }
    
    for(j = 0; j < 7; j++){
        
        lower_section[j] = -1;
    }
    
    yahtzee();
    return (0);
}

void yahtzee(){
    int i;
    int k;
    int total = 0;
    int choice;
    int turn;
    
    char *get_input = malloc(sizeof(char)*10);    
    while(turn <= 13){
        printf("Your roll: \n");
        
        
        roll();
        show_roll();
        
        reroll();
        
        printf("Put the dice into the section \n");
        printf("1.) Upper Section");
        printf("2.) Lower Section");
        fgets(get_input, sizeof(int), stdin);
        choice = atoi(get_input);
        
        printf("\n Where do you want to place the dice \n");
        if(choice == 1){
            
        
            printf("1) Ones \n");
            printf("2) Twos \n");
            printf("3) Threes \n");
            printf("4) Fours \n");
            printf("5) Fives \n");
            printf("6) Sixes \n");
        
            fgets(get_input, sizeof(int), stdin);
        
            choice = atoi(get_input);
            upper_selection(choice);
        }
        else if(choice == 2){
            
            printf("1) Three of a kind \n");
            printf("2) Four of a kind \n");
            printf("3) Small straight \n");
            printf("4) Large straight \n");
            printf("5) Full house \n");
            printf("6) Yahtzee \n");
            
            fgets(get_input, sizeof(int), stdin);
            
            choice = atoi(get_input);
            lower_selection(choice);
        }
        
        show_scores();
        show_board();
        
        turn = turn + 1;
        
        new_turn(1);
        
        
    }
    free(get_input);
}

void roll(){
    
    int i;
    
    for(i = 0; i < 5; i++){
        
        if(reroll[i] != 0){
            number[i] = random();
        }
    }
    
    new_turn(0);
  
}
char random(){
    FILE* f;
    char roll;
    int valid;
    
    f = fopen("/dev/dice", "r");
    
    if(f == NULL){
        printf("The driver did not work");
    }
    
    do{
        valid = fread(&roll, sizeof(char), 1, f);
       
    }while(valid != 1);
    
    if(roll > 6 || roll < 1){
        printf("A valid number was not rolled");
    }
    
    fclose(f);
    
    return roll;
}

void show_roll(){
    int i;
    
    for(i = 0; i < 5; i++){
        
        printf("%d", number[i]);
    }
    
    printf("\n");
}

void new_turn(int i){
    int j;
    
    for(j = 0; j < 5 ; j++){
        reroll[j] = i;
    }
}

void reroll(){
    char choice;
    char input[10];
    int new_roll[6];
    char *p;
    int i;
    int j;
    
    for(i = 0; i < 2; i++){
        
        for(j = 0; j < 6; j++){
            
            new_roll[i] = 0;
        }
        
        printf("What die would you like to reroll? \n");
        
        fgets(input, 10, stdin);
        
        j = 0;
        
        p = strtok(input, " ");
        
        while(p != NULL){
            
            input[j++] = atoi(p);
            
            p = strtok(NULL, " ");
        }
        
        if(input[0] == 0){
            break;
        }
        
        i = 0;
        do{
            
            choice = input[i++];
            
            if(choice != 0){
                
                multiple_rolls[choice - 1] = 1;
            }
        }while(choice != 0);
        
        printf("Your new roll: \n");
        roll();
        show_roll();
    }
}

void upper_selection(int result){
    int numbers = result - 1;
    int count = 0;
    int i;
    
    for(i = 0; i < 5; i++){
        
        if(number[i] == result){
            count++;
        }
    }
    
    upper_section[numbers] = result * count;
}

void low_selection(int result){
    char results;
    int dice = result - 1;
    int score = 0;
    
    char results[5];
    
    int i;
    for(i = 0; i < 5;  i++){
        results[i] = number[i];
    }
    
    qsort(results, 5, sizeof(char), compare_die);
    
    if(result == 1){
        if(multiple_kind(3, results)){
            for(i = 0; i < 5; i++){
                score += number[i];
            }
        }
    }
    else if(result == 2){
        if(multiple_kind(4, results)){
            for(i = 0; i < 5; i++){
                score += number[i];
            }
        }
    }else if(result == 3){
        if(check_straight(4, results)){
            score = 30;
        }
    }else if(result == 4){
        if(check_straight(5, results)){
            score = 40;
        }
    }else if(result == 5){
        if(check_fullhouse(results){
            score = 25;
        }
    }else if(result == 6){
        if(multiple_kind(5, results)){
            if(multiple_kind(5, results)){
                for(i = 0; i < 5; i++){
                    score += number[i];
                }
            }
        }
    }else if(result == 7){
        for(i = 0; i < 5; i++){
            score += number[i];
        }
    }
    
    lower_section[dice] = score;
}

void show_scores(){
    int score = 0;
    
    int j;
    int i;
    for(i = 0; i < 6; i++){
        if(upper_section[i] > 0){
            score = score + upper_section[i];
        }
    }
    
    if(score >= 63){
        
        bonus = 35;
        
        score = score + bonus;
    }
    
    for(j = 0; j < 7; j++){
        if(lower_section[j] > 0){
            
            score = score + lower_section[j];
        }
    }
    
    printf("Your score is: %d \n", score);
    
}

void show_board(){
     
    printf("\nOnes: %s \t\t\tFours: %s\nTwos: %s\t\t\t\tFives: %s\nThrees: %s\t\t\tSixes: %s\n", (upper_section[0] == -1)?" ":int_to_string(upper_section[0]), (upper_section[3] == -1)?" ":int_to_string(upper_section[3]), (upper_section[1] == -1)?" ":int_to_string(upper_section[1]), (upper_section[4] == -1)?" ":int_to_string(upper_section[4]), (upper_section[2] == -1)?" ":int_to_string(upper_section[2]), (upper_section[5] == -1)?" ":int_to_string(upper_section[5])); 
    printf("Upper Section Bonus: %d\n", bonus); 
    printf("Three of a kind: %s\t\tFour of a kind: %s\nSmall straight: %s\t\tLarge straight: %s\nFull house: %s\t\t\tYahtzee: %s\nChance: %s\n", (lower_section[0] == -1)?" ":int_to_string(lower_section[0]), (lower_section[1] == -1)?" ":int_to_string(lower_section[1]), (lower_section[2] == -1)?" ":int_to_string(lower_section[2]), (lower_section[3] == -1)?" ":int_to_string(lower_section[3]), (lower_section[4] == -1)?" ":int_to_string(lower_section[4]), (lower_section[5] == -1)?" ":int_to_string(lower_section[5]), (lower_section[6] == -1)?" ":int_to_string(lower_section[6])); 

}

int check_fullhouse(char* results){
    int i;
    int j;
    int check_first_set = 1;
    int check_second_set = 0;
    
    char first_set = results[0];
    char second_set = 0;
    
    for(i = 1; i < 5; i++){
        
        if(results[i] == first_set){
            check_first_set += 1;
        }
        
        else{
            if(second_set == 0){
                second_set = results[i];
                check_second_set = 1;
            }
            else if(results[i] == second_set){
                check_second_set += 1;
            }
        }
    }
    
    if((check_first_set == 2 && check_second_set == 3) || (check_first_set == 3 && check_second_set == 2)){
        return 1;
    }
    else{
        return 0;
    }
}

int multiple_kind(char *results, int multiple){
    int i;
    int j;
    int k;
    
    for(int i = 1; i <= 6; j++){
        
        k = 0;
        for(int j = 0; j < 5; j++){
            if(results[j] == i){
                k++;
            }
        }
        if(k >= multiple){
            return 1;
        }
        
             
    }
    
    return 0;
}

int check_straight(char *results, int straight){
    int i;
    int multiple = 1;
    
    check_dice(results);
    
    for(i = 0; i < straight - 1 ; i++){
        if(results[i+1] == (results[i] + 1)){
            multiple++;
        }
        else{
            return 0;
        }
    }
    
    if(multiple == straight){
        return 1;
    }
    else{
        return 0;
    }
}

void check_dice(char* results){
    char first_die = results[0];
    char second_die = results[1];
    char third_die = results[2];
    char fourth_die = results[3];
    char fifth_die = results[4];
    
    if(fourth_die == fifth_die){
        fifth_die = 0;
    }
    if(third_die == fourth_die){
        fourth_die = 0;
    }
    if(second_die == third_die){
        third_die = 0;
    }
    if(first_die == second_die){
        second_die = 0;
    }
    results[4] = fifth_die;
    results[3] = fourth_die;
    results[2] = third_die;
    results[1] = second_die;
    results[0] = first_die;
    
    qsort(results, 5, sizeof(char), compare_die);
}

int compare_die(const void * diceOne, const void * diceTwo){
    char compareOne = *(char*)diceOne;
    char compareTwo = *(char*)diceTwo;
    
    if(compareOne == 0){
        return 1;
    }
    if(compareTwo = 0){
        return -1;
    }
    
    return compareOne - compareTwo;
}

void create_dice(){
    int i;
    for(i = 0; i < 5; i++){
        reroll[i] = 1;
        number[i] = 0;
    }
}

char *to_String(int dice){
    char *print = malloc(sizeof(char)*10);
    
    int i = 0;
    int index = 0;
    if(dice < 0){
        index = 1;
    }
    if(dice == 0){
        print[i++] = '0';
    } else if(dice < 0){
        print[i++] = '-';
        dice = -dice;
    }
    
    while(dice > 0){
        print[i++] = '0' + dice % 10;
        dice = dice/10;
    }
    
    print[i] = '\0';
    swap(i - index, print + index );
    return print;
}

void swap(int length, char* str){
    int j = length - 1;
    int i = 0;
    char next;
    while(i < j){
        next = str[i];
        
        str[i]= str[j];
        str[j] = next;
        i++;
        j--;
    }
}