#include "mp3_header.h"
void help_mp3()
{
    printf(">> VIEW >>\t ./a.out -v file_name\n");
    printf("-------------------------------------------------------------------------\n");
	printf(">> HELP >>\t ./a.out --help\t(prints this menu)\n");
    printf("-------------------------------------------------------------------------\n");
	printf(">> EDIT >>\t ./a.out -e file_name -[a t A y C c] ""tag_content""\n");
    printf(".........................................................................\n");
	printf("\t[-a] --> Modify Artist Name\n");
	printf("\t[-t] --> Modify Song Title\n");
	printf("\t[-A] --> Modify Album Name\n");
	printf("\t[-y] --> Modify Release Year\n");
	printf("\t[-C] --> Modify Content\n");
	printf("\t[-c] --> Modify Comment\n");
    printf("=========================================================================\n");
    printf("#########################################################################\n");
}