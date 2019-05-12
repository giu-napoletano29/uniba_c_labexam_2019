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

	int ret = 0;

    FILE *fp_build;

    do{
		fp_build = fopen ("buildings.dat", "a+b");
		if (fp_build==NULL){
			printf("\n------------------------ WARNING ------------------------");
			printf("\nBuilding store file does not exist. Creating new one....\n");

			fp_build = fopen ("buildings", "w+");
			if (fp_build==NULL){
				printf("\n------------------------------------ ERROR ------------------------------------");
				printf("\nAn error as occured while creating the file. Check your file system and retry.\n");
			}
			else{
				ret = 1;
				fclose (fp_build);
			}
		}
		else{
			property p;
			//TODO: need to handle escape characters
			printf("Inserisci l'ID dell'immobile: \n");
			scanf("%d",&p.id);
			printf("Inserisci il nome dell'immobile: \n");
			scanf("%s", p.name);
			printf("Inserisci la localita': \n");
			scanf("%s", p.locality);
			printf("Inserisci il prezzo: \n");
			scanf("%d", &p.price);
			printf("Inserisci la data: \n");
			scanf("%hd %hd %hd", &p.reg_date.day, &p.reg_date.month, &p.reg_date.year);	//TODO: Inserire controllo data


			fprintf(fp_build, "%d, %s, %s, %d, %hd/%hd/%hd\n", p.id, p.name, p.locality, p.price, p.reg_date.day, p.reg_date.month, p.reg_date.year);
			ret = 0;
			fclose (fp_build);
		}
    }while(ret == 1);
    return -1;
}
int editbuild(){

	int count = 0; //File rows counter
	int stop = 0; //Valid choice controller
	int choice = 0;
	FILE *fp_build;
	FILE *fp_temp;
	property p;

	fp_build = fopen ("buildings.dat", "rb");
	if (fp_build==NULL){
		printf("\n------------------------ WARNING ------------------------");
		printf("\nBuilding store file does not exist. Create new one first\n");

		/*
		fp_build = fopen ("buildings.txt", "w+");
		if (fp_build==NULL){
			printf("\n------------------------------------ ERROR ------------------------------------");
			printf("\nAn error as occured while creating the file. Check your file system and retry.\n");
		}
		else{
			fclose (fp_build);
		}*/
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
	      //count = 0;
	      if(count>0){
		      do{
		    	  newLine();
			      printf("Inserisci il numero dell'immobile da modificare: \n");
			      scanf("%d",&choice);

			      if(choice <= count){

			    	  count = 0;
				      while ( fgets ( line, sizeof line, fp_build ) != NULL ) /* read a line */
				      {
				    	  count++;

				    	  if(choice == count){
				    		  printf("Inserisci l'ID dell'immobile: \n");
				    		  scanf("%d",&p.id);
				    		  printf("Inserisci il nome dell'immobile: \n");
				    		  scanf("%s", p.name);
				    		  printf("Inserisci la localita': \n");
				    		  scanf("%s", p.locality);
				    		  printf("Inserisci il prezzo: \n");
				    		  scanf("%d", &p.price);
				    		  printf("Inserisci la data: \n");
				    		  scanf("%hd %hd %hd", &p.reg_date.day, &p.reg_date.month, &p.reg_date.year);	//TODO: Inserire controllo data

				    		  fprintf(fp_temp, "%d, %s, %s, %d, %hd/%hd/%hd\n", p.id, p.name, p.locality, p.price, p.reg_date.day, p.reg_date.month, p.reg_date.year);

				    	  }
				    	  else{
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
			    	  stop=1;
			      }
		      }while(stop==1);
	      }
	      else{
	    	  printf("\n---- WARNING ----");
	    	  printf("\nNo data found.\n");
	      }

	      count = 0;
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
