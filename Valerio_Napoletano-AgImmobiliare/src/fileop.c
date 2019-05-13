/*
 * fileop.h
 *
 *  Created on: 11 mag 2019
 *      Author: Giuseppe Napoletano
 */

//Operazioni su immobili
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "datatypes.h"


int addbuild(){
    FILE *fp_build;
    fp_build = fopen ("buildings.dat", "a+b");

    checkFile(fp_build);
    if (fp_build!=NULL){
    	infoBuild(fp_build);
    }

    fclose(fp_build);

    return -1;
}
int editbuild(){
	int count = 0; //File rows counter
	int stop = 0; //Valid choice controller
	int choice = 0;
	FILE *fp_build;
	FILE *fp_temp;

	fp_build = fopen ("buildings.dat", "rb");
	checkFile(fp_build);
	if (fp_build!=NULL){
		count = countRows(fp_build);
	    fclose (fp_build);

	    fp_build = fopen ("buildings.dat", "rb");
	    checkFile(fp_build);

	    fp_temp = fopen ("temp_build.dat", "w+b");
	    stop = checkFile(fp_temp);

	    if(count>0 && stop == 0){
		    do{
		    	newLine();
			    printf("Inserisci il numero dell'immobile da modificare: \n");
			    scanf("%d",&choice);

			    if(choice <= count){
			    	copyFile(fp_build, fp_temp, choice);

				    fclose (fp_temp);
				    fclose (fp_build);

				    fp_build = fopen ("buildings.dat", "w+b");
				    fp_temp = fopen ("temp_build.dat", "rb");

				    copyFile(fp_temp, fp_build, 0);

				    stop=0;
			      }
			      else{
			    	  printf("\nYou must enter a valid number.\n");
			    	  stop=1;
			      }
		      }while(stop==1);
	      }
	      else{
	    	  printf("\n---- WARNING ----");
	    	  printf("\nNo data found.\n");
	      }

	      fclose (fp_temp);
	      fclose (fp_build);
	      remove("temp_building.dat");
	}
	return -1;
}
int removebuild(){
	int count = 0; //File rows counter
	int stop = 0; //Valid choice controller
	int choice = 0;
	FILE *fp_build;
	FILE *fp_temp;

	fp_build = fopen ("buildings.dat", "rb");
	if (fp_build==NULL){
		printf("\n------------------------ WARNING ------------------------");
		printf("\nBuilding store file does not exist. Create new one first\n");
	}
	else{
		char line [ 400 ];
	    while ( fgets ( line, sizeof line, fp_build ) != NULL ) /* read a line */
	    {
	    	printf("%d. ", count+1);
	    	fputs ( line, stdout ); /* write the line */
	    	count++;
	    }
	    fclose (fp_build);
	    fp_build = fopen ("buildings.dat", "rb");
	    fp_temp = fopen ("temp_build.dat", "w+b");
	    if(count>0){
	    	do{
	    		newLine();
	    		printf("Inserisci il numero dell'immobile da eliminare: \n");
			    scanf("%d",&choice);
			    if(choice <= count){
			    	count = 0;
				    while ( fgets ( line, sizeof line, fp_build ) != NULL ) /* read a line */
				    {
				    	count++;
				    	if(choice != count){
				    		fputs( line, fp_temp);
				    	}
				    }
				    fclose (fp_temp);
				    fclose (fp_build);
				    fp_build = fopen ("buildings.dat", "w+b");
				    fp_temp = fopen ("temp_build.dat", "rb");

				    while ( fgets ( line, sizeof line, fp_temp ) != NULL ) /* read a line */
				    {
				    	fputs( line, fp_build);
				    }
				    stop=0;
			    }
			    else{
			    	printf("\nYou must enter a valid number.\n");
			    	stop = 1;
			    }
	    	}while(stop==1);
	    }
	}
	fclose (fp_temp);
	fclose (fp_build);
	remove("temp_building.dat");

	return -1;
}
