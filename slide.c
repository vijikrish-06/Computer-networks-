#include <stdio.h>

/* Check whether a frame is lost */
int isLost(int frame, int lost[], int lostCount)
{
    int i;
    for (i = 0; i < lostCount; i++)
    {
        if (frame == lost[i])
            return 1;
    }
    return 0;
}

/* ---------------- STOP-AND-WAIT ARQ ---------------- */
void stopAndWait(int n, int lost[], int lostCount)
{
    int i;
    int total = 0;
    printf("\n===== STOP-AND-WAIT ARQ =====\n");
    printf("Window Size = 1\n");
    for (i = 0; i < n; i++)
    {
        printf("\nFrame %d transmitted\n", i);
        total++;
        if (isLost(i, lost, lostCount))
        {
            printf("Frame %d LOST/CORRUPTED\n", i);
            printf("Timeout occurred for Frame %d\n", i);
            printf("Frame %d retransmitted\n", i);
            total++;
            printf("Frame %d correctly received\n", i);
            printf("ACK %d received\n", i);
        }
        else
        {
            printf("Frame %d correctly received\n", i);
            printf("ACK %d received\n", i);
        }
    }
    printf("\nAll frames delivered successfully.\n");
    printf("Total transmissions = %d\n", total);
}

/* ---------------- GO-BACK-N ARQ ---------------- */
void goBackN(int n, int w, int lost[], int lostCount)
{
    int i, j, k;
    int total = 0;
    i = 0;
    printf("\n===== GO-BACK-N ARQ =====\n");
    printf("Window Size = %d\n", w);
    while (i < n)
    {
        printf("\nTransmitting Window: ");
        for (j = i; j < i + w && j < n; j++)
        {
            printf("%d ", j);
        }
        printf("\n");
        for (j = i; j < i + w && j < n; j++)
        {
            printf("\nFrame %d transmitted\n", j);
            total++;
            if (isLost(j, lost, lostCount))
            {
                printf("Frame %d LOST/CORRUPTED\n", j);
                printf("Timeout occurred for Frame %d\n", j);
                printf("\nGo-Back-N: Retransmitting from Frame %d\n", j);
                /*
                 * Retransmit the lost frame and all
                 * following frames in the same window.
                 */
                for (k = j; k < i + w && k < n; k++)
                {
                    printf("Frame %d retransmitted\n", k);
                    total++;
                    printf("Frame %d correctly received\n", k);
                    printf("ACK %d received\n", k);
                }
                break;
            }
            else
            {
                printf("Frame %d correctly received\n", j);
                printf("ACK %d received\n", j);
            }
        }
        i = i + w;
    }
    printf("\nAll frames delivered successfully.\n");
    printf("Total transmissions = %d\n", total);
}

/* ---------------- SELECTIVE REPEAT ARQ ---------------- */
void selectiveRepeat(int n, int w, int lost[], int lostCount)
{
    int i, j, k;
    int total = 0;
    printf("\n===== SELECTIVE REPEAT ARQ =====\n");
    printf("Window Size = %d\n", w);
    for (i = 0; i < n; i = i + w)
    {
        printf("\nTransmitting Window: ");
        for (j = i; j < i + w && j < n; j++)
        {
            printf("%d ", j);
        }
        printf("\n");
        /* Initial transmission */
        for (j = i; j < i + w && j < n; j++)
        {
            printf("\nFrame %d transmitted\n", j);
            total++;
            if (isLost(j, lost, lostCount))
            {
                printf("Frame %d LOST/CORRUPTED\n", j);
                printf("No ACK received for Frame %d\n", j);
            }
            else
            {
                printf("Frame %d correctly received\n", j);
                printf("ACK %d received\n", j);
            }
        }
        /* Retransmit only lost frames */
        for (k = i; k < i + w && k < n; k++)
        {
            if (isLost(k, lost, lostCount))
            {
                printf("\nTimeout occurred for Frame %d\n", k);
                printf("Selective Repeat: Retransmitting only Frame %d\n", k);
                printf("Frame %d retransmitted\n", k);
                total++;
                printf("Frame %d correctly received\n", k);
                printf("ACK %d received\n", k);
            }
        }
    }
    printf("\nAll frames delivered successfully.\n");
    printf("Total transmissions = %d\n", total);
}

