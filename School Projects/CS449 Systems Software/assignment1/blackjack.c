/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BlackJack.c
 * Author: Chris
 * Created on January 25, 2016, 7:51 PM
 *
 * This is a simple C program that allows a user to play blackjack with a simulated random
 * deck. After the cards are dealt, the user is prompted whether they want to "hit" or "stand"
 * If the player's total goes over 21, they lose. If their total is greater than
 * the dealers, they win.
 *
 * 
 */

#include <stdio.h>
#include <time.h>
#include <string.h>

int value;
int deck[] = {2,3,4,5,6,7,8,9,10,10,10,11};
int card;

/* Returns a randomly selected value from the array of card values*/

int random(){
    
    value = rand() % (11 - 0 + 1) + 0;
    card = deck[value];
    return card;
}

int card1, card2, player_total, new_total;
int dealer_card1, dealer_card2, dealer_total;
char input[25];
char hit[25];
char Hit[25];
char Stand[25];
char stand[25];

int ace_count;


void game(){
    
	/* Deals cards for both the player and the dealer by calling the random method */
    card1 = random();
    card2 = random();
    dealer_card1 = random();
    dealer_card2 = random();
    
    strcpy(hit, "hit");
    strcpy(Hit, "Hit");
    strcpy(Stand, "Stand");
    strcpy(Stand, "stand");
    
    player_total = card1 + card2;
    dealer_total = dealer_card1 + dealer_card2;
    

    printf("The dealer: \n ? + %d \n", dealer_card2);
    
	/*Checks initially for any aces*/
	if(player_total > 21){
	if(card1 = 11){
	   card1 = 1;
	}
	else{
	   card2 = 1;
	}
     }	

    printf("You: "
           "\n %d + %d = %d \n", card1, card2, player_total);
    new_total = player_total;
    
	/*While loop for the player receiving cards
	* If hit is entered then they will be dealt a card
	* If stand is entered then a break statement will terminate while loop and their turn is over
	*/
    while(player_total <= 20 || new_total <= 20){
        printf("Would you like to \"hit\" or \"stand\"? ");
        scanf("%s", input);
        if(strcmp(input, "hit") == 0 || strcmp(input, "Hit") == 0){
            card2 = random();
            if(card2 == 11){
                ace_count++;
                
            }
            new_total += card2;
			/* Keeps track of any aces that the player may has and adjusts their score accordingly
			* If the player's total is greater than 21 and they have an ace, the ace's value goes from 11 to 1.
			*/
            if(new_total > 21 && ace_count >= 1){
                ace_count--;
                new_total -= 10;
                printf("Ace turns into a one \n");
            }
            printf("Your new total: \n "
                    "%d + %d = %d \n" , player_total, card2, new_total);
        } else if(strcmp(input, "stand") == 0 || strcmp(input, "Stand") == 0){
            break;
        }
        else{
            printf("Please enter either hit or stand \n");
            continue;
        }
        
        
    }
	printf("Dealer total: %d \n", dealer_total);
	/* Dealer draws:
	* Dealer must hit if their total is below 17 and stand if at 17 or above
	*/
	while(dealer_total < 17){
	   dealer_card2 = random();
	   printf("Dealer hits: %d + %d = %d \n", dealer_total, 
				dealer_card2, dealer_total + dealer_card2);
	   dealer_total += dealer_card2;
	   
	   if(dealer_total > 21){
		printf("Dealer busted. You win!! \n");
		break;
	   }
	}
	if(dealer_total < 21){
        printf("Dealer total: \n"
               "%d + %d = %d \n", dealer_card1, dealer_card2, dealer_total);
	}
	/* 
	* Final results for the game:
	* Whichever player has the higher score without being over 21 wins
	*/
	if(new_total == 21){
	    printf("Blackjack! ");
	}
        if(new_total > 21){
            printf("Busted! You lose :( \n");
        }
        else{
            if(new_total > dealer_total){
                printf("Congrats you win! \n");
            }
            else if(new_total == dealer_total){
                printf("Its a draw! \n");
            }
			else if (dealer_total > 21) {

			}
			else{
                printf("Dealer wins!\n");
            }
        }
    
}
 /*
 * Calls game function and initiates srand to use for our random number generator
 */
int main() {
    printf("Welcome to BlackJack game \n");
    srand((unsigned int)time(NULL));
    game();
    return (0);
}



