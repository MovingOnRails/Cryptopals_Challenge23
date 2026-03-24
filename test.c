#include <stdio.h>

#include "../Challenge21/MT19937_wikipedia.c"
#include "./main.c"

int main(){


    mt_state targetState;
    initialize_state(&targetState,0);

    mt_state clonedState;
    initialize_state(&clonedState,0);
    
    for(int i=0;i<624;i++){
        uint32_t targetOutput = random_uint32(&targetState);
        uint32_t targetUntempered = untemper_value(targetOutput);
        clonedState.state_array[i] = targetUntempered;
        clonedState.state_index = ((i+1) % 624);
    }

    printf("targetState.state_index: %i\n",targetState.state_index);
    printf("clonedState.state_index: %i\n",clonedState.state_index);
    for(int i=0;i<624;i++){
        printf("-------------------\n");
        printf("%u \n",targetState.state_array[i]);
        printf("%u \n",clonedState.state_array[i]);
    }

    printf("--------------------\n");
    printf("targetState: %i \n",random_uint32(&targetState));
    printf("clonedState: %i \n",random_uint32(&clonedState));
    
    return 0;
}