/* ---------------- MAIN FUNCTION ---------------- */
int main()
{
    int choice;
    int n, w;
    int lostCount;
    int lost[100];
    int i;
    while (1)
    {
        printf("\n========================================\n");
        printf("       SLIDING WINDOW PROTOCOLS\n");
        printf("========================================\n");
        printf("\n1. Stop-and-Wait ARQ");
        printf("\n2. Go-Back-N ARQ");
        printf("\n3. Selective Repeat ARQ");
        printf("\n4. Exit");
        printf("\n\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice)
        {
            /* -------- STOP AND WAIT -------- */
            case 1:
                printf("\nEnter number of frames: ");
                scanf("%d", &n);
                printf("Enter number of lost frames: ");
                scanf("%d", &lostCount);
                if (n <= 0 || lostCount < 0 || lostCount > n)
                {
                    printf("Invalid input!\n");
                    break;
                }
                printf("Enter %d lost frame(s): ", lostCount);
                for (i = 0; i < lostCount; i++)
                {
                    scanf("%d", &lost[i]);
                    if (lost[i] < 0 || lost[i] >= n)
                    {
                        printf("Invalid frame number!\n");
                        return 0;
                    }
                }
                stopAndWait(n, lost, lostCount);
                break;

            /* -------- GO BACK N -------- */
            case 2:
                printf("\nEnter number of frames: ");
                scanf("%d", &n);
                printf("Enter window size: ");
                scanf("%d", &w);
                printf("Enter number of lost frames: ");
                scanf("%d", &lostCount);
                if (n <= 0 || w <= 0 || w > n ||
                    lostCount < 0 || lostCount > n)
                {
                    printf("Invalid input!\n");
                    break;
                }
                printf("Enter %d lost frame(s): ", lostCount);
                for (i = 0; i < lostCount; i++)
                {
                    scanf("%d", &lost[i]);
                    if (lost[i] < 0 || lost[i] >= n)
                    {
                        printf("Invalid frame number!\n");
                        return 0;
                    }
                }
                goBackN(n, w, lost, lostCount);
                break;

            /* -------- SELECTIVE REPEAT -------- */
            case 3:
                printf("\nEnter number of frames: ");
                scanf("%d", &n);
                printf("Enter window size: ");
                scanf("%d", &w);
                printf("Enter number of lost frames: ");
                scanf("%d", &lostCount);
                if (n <= 0 || w <= 0 || w > n ||
                    lostCount < 0 || lostCount > n)
                {
                    printf("Invalid input!\n");
                    break;
                }
                printf("Enter %d lost frame(s): ", lostCount);
                for (i = 0; i < lostCount; i++)
                {
                    scanf("%d", &lost[i]);
                    if (lost[i] < 0 || lost[i] >= n)
                    {
                        printf("Invalid frame number!\n");
                        return 0;
                    }
                }
                selectiveRepeat(n, w, lost, lostCount);
                break;

            case 4:
                printf("\nProgram terminated.\n");
                return 0;

            default:
                printf("\nInvalid choice!\n");
        }
    }
    return 0;
}

[24bcs033@mepcolinux cn]$./a.out

========================================
       SLIDING WINDOW PROTOCOLS
========================================

1. Stop-and-Wait ARQ
2. Go-Back-N ARQ
3. Selective Repeat ARQ
4. Exit

Enter your choice: 1

Enter number of frames: 3
Enter number of lost frames: 1
Enter 1 lost frame(s): 1

===== STOP-AND-WAIT ARQ =====
Window Size = 1

Frame 0 transmitted
Frame 0 correctly received
ACK 0 received

Frame 1 transmitted
Frame 1 LOST/CORRUPTED
Timeout occurred for Frame 1
Frame 1 retransmitted
Frame 1 correctly received
ACK 1 received

Frame 2 transmitted
Frame 2 correctly received
ACK 2 received

All frames delivered successfully.
Total transmissions = 4

========================================
       SLIDING WINDOW PROTOCOLS
========================================

1. Stop-and-Wait ARQ
2. Go-Back-N ARQ
3. Selective Repeat ARQ
4. Exit

Enter your choice: 2

Enter number of frames: 5
Enter window size: 3
Enter number of lost frames: 1
Enter 1 lost frame(s): 1

===== GO-BACK-N ARQ =====
Window Size = 3

Transmitting Window: 0 1 2

Frame 0 transmitted
Frame 0 correctly received
ACK 0 received

Frame 1 transmitted
Frame 1 LOST/CORRUPTED
Timeout occurred for Frame 1

Go-Back-N: Retransmitting from Frame 1
Frame 1 retransmitted
Frame 1 correctly received
ACK 1 received
Frame 2 retransmitted
Frame 2 correctly received
ACK 2 received

Transmitting Window: 3 4

Frame 3 transmitted
Frame 3 correctly received
ACK 3 received

Frame 4 transmitted
Frame 4 correctly received
ACK 4 received

All frames delivered successfully.
Total transmissions = 6

========================================
       SLIDING WINDOW PROTOCOLS
========================================

1. Stop-and-Wait ARQ
2. Go-Back-N ARQ
3. Selective Repeat ARQ
4. Exit

Enter your choice: 3

Enter number of frames: 5
Enter window size: 2
Enter number of lost frames: 1
Enter 1 lost frame(s): 1

===== SELECTIVE REPEAT ARQ =====
Window Size = 2

Transmitting Window: 0 1

Frame 0 transmitted
Frame 0 correctly received
ACK 0 received

Frame 1 transmitted
Frame 1 LOST/CORRUPTED
No ACK received for Frame 1

Timeout occurred for Frame 1
Selective Repeat: Retransmitting only Frame 1
Frame 1 retransmitted
Frame 1 correctly received
ACK 1 received

Transmitting Window: 2 3

Frame 2 transmitted
Frame 2 correctly received
ACK 2 received

Frame 3 transmitted
Frame 3 correctly received
ACK 3 received

Transmitting Window: 4

Frame 4 transmitted
Frame 4 correctly received
ACK 4 received

All frames delivered successfully.
Total transmissions = 6

========================================
       SLIDING WINDOW PROTOCOLS
========================================

1. Stop-and-Wait ARQ
2. Go-Back-N ARQ
3. Selective Repeat ARQ
4. Exit

Enter your choice: 4

Program terminated.
