#include <stdio.h>

int main() {
    printf("Initial Text");
    
    // Move the cursor up 1 line and to the beginning
    printf("\033[1A\033[0G");
    
    // Clear the line
    printf("\033[K");
    
    // Print the updated text
    printf("Updated Text");
    
    return 0;
}   
