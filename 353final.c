//353 Group 4 Final Project
//Created by Brad Bieselin, Caleb Rodabaugh, Vince Seeraj, and Thupten Choephel

/*
Simon Says is a well-known game that is both quick and challenging to play.
To beat our game, make it to level 20!
This game includes 3 pushbuttons, each with its own LED. Each level, you are
required to copy what "Simon Says" and the game will gradually become more difficult.
*/


int randomSequence[20]; //An array to hold the randomized sequence
int input[20]; //An array to hold user's entry
const int buzzer = 9; // The buzzer's pin #
int level = 1; //Starting level

//Basic setup
void setup() {
    pinMode(A0, INPUT); //Sets the green LEDs button as an input
    pinMode(A1, INPUT); //Sets the red LEDs button as an input
    pinMode(A2, INPUT); //Sets the blue LEDs button as an input
    
    pinMode(13, OUTPUT); //Sets the green LED as an output
    pinMode(12, OUTPUT); //Sets the red LED as an output
    pinMode(11, OUTPUT); //Sets the blue LED as an output
    pinMode(buzzer, OUTPUT); //Sets the buzzer as an output
    
    digitalWrite(13, LOW); //Initializes output as low
    digitalWrite(12, LOW); //Initializes output as low
    digitalWrite(11, LOW); //Initializes output as low
}

//The loop that calls other functions to run the game
void loop()
{
    randomize(); //Calls a function to randomize the sequence of LEDs displayed
    play(); //Displays the randomized sequence by flashing LEDs
    readInput(); //Checks the buttons the user presses and sees if they match
}

//Displays the sequence of LEDs stored in the randomized array
void play()
{
    digitalWrite(13, LOW); //Sets output as low
    digitalWrite(12, LOW); //Sets output as low
    digitalWrite(11, LOW); //Sets output as low
    
    for (int i = 0; i < level; i++) //Reads through the array for a number of LEDs to lightup equal to the level the user is on
    {
        digitalWrite(randomSequence[i], HIGH); //Sets the output of whatever led is read from the array as high
        if (randomSequence[i] == 11) //If the blue LED is lit up
        {
            tone(buzzer, 500); //Plays a sound unique to the blue LED
        }
        if (randomSequence[i] == 12) //If the red LED is lit up
        {
            tone(buzzer, 400); //Plays a sound unique to the red LED
        }
        if (randomSequence[i] == 13) //If the green LED is lit up
        {
            tone(buzzer, 300); //Plays a sound unique to the green LED
        }
        delay(1000); //Waits 1 second, so it shows the light and plays the sound for a second
        digitalWrite(randomSequence[i], LOW); //Sets LED output as low
        noTone(buzzer); //Stops the buzzer
        delay(200); //Waits .2 seconds
    }
}

//Has the user press buttons and check if those buttons match up to the randomized array
void readInput()
{
    int flag = 0; //A variable that will be set to 1 if a button has been pressed
    
    for (int i = 0; i < level; i++) //A loop to read user input for a number equal to the level
    {
        flag = 0; //Sets flag as 0
        while(flag == 0) //A loop that runs if the flag is 0, will keep looping until a button is pressed
        {
            if (digitalRead(A0) == LOW) //If the green LEDs button is pressed
            {
                tone(buzzer, 300); //Plays the green LEDs sound
                digitalWrite(13, HIGH); //Lights up the green LED
                input[i] = 13; //Sets the user input array
                flag = 1; //Sets the flag to show the button has been pressed
                delay(1000); //Waits a second, so the LED and buzzer run for a second
                noTone(buzzer); //Turns the buzzer off
                if (input[i] != randomSequence[i]) //Checks if the user hit a button for a LED that wasn't diplayed in that order
                {
                    wrong(); //Jumps to the wrong function
                    return; //Returns, so the for loop continues to the next entry
                }
                digitalWrite(13, LOW); //Turns the LED off
            }
            
            if (digitalRead(A1) == LOW) //If the red LEDs button is pressed
            {
                tone(buzzer, 400); //Plays the red LEDs sound
                digitalWrite(12, HIGH); //Lights up the red LED
                input[i] = 12; //Sets the user input array
                flag = 1; //Sets the flag to show the button has been pressed
                delay(1000); //Waits a second, so the LED and buzzer run for a second
                noTone(buzzer); //Turns the buzzer off
                if (input[i] != randomSequence[i]) //Checks if the user hit a button for a LED that wasn't diplayed in that order
                {
                    wrong(); //Jumps to the wrong function
                    return; //Returns, so the for loop continues to the next entry
                }
                digitalWrite(12, LOW); //Turns the LED off
            }
            
            if (digitalRead(A2) == LOW) //If the blue LEDs button is pressed
            {
                tone(buzzer, 500); //Plays the blue LEDs sound
                digitalWrite(11, HIGH); //Lights up the blue LED
                input[i] = 11; //Sets the user input array
                flag = 1; //Sets the flag to show the button has been pressed
                delay(1000); //Waits a second, so the LED and buzzer run for a second
                noTone(buzzer); //Turns the buzzer off
                if (input[i] != randomSequence[i]) //Checks if the user hit a button for a LED that wasn't diplayed in that order
                {
                    wrong(); //Jumps to the wrong function
                    return; //Returns, so the for loop continues to the next entry
                }
                digitalWrite(11, LOW); //Turns the LED off
            }
        }
    }
    correct(); //Jumps to the correct function if the sequence was replicated correctly
}

//A function to make a random array
void randomize()
{
    for (int i = 0; i < 20; i++) //A loop that runs 20 times, for 20 levels max
    {
        randomSequence[i] = random(11,14); //Randomly sets each element in the array to be either 11,12 or 13
    }
}

//A function for if the wrong button was pressed
void wrong()
{
    delay(500); //Waits .5 seconds
    tone(buzzer, 100); //Plays a tone
    digitalWrite(13, HIGH); //Lights up the green LED
    digitalWrite(12, HIGH); //Lights up the red LED
    digitalWrite(11, HIGH); //Lights up the blue LED
    delay(500); //Waits .5 seconds
    digitalWrite(13, LOW); //Turns the green LED off
    digitalWrite(12, LOW); //Turns the red LED off
    digitalWrite(11, LOW); //Turns the blue LED off
    noTone(buzzer); //Turns the buzzer off
    delay(500); //Waits .5 seconds
    level = 1; //Resets the game, so it starts over at level 1
}

//A function for if the correct sequence was entered
void correct()
{
    delay(500); //Waits .5 seconds
    if (level < 20); //If the game isn't over
    level++; //Increase the level
}
