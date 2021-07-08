#include <stdio.h>
#include <string.h>
#include "dump.h"
void dump(char *buffer,int len)
{
	for(int i=1;i<=len;i++)
	{
		printf("%02x ",buffer[i-1]);
		if(i%16==0 || i==len)
		{	
			/* to pad the space if buffer ends before reaching the 16 bit mark */
			if((i==len) && !(i%16==0))
			{
				for(int j=1; j <= 16-(i%16);j++){
					printf("   ");
				}
			}
			printf("| ");
			int offset;
			if((i%16)==0)
				 offset=i-16;
			else  offset = i-(i%16);
			int counter=offset;
			for(int k=0;k<i-offset;k++){
				if(buffer[counter] > 32 && buffer[counter] < 127){
				   printf("%c",buffer[counter]);	   
				}
				else printf(".");
				counter++;
			}
			printf("\n");
		}
	}
}

