#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

int printu(u32 x);
int printd(int x);
int rpu(int x);
char prints(char *s);
int printo(u32 x);
int printx(u32 x);
int toOctal(u32 x);
int mymain(int argc, char *argv[], char *env[]);

int rpuo(u32 x);
int Myprintf(char *format, ...);

int BASE = 10;

char *table = "0123456789ABCDEF";

/*int main(int argc, char *argv[], char *env[])
{
//    mymain(argc, argv, env);
}*/

int printu(u32 x) // prints a 32 bit unsigned integer
{
    if (x == 0)
        putchar('0');
    else
        rpu(x);
    putchar(' ');
}

int printd(int x) // prints an integer
{
    if (x == 0)
        putchar('0');
    else if (x < 0)
    {
        x = abs(x);
        putchar('-');
        rpu(x);       
    }

    else
        rpu(x);
    
    //putchar(' ');
}

char prints(char *s) // prints a string
{
    int i = 0;

    while (s[i] != '\0')
    {
        putchar(s[i]);
        i++;
    }
}

int rpu(int x)
{  
    char c; 
    if (x)
    {
        c = table[x % BASE];        
        rpu(x / BASE);                   
        putchar(c);
    }
} 


int rpuo(u32 x)
{  
    char c; 
    if (x)
    {
        c = table[x % BASE];        
        rpu(x / BASE);                   
        putchar(c);
    }
} 

int printo(u32 x)
{
    int octal = toOctal(x);
    
    if (octal == 0)
        putchar('0');
    else
        rpuo(octal);
    
    putchar(' ');
}

int toOctal(u32 x)
{
    int rem, i=1, octal=0;    
    while (x != 0)            
    {                
        rem = x%8;     
        x /= 8;                
        octal += rem*i;             
        i *= 10;
    }
       
    return octal;
}

int printx(u32 x)
{
   /* char *hexadecimalNumber = '\0';
    hexadecimalNumber = toHex(x);

    prints(hexadecimalNumber);
}

char *toHex(u32 x)
{*/
    u32 quotient, temp;
    int i = 0, j = 0;
    char hexadecimalNumber[100] = {'\0', '\0', '\0'};

    quotient = x;

    while(x != 0)
    {
        temp = x % 16;                
        //To convert integer into character       
        if(temp < 10)                       
            temp += 48;
        else                          
            temp += 55;

        hexadecimalNumber[i++]= temp;
        x /= 16;                                     
    }
    char finalHex[100] = {'\0', '\0', '\0'};

    while (hexadecimalNumber[i] != '\0')
        i++;

    i--;

    while (i >= 0)
    {
        finalHex[j] = hexadecimalNumber[i];
        j++;
        i--;
    }
    
    putchar('0');
    putchar('x'); 
    prints(finalHex);

  //  return hexadecimalNumber;
}

int Myprintf(char* format, ...) 
{ 
	char *traverse; 
	unsigned int i; 
	char *s; 
	
	//Initializing Myprintf's arguments 
	va_list arg; 
	va_start(arg, format); 
	
	for(traverse = format; *traverse != '\0'; traverse++) 
	{ 
		while(*traverse != '%' && *traverse != '\n') 
		{ 
			putchar(*traverse);
			traverse++; 
		} 
	    
        if (*traverse == '\n')
        {
            putchar('\n');
        }

        else
        {    
            traverse++; 
            
            switch(*traverse) 
            { 
                case 'c' : i = va_arg(arg, int);		//Fetch char argument
                            putchar(i);
                            break; 
                            
                case 'd' : i = va_arg(arg, int);        //Fetch Decimal/Integer argument
                           printd(i);	
                           break; 
                            
                case 'o': i = va_arg(arg,unsigned int); //Fetch Octal representation
                            printo(i);
                            break; 
                            
                case 's': s = va_arg(arg,char *); 		//Fetch string
                            prints(s); 
                            break; 
                            
                case 'x': i = va_arg(arg,unsigned int); //Fetch Hexadecimal representation
                            printx(i);
                            break;
            }
    
        } 
    }

    va_end(arg);
}

int mymain(int argc, char *argv[], char *env[])
{
    int i = 0;

    Myprintf("---------- Printing Command Line Parameters ---------\n");   
    
    Myprintf("argc: %d\n", argc);

    for (i = 0; i < argc; i++)
    {
        Myprintf("argv[%d] = %s\n", i, argv[i]);
    }

    Myprintf("\n---------- Printing env Strings ---------\n");   
    
    char** envp;  
    for (i = 0; *env != 0; env++, i++)        
    {            
        char* thisEnv = *env;
        printf("env[%d] = %s\n", i, *env);
    }

    Myprintf("\n---------- Printing PATH and HOME ---------\n");   
    
    const char *path = getenv("PATH"), *home = getenv("HOME");
    
    if (path != NULL)
        Myprintf("PATH: %s\n", path);
    else
        Myprintf("PATH returned NULL\n");

    if (home != NULL)
        Myprintf("HOME: %s\n", home);
    else
        Myprintf("HOME returned NULL\n");

    Myprintf("\n---------- testing YOUR myprintf() ---------\n");   
    Myprintf("this is a test\n");      
    Myprintf("testing a=%d b=%x c=%c s=%s\n", 123, 123, 'a', "testing");         
    Myprintf("string=%s, a=%d  b=%u  c=%o  d=%x\n",                    
            "testing string", -1024, 1024, 1024, 1024);            
    Myprintf("mymain() return to main() in assembly\n"); 
}
