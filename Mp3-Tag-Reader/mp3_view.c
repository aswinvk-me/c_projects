
/*
 * Name: Aswin chandra M A
 */

#include "mp3_header.h"
char *name[6] = {"Title", "Artist", "Album", "Year", "Content", "Comment"};
void view_mp3(char song[])
{
   	//open the file in read mode

	FILE * fp = fopen(song, "rb");
	if(fp == NULL)
	{
		printf("|                      The file does not exist!!                        |\n");
		printf("=========================================================================\n");
		printf("#########################################################################\n");
		return;
	}

	//read first 3 bytes from the file (to check if the file is mp3 or not by checking IDV3)
	char id3[4];
	fread(id3, (sizeof(id3) - 1), 1, fp);

	//id3 ->will have data ID3'\0' if mp3


	if(strcmp(id3, "ID3") ==0)
	{
		printf("%s\to|-_-|o\n", song);
		printf(".........................................................................\n");
	}
	else
	{
		printf("|                       File is not an mp3!!!                           |\n");
		printf("=========================================================================\n");
		printf("#########################################################################\n");
		return;
	}
		
	//skip the next 7 bytes
	fseek(fp,7,SEEK_CUR);

for(int i  = 0 ; i < 6 ; i++)
{

	//read the 4 bytes
	char TAG[5];
	fread(TAG, (sizeof(TAG)-1), 1, fp);
	TAG[4] = '\0';

	int size;
	fread(&size, sizeof(size), 1, fp);
	
	//convert the number in litte endian to big endian using function
	size = convert(size);
	
	 //skip 3 bytes(2flag and 1 null)
	 fseek(fp, 3, SEEK_CUR);
	 char content[size];
	 //read size - 1 no of bytes from file
	 fread(content, size - 1, 1, fp);
	 content[size - 1] = '\0';
	 printf("%s\t:\t%s\n", name[i], content);
	 //repeat the proces 6 times for 6 tags and print
}
printf("=========================================================================\n");
printf("#########################################################################\n");
fclose(fp);
}
int convert(int size)
{
	char*ptr = (char *)&size;
	//swap the bytes using a loop
	for(int i = 0; i < sizeof(int)/2; i++)
	{
		char temp = ptr[i];
		ptr[i] = ptr[sizeof(int) - i - 1];
		ptr[sizeof(int) - i - 1] = temp;

	}
	return size;
}
