#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
FILE* fp;
FILE* fp1;
FILE* fp2;
FILE* fp3;

//long int period = 20000L;
unsigned char maska;
char *str1;
char *str2;
char lval1,lval2,lval3,lval4;
char btn3, btn2, btn1, btn0;
char sw1, sw0;
size_t num_of_bytes = 6;
int x;
int novo=0;
int staro=0;

while(1)
{


fp1 = fopen("/dev/switch", "r");
if(fp1==NULL)
{
puts("problem pri otvaranju fajla switch");
return -1;
}
str1 = (char *)malloc(num_of_bytes + 1);
getline(&str1, &num_of_bytes, fp1);

if(fclose(fp1))
{
puts("problem pri zatvaranju fajla switch");
return -1;
}

sw1 = str1[4] - 48;
sw0 = str1[5] - 48;
free(str1);

if(sw1 == 0 && sw0 == 0)
x = 0;
else if(sw1 == 0 && sw0 == 1)
x = 1;
else if(sw1 == 1 && sw0 == 0)
x = 2;
else
x = 3;


fp2 = fopen("/dev/button", "r");
if(fp2==NULL)
{
puts("problem pri otvaranju fajla button");
return -1;
}
str2 = (char *)malloc(num_of_bytes + 1);
getline(&str2, &num_of_bytes, fp2);

if(fclose(fp2))
{
puts("problem pri zatvaranju fajla button");
return -1;
}

btn3 = str2[2] - 48;
btn2 = str2[3] - 48;
btn1 = str2[4] - 48;
btn0 = str2[5] - 48;
free(str2);

novo = 0;
if(btn3) novo=1;
if(btn2) novo=2;
if(btn1) novo=3;
if(btn0) novo=4;


										//Citanje vrednosti dioda
                                        fp = fopen ("/dev/led", "r");
                                        if(fp==NULL)
                                        {
                                                puts("Problem pri otvaranju /dev/led\n");
                                                return -1;
                                        }
                                        str = (char *)malloc(num_of_bytes+1);
                                        getline(&str, &num_of_bytes, fp);
                                        if(fclose(fp))
                                        {
                                                puts("Problem pri zatvaranju /dev/led\n");
                                                return -1;
                                        }
			
			
										lval1 = str[2] - 48;
                                        lval2 = str[3] - 48;
                                        lval3 = str[4] - 48;
                                        lval4 = str[5] - 48;
                                        free(str);

                                        if(lval1==0 && lval2==0 && lval3==0 && lval4==1 )
                                                maska=0x01;
                                        if(lval1==0 && lval2==0 && lval3==1 && lval4==0 )
                                                maska=0x02;
                                        if(lval1==0 && lval2==1 && lval3==0 && lval4==0 )
                                                maska=0x04;
                                        if(lval1==1 && lval2==0 && lval3==0 && lval4==0 )
                                                maska=0x08;
                                        


if(novo != staro && novo !=0)
{
	switch(novo)
	{
	case 1:
		fp3 = fopen ("/dev/led", "w");
        if(fp==NULL)
        {
            puts("Problem pri otvaranju /dev/led tokom upisa\n ");
            return -1;
        }
		fputs("0x08", fp3);
		if(fclose(fp3))
        {
            puts("Problem pri zatvaranju /dev/led tokom upisa\n");
            return -1;
        }
	break;
	case 2:
		maska=maska<<x;
		fp3 = fopen ("/dev/led", "w");
        if(fp==NULL)
        {
            puts("Problem pri otvaranju /dev/led tokom upisa\n ");
            return -1;
        }
		fputs(maska, fp3);
		if(fclose(fp3))
        {
            puts("Problem pri zatvaranju /dev/led tokom upisa\n");
            return -1;
        }
	
	
	break;	
	case 3:
		maska=maska>>x;
		fp3 = fopen ("/dev/led", "w");
        if(fp==NULL)
        {
            puts("Problem pri otvaranju /dev/led tokom upisa\n ");
            return -1;
        }
		fputs(maska, fp3);
		if(fclose(fp3))
        {
            puts("Problem pri zatvaranju /dev/led tokom upisa\n");
            return -1;
        }

	
	
	break;
	case 4:
		fp3 = fopen ("/dev/led", "w");
        if(fp==NULL)
        {
            puts("Problem pri otvaranju /dev/led tokom upisa\n ");
            return -1;
        }
		fputs("0x01", fp3);
		if(fclose(fp3))
        {
            puts("Problem pri zatvaranju /dev/led tokom upisa\n");
            return -1;
        }
	break;
	}
}
staro=novo;
usleep(1000);
}
}
