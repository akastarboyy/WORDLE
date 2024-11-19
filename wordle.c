    #include<stdio.h>
    #include<time.h>
    #include<stdlib.h>
    #include<string.h>

    #define NoofChances 5
    
    int main()
    {
        /* initialization of variables */
        int chance_counter = 0;
        int word_count = 0;
        int current_index = 0;
        int flag = 0;
        int wrongpos_counter=0;
        int correctpos_counter =0;
        char word[6];
        char question[6];
        char answer[6];
        char wrongpos[6];
        char correctpos[6];


        /* Code begins */
        printf("I WELCOME YOU TO THE GAME ! \n");
        

        //Take a random word from a file and store it in question array
        FILE *file = fopen("WORDS.txt","r");
        if(file == NULL)   
        {
            printf("Could not Open the file \n");
            return 1;
        } 

        while(fgets(word,sizeof(word),file))
        {
            word_count++;
        } 

        srand(time(NULL));
        int random_index = rand() % word_count;
        rewind(file);

        while(fgets(word,sizeof(word),file))
        {
            word[strcspn(word, "\n")] = '\0';
            if(current_index == random_index)
            {
                strncpy(question,word,5);
                question[5] = '\0';
                break;
            }
            current_index++;
        }

        // printf("The random word is  - %s \n",question);
        

        while(chance_counter != NoofChances)
        {
            wrongpos_counter = 0;
            correctpos_counter = 0;
            printf("Enter To guess!\n");
            printf("chance - %d \n",chance_counter+1);
            gets(answer);
            memset(correctpos,0,sizeof(correctpos));
            memset(wrongpos,0,sizeof(wrongpos));

            
            if (strcmp(answer, question) == 0) 
            {
                printf("Congratulations, you won!\n");
                return 1;
            }

            for (int i = 0; i < 5; i++) 
            {
                if (answer[i] == question[i]) 
                {
                    correctpos[correctpos_counter++] = answer[i];
                }       
                else 
                {
                    for (int j = 0; j < 5; j++) 
                    {
                        if (answer[i] == question[j] && i != j ) 
                        {
                            wrongpos[wrongpos_counter++] = answer[i];
                            break;
                        }
                    }
                }
            }

            wrongpos[wrongpos_counter] = '\0';
            correctpos[correctpos_counter] = '\0';

            // printf("Correct letter and in correct pos \n");
            // for(int i=0;i<correctpos_counter;i++)
            // {
            //    printf("%c ",correctpos[i]);
            // }
            // printf("\n");


            // printf("correct letter and but in wrong pos \n");
            // for(int i=0;i<wrongpos_counter;i++)
            // {
            //    printf("%c ",wrongpos[i]);
            // }
            // printf("\n");

            for(int i=0;i<5;i++)
            {
                if(strchr(correctpos,answer[i]) && answer[i] == question[i])
                {
                    printf("\033[32m%c\033[0m ", answer[i]);
                }
                else if(strchr(wrongpos,answer[i]) && !(strchr(correctpos,answer[i])))
                {
                    printf("\033[31m%c\033[0m ", answer[i]);
                }
                else
                {
                    printf("%c ",answer[i]);
                }
            }
            printf("\n");

            chance_counter++;
        }

        printf("Chance over better luck next time \n");
        printf("The word is  - %s \n",question);
        return 0;
    }