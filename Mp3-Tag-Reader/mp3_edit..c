//Name: Aswin chandra M A

#include "mp3_header.h"
void edit_mp3(char song[], char tag[], char content[])
{
    char tagEdit[5];
    //assign tagname to the curesponding option given
    if(strcmp(tag, "-a") == 0)
    strcpy(tagEdit, "TPE1");

    else if(strcmp(tag, "-t") == 0)
    strcpy(tagEdit, "TIT2");

    else if(strcmp(tag, "-A") == 0)
    strcpy(tagEdit, "TALB");

    else if(strcmp(tag, "-y") == 0)
    strcpy(tagEdit, "TYER");

    else if(strcmp(tag, "-C") == 0)
    strcpy(tagEdit, "TCON");

    else if(strcmp(tag, "-c") == 0)
    strcpy(tagEdit, "COMM");
    else
    {
    printf("|                        Invalid tag option                             |\n");
    return;
    } 
     printf("%s\t>>>\tEditing %s\n", song, tagEdit);
    printf("=========================================================================\n");

    //create a temporary file
    FILE * tp = fopen("temp.mp3", "wb");

    //open the mp3 file in read mode
    FILE * fp = fopen(song, "rb");
    if(fp == NULL)
    {
        printf("                     File not found in the folder!!                     |\n");
        printf("=========================================================================\n");
        return;
    }
    char id3[10];
    //copy header(10bytes) from original to temperory file 
	fread(id3, (sizeof(id3)), 1, fp);
    fwrite(id3, (sizeof(id3)), 1, tp);

    //in loop find the required tag and replace that with given content
    for(int i = 0; i < 6; i++)
    {
        char TAG[5];
        //read and write tag
	    fread(TAG, (sizeof(TAG)-1), 1, fp);
	    TAG[4] = '\0';  
        fwrite(TAG,(sizeof(TAG) - 1), 1, tp);
        //if tag matches to user given tag, write that given content.
        if(strcmp(TAG, tagEdit) ==0)
        {  
            int size = strlen(content) + 1;
            int temp_size = size -1;
            size = convert(size); 
            fwrite(&size, 1,sizeof(size), tp);
            char flag[2];
            int og_size;
            fread(&og_size,sizeof(og_size),1,fp);
            fread(flag,2,1,fp);
            fwrite(flag,2,1,tp);
            char null = '\0';
            fwrite(&null, 1, 1, tp);
            fwrite(content, temp_size, 1, tp);
            og_size=convert(og_size);
            fseek(fp,og_size,SEEK_CUR);
            break;
        }
        //else copy the size and content from original file
        else
        {
            int size;
            fread(&size,4,1,fp);
            fwrite(&size,4,1,tp);
            size=convert(size);

            char flag[2];
            fread(flag,2,1,fp);
            fwrite(flag,2,1,tp);

            char content2[size];
            fread(content2,size,1,fp);
            fwrite(content2,size,1,tp);
        }
    }
    char buffer[1];
    //copy all the remaining bytes as it is one by one
    while(fread(buffer, 1, (sizeof(buffer)), fp))
    {
        fwrite(buffer, 1, sizeof(buffer), tp);
    }
    fclose(fp);
    fclose(tp);
    //remove the original file and rename edited file to original
    remove(song);
    rename("temp.mp3",song);
    printf("          ####           File edited succesfully           ###\n");
    printf("=========================================================================\n");
    printf("#########################################################################\n");
}