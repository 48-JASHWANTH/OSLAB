#include<stdio.h>
#include<unistd.h>
#include<stdbool.h>

int main() {
    int ms, fs, np, frames[100][100];
    printf("Enter memory size and frame size : ");
    scanf("%d%d", &ms, &fs);
    printf("Enter no.of processes : ");
    scanf("%d", &np);

    for(int i = 0; i < np; i++) {
        int ps;
        printf("Enter process %d size : ", i);
        scanf("%d", &ps);
        int nfr = ps / fs;
        printf("No.of frames required is : %d\n", nfr);
        printf("Enter frames for process %d : ", i);
        for(int j = 0; j < nfr; j++)
            scanf("%d", &frames[i][j]);
    }

    bool choice;
    do {
        int a, b, c;
        printf("Enter process no, page no and offset : ");
        scanf("%d%d%d", &a, &b, &c);
        printf("The physical address is %d\n", frames[a][b] * fs + c);
        printf("Do you want to continue?(1/0) ");
        scanf("%d", &choice);
    } while(choice);
    return 0;
}
