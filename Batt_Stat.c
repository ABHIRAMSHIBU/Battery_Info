#include<stdio.h>
#include<time.h>
char *batt_cont(float a)
{
    a=100.0-a;
   if(a<=25.0)
   {
       return "Dying soon!";
   }
   else if(a<=50.0 && a>25.0)
   {
       return "Bad!";
   }
   else if(a<=75.0 && a>50.0)
   {
       return "Good";
   }
   else
   {
       return "Excillent";
   }
}
void main()
{
    FILE *f;
    long long int a;
    float b,c;
    while(1)
    {
        printf("BatteryInfo, program by Abhiram Shibu [Compiled for x64 with GCC on Arch Linux]\n");
        f = fopen("/sys/class/power_supply/BAT0/capacity", "r");
        fscanf(f, "%lld", &a);
        fclose(f);
        printf("Current Battery Capacity :%lld\%\n",a);
        f = fopen("/sys/class/power_supply/BAT0/energy_now", "r");
        fscanf(f, "%lld", &a);
        fclose(f);
        b=a/1000000.0f;
        printf("Current energy :%fWh\n",b);
        f = fopen("/sys/class/power_supply/BAT0/energy_full", "r");
        fscanf(f, "%lld", &a);
        fclose(f);
        b=a/1000000.0f;
        printf("MAX energy :%fWh\n",b);
        f = fopen("/sys/class/power_supply/BAT0/energy_full_design", "r");
        fscanf(f, "%lld", &a);
        fclose(f);
        c=a/1000000.0f;
        printf("MAX Energy when Manufactured :%fWh\n",c);
        c=((c-b)/c)*100;
        printf("Battery Depletion Level : %f\%\n",c);
        printf("Battery condtion :%s\n",batt_cont(c));
        system("sleep 0.1");
        system("clear");
    }
}
