#include <stdio.h>
#include <stdlib.h>

struct Point {
    int x;
    int y;
    char a;
};

void print_pos(struct Point *myPos) {
    printf("I am at %d, %d\n", (*myPos).x, myPos->y);
}

int main() {
    struct Point myPos;
    myPos.x = 1;
    myPos.y = 2; 
    print_pos(&myPos);
    printf("Size of myPos = %ld bytes\n", sizeof(struct Point));
}