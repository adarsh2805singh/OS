#include <stdio.h>

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], ct[n], tat[n], wt[n], rt[n];
    int completed[n];

    for(int i = 0; i < n; i++) {
        pid[i] = i + 1;
        completed[i] = 0;

        printf("Enter Arrival Time and Burst Time for Process %d: ", pid[i]);
        scanf("%d %d", &at[i], &bt[i]);
    }

    int currentTime = 0;
    int count = 0;

    float total_ct = 0, total_tat = 0, total_wt = 0, total_rt = 0;

    while(count < n) {

        int shortest = -1;
        int min_bt = 9999;

        for(int i = 0; i < n; i++) {

            if(at[i] <= currentTime &&
               completed[i] == 0 &&
               bt[i] < min_bt) {

                min_bt = bt[i];
                shortest = i;
            }
        }

        if(shortest == -1) {
            currentTime++;
            continue;
        }

        rt[shortest] = currentTime - at[shortest];

        ct[shortest] = currentTime + bt[shortest];

        tat[shortest] = ct[shortest] - at[shortest];

        wt[shortest] = tat[shortest] - bt[shortest];

        currentTime = ct[shortest];

        completed[shortest] = 1;
        count++;

        total_ct += ct[shortest];
        total_tat += tat[shortest];
        total_wt += wt[shortest];
        total_rt += rt[shortest];
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i],
               ct[i], tat[i], wt[i], rt[i]);
    }

    printf("\nAverage Completion Time = %.2f", total_ct / n);
    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Response Time = %.2f\n", total_rt / n);

    return 0;
}
