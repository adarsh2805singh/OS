#include<stdio.h>
int main(){
    int n;
    printf("Enter the number of processors:");
    scanf("%d",&n);
    int at[n],bt[n],ct[n],tat[n],wt[n];
    printf("Enter the arrival time & burst time\n");
    for(int i=0;i<n;i++){
        printf("Processor %d\n",i+1);
        printf("Arrival Time:\n");
        scanf("%d",&at[i]);
        printf("Burst Time:\n");
        scanf("%d",&bt[i]);
    }

    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(at[i]>at[j]){
                int temp =at[i];
                at[i]=at[j];
                at[j]=temp;
                temp=bt[i];
                bt[i]=bt[j];
                bt[j]=temp;
            }
        }
    }

    ct[0]=at[0]+bt[0];
    for(int i=1;i<n;i++){
        if(ct[i-1]<at[i])
            ct[i]=at[i] + bt[i];
        else
            ct[i]=ct[i-1]+bt[i];
    }

    for(int i=0;i<n;i++){
        tat[i]=ct[i]-at[i];
    }
    for(int i=0;i<n;i++){
        wt[i]=tat[i]-bt[i];
    }

    float total_tat=0,total_wt=0;
    printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],ct[i],tat[i],wt[i]);
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("\nAverage Waiting Time: %.2f", (float)total_wt/n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_tat/n);

    return 0;
}
