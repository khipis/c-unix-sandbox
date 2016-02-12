/* kompilacja: gcc -lpthread -o watki watki.c*/
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 

pthread_t filozof[5];pthread_mutex_t widelec[5]={PTHREAD_MUTEX_INITIALIZER , PTHREAD_MUTEX_INITIALIZER , PTHREAD_MUTEX_INITIALIZER , PTHREAD_MUTEX_INITIALIZER , PTHREAD_MUTEX_INITIALIZER};

/*
filozof0 jest asymetryczny i podnosi najpierw prawy widelec.
Nie wystepuje w tym rozwiazaniu mozliwosc zakleszczenia jednak filozow0 jest uprzywilejowany poniewaz nikt inny nie podnosi w pierwszej kolejnosci jego widelcow. Dostep niesprawiedliwy. Moze wystawic zaglodzenie.
*/


void *filozof0() {
while(1){
	if(!pthread_mutex_lock(&widelec[4])){ //Najpierw prawy
		puts("F0: podnosi prawy widelec");
		while(1)
		if(!pthread_mutex_lock(&widelec[0])){ //Potem lewy
			puts("F0: podnosi lewy widelec. JE");
			pthread_mutex_unlock(&widelec[4]);
			pthread_mutex_unlock(&widelec[0]);
			sleep(2);
			break;
		}
	}
}
}
void *filozof1() {
while(1){
	if(!pthread_mutex_lock(&widelec[1])){
		puts("F1: podnosi lewy widelec");
		while(1)
		if(!pthread_mutex_lock(&widelec[0])){
			puts("F1: podnosi prawy widelec. JE");
			pthread_mutex_unlock(&widelec[0]);
			pthread_mutex_unlock(&widelec[1]);
			sleep(1);
			break;
		}
	}
}}
void *filozof2() {
while(1){
	if(!pthread_mutex_lock(&widelec[2])){
		puts("F2: podnosi lewy widelec");
		while(1)
		if(!pthread_mutex_lock(&widelec[1])){
			puts("F2: podnosi prawy widelec. JE");
			pthread_mutex_unlock(&widelec[1]);
			pthread_mutex_unlock(&widelec[2]);
			sleep(1);
			break;
		}
	}
}
}
void *filozof3() {
while(1){
	if(!pthread_mutex_lock(&widelec[3])){
		puts("F3: podnosi lewy widelec");
		while(1)
		if(!pthread_mutex_lock(&widelec[2])){
			puts("F3: podnosi prawy widelec. JE");
			pthread_mutex_unlock(&widelec[2]);
			pthread_mutex_unlock(&widelec[3]);
			sleep(2);
			break;
		}
	}
}
}
void *filozof4() {
while(1){
	if(!pthread_mutex_lock(&widelec[4])){
		puts("F4: podnosi lewy widelec");
		while(1)
		if(!pthread_mutex_lock(&widelec[3])){
			puts("F4: podnosi prawy widelec. JE");
			pthread_mutex_unlock(&widelec[3]);
			pthread_mutex_unlock(&widelec[4]);
			sleep(3);
			break;
		}
	}
}
}

int main(){
 
if ( pthread_create( &filozof[0], NULL, filozof0,NULL) ){puts("Error while creating 0\n"); exit(1);}
if ( pthread_create( &filozof[1], NULL, filozof1,NULL) ){puts("Error while creating 1\n"); exit(1);}
if ( pthread_create( &filozof[2], NULL, filozof2,NULL) ){puts("Error while creating 2\n"); exit(1);}
if ( pthread_create( &filozof[3], NULL, filozof3,NULL) ){puts("Error while creating 3\n"); exit(1);}
if ( pthread_create( &filozof[4], NULL, filozof4,NULL) ){puts("Error while creating 4\n"); exit(1);}


if ( pthread_join ( filozof[0], NULL ) ) {puts("Error while ending 0\n");exit(1);}
if ( pthread_join ( filozof[1], NULL ) ) {puts("Error while ending 1\n");exit(1);}
if ( pthread_join ( filozof[2], NULL ) ) {puts("Error while ending 2\n");exit(1);}
if ( pthread_join ( filozof[3], NULL ) ) {puts("Error while ending 3\n");exit(1);}
if ( pthread_join ( filozof[4], NULL ) ) {puts("Error while ending 4\n");exit(1);}

return 0;
}

