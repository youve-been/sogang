#include <stdio.h>

void main()
{
	char filename1[40], filename2[40];
	char f1, f2;
	int count = 0;
	int total = 0;
	float percent;

	FILE *fp1, *fp2;

	printf("Input first file name : ");
	scanf("%s", filename1);
	printf("Input second file name : ");
	scanf("%s", filename2);

	fp1 = fopen(filename1, "r");
	fp2 = fopen(filename2, "r");
	
	while(1) {
		while(1) {
			f1 = fgetc(fp1);
			if(f1 != 10 && f1!= 32)
				break;
		}
        
		while(1) {
			f2 = fgetc(fp2);
       			if(f2 != 10 && f2 != 32)
            			break;
		}

	   	if(f1 == EOF || f2 == EOF)
	        	break;
	   	if(f1 == f2)
	        	count++;

	   	total++;
	}
	
	percent = ((float)count / total) * 100;
	
	printf("Total character : %d\n", total);
	printf("Same character : %d\n", count);
	printf("%.3f%%\n", percent);
	
	fclose(fp1);
	fclose(fp2);
}
