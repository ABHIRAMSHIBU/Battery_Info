#include<stdio.h>
#include<time.h>
#include<signal.h>
#include<stdlib.h>
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
void killer(int sig)
{     system("clear");
        printf("CTRL + C (Signal INT).Exiting.Bye...\n");
      exit(0);
}
char *batt_cont(float a)
{
    a=100.0-a;
   if(a<=25.0)
   {
       return RED "Dying soon!";
   }
   else if(a<=50.0 && a>25.0)
   {
       return MAG "Bad!";
   }
   else if(a<=75.0 && a>50.0)
   {
       return BLU "Good";
   }
   else
   {
       return GRN "Excillent";
   }
}
int run()
{
    FILE *f;
    long long int a;
    float b,c;
    double i=0;
    signal(SIGINT, killer);
    while(1)
    {
        printf("Refreshes :%.0lf\n", ++i);
        printf(GRN "BatteryInfo, program by Abhiram Shibu " RED "[Compiled for x64 with GCC on Arch Linux]\n" RESET);
        f = fopen("/sys/class/power_supply/BAT0/capacity", "r");
        fscanf(f, "%lld", &a);
        fclose(f);
        printf("Current Battery Capacity :" RED "%lld\%\n" RESET,a);
        f = fopen("/sys/class/power_supply/BAT0/energy_now", "r");
        fscanf(f, "%lld", &a);
        fclose(f);
        b=a/1000000.0f;
        printf("Current energy :" RED "%fWh\n" RESET,b);
        f = fopen("/sys/class/power_supply/BAT0/energy_full", "r");
        fscanf(f, "%lld", &a);
        fclose(f);
        b=a/1000000.0f;
        printf("MAX energy :"RED"%fWh\n"RESET,b);
        f = fopen("/sys/class/power_supply/BAT0/energy_full_design", "r");
        fscanf(f, "%lld", &a);
        fclose(f);
        c=a/1000000.0f;
        printf("MAX Energy when Manufactured :"RED"%fWh\n"RESET,c);
        c=((c-b)/c)*100;
        printf("Battery Depletion Level :"RED" %f\%\n"RESET,c);
        printf("Battery condtion :""%s\n" RESET,batt_cont(c));
        usleep(60000L);
        system("clear");
    }
    return 0;
}
