#include <stdio.h>
#include <conio.h>

void wait_time(int waittime[],int bursttime[],char proc[],int n)
{
    int wait_sum=0;
    float wait_avg=0.0;
    waittime[0]=0;
    int i,j;
    for(j=1;j<n;j++)
    {
        waittime[j]=waittime[j-1]+bursttime[j-1];
        wait_sum=wait_sum+waittime[j];
    }
    wait_avg=wait_sum/n;

    printf("Wait time for processors are:\n");
    printf("Processor name \t Wait time \n");
    for(i=0;i<n;i++)
    {
         printf("%c \t %d \n",proc[i],waittime[i]);
    }

    printf("Äverage wait time for processors is: %f \n",wait_avg );

}

void turnaround_time(int waittime[],int turntime[],int bursttime[],char proc[],int n)
{
    int turn_sum=0;
    float turn_avg=0.0;
    int i,j;
    for(j=0;j<n;j++)
    {
       turntime[j]=waittime[j]+bursttime[j];
       turn_sum=turn_sum+turntime[j];
    }
     turn_avg=turn_sum/n;

    printf("Turnaround time for processors are:\n");
    printf("Processor name \t Turnaround time \n");
    for(i=0;i<n;i++)
    {
         printf("%c \t %d \n",proc[i],turntime[i]);
    }
    printf("Äverage turnaround time for processors is: %f \n",turn_avg );

}

void main()
{
    char proc[10];
    int bursttime[10];
    int waittime[10];
    int turntime[10];
    int n,i,j;
    printf("Enter the number of processors \t");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("Enter the name of processor \t");
        scanf("%s",&proc[i]);
        printf("Enter the burst time \t");
        scanf("%d",&bursttime[i]);
    }
    wait_time(waittime,bursttime,proc,n);
    turnaround_time(waittime,turntime,bursttime,proc,n);

}
