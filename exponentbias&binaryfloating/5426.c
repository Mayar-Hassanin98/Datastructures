#include <stdio.h>
#include <stdlib.h>



void print_binary_char(char c)
{

    int mask = 0x80;
    while (mask>0)
    {
        printf("%d", (c & mask) > 0 );
        mask >>= 1;
    }
}


void question1()
{
    printf("printing from -16 to 15 in binary\n");
    char c;
    for(c=-16; c<16; c++)
    {

        printf("%d\t",c);
        print_binary_char(c);
        printf("\n");

    }


}


void print_binary_float(float f)
{
    union test
    {
        float p;
        unsigned char s[4];
    };

    union test t1;
    t1.p=f;
    for (int i=3; i>=0; i--)

        printf("%02x",t1.s[i]);//my machine print the data by little endians first


}
void question2()
{

    float numbers[] = {0.0f, 1.0f, 2.0f, 0.1f};

    int count =sizeof (numbers)/sizeof (numbers[0]);
    int i;
    for(i=0; i<count; i++)
    {
        printf("%.2f is represented as:",numbers[i]);
        print_binary_float(numbers[i]);
        printf("\n");
    }


}


float get_smallest_positive_float()
{
    union test
    {
        float x;
        unsigned char s[4];


    };

    union test t1;

    t1.s[0]=0x00;
    t1.s[1]=0x00;
    t1.s[2]=0x80;
    t1.s[3]=0x00;
    printf("%1e",t1.x);
    return 0;
}


double get_double_epsilon()
{
    typedef union
    {
        unsigned long i;
        double d;
    } myDouble;
    printf("----double: (bits) 1 sign + 11 exp +52 mantissa=%dbytes\n",sizeof(double));
    myDouble m;
    m.d=1.0;
    m.i++;
    double x=m.d-1.0;
    printf("eps_double=%le\n",x);
    return 0;
}


int get_longdouble_exponent_bias()
{  int count=0;
   union test
    {
        long double x;
       unsigned char s[12];
};
    union test t1;
t1.x=1.0;

   for(int i=9; i>=0; i--)
        printf("%02x",t1.s[i]);


 int mask = 0x80;
 for(int i=9; i>=0; i--){

mask = 0x80;
    while (mask>0)
    {
        if( (t1.s[i]& mask) > 0 )
        count++;
        mask >>= 1;
    }
 }

printf("\ncount of ones =%d",(count));
int z=pow(2,count)-1;
printf("\n%d",z);

return 0;

}


void question3()
{

    printf("the smallest positive 'float' is :%f\n",
           get_smallest_positive_float());

    printf("Epsilon for 'double' is :%1d\n",get_double_epsilon());

printf("long double has a bias of %d for its exponent\n",get_longdouble_exponent_bias());


}

int get_command() {
int choice;
printf("\n\n");
printf("*********************************************\n");
printf("* Enter 1 for Signed Integer Representation *\n");
printf("* Enter 2 for Floating-Point Endianness *\n");
printf("* Enter 3 for Floating-Point Representation *\n");
printf("* Enter anything else to exit *\n");
printf("*********************************************\n");
printf("Your choice: ");
scanf("%d", &choice);
fseek(stdin, 0, SEEK_END);
printf("\n");
return choice;
}
/*
*
*/
main() {
int choice;
while(1) {
switch(get_command()) {
case 1:
question1();
break;
case 2:
question2();
break;
case 3:
question3();
break;
default:
printf("Invalid Choice. Exiting...\n");
exit(1);
}
}
return 0;
}












