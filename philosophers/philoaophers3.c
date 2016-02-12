#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 

sem_t sem;

void SLEEP(int x){
int i=0;
for(i=0;i<x;i++);
}

pthread_t filozof[5];
pthread_mutex_t widelec[5]={
PTHREAD_MUTEX_INITIALIZER,
PTHREAD_MUTEX_INITIALIZER,
PTHREAD_MUTEX_INITIALIZER, 
PTHREAD_MUTEX_INITIALIZER, 
PTHREAD_MUTEX_INITIALIZER
};

/*
Wprowadzenie semaforu zliczajacego eleminuje zjawisko zakleszczenia gdyz
tylko 4 filozofow naraz moze rywalizowac o widelce wiec nie nastapi sytuacja ze wszyscy filozofowie podniosa naraz lewy widelec.
*/


void *filozof0() {
while(1){
sem_wait(&sem);//Podnosimy semafor
	if(!pthread_mutex_lock(&widelec[0])){
		puts("F0: podnosi lewy widelec");
		while(1)
		if(!pthread_mutex_lock(&widelec[4])){
			puts("F0: podnosi prawy widelec. JE");
			pthread_mutex_unlock(&widelec[4]);
			pthread_mutex_unlock(&widelec[0]);
			SLEEP(10000);
			break;
		}
	}
sem_post(&sem);//Opuszczamy semafor
}
}
void *filozof1() {
while(1){
sem_wait(&sem);//Podnosimy semafor
	if(!pthread_mutex_lock(&widelec[1])){
		puts("F1: podnosi lewy widelec");
		while(1)
		if(!pthread_mutex_lock(&widelec[0])){
			puts("F1: podnosi prawy widelec. JE");
			pthread_mutex_unlock(&widelec[0]);
			pthread_mutex_unlock(&widelec[1]);
			SLEEP(7000);
			break;
		}
	}
sem_post(&sem);//Opuszczamy semafor
}
}
void *filozof2() {
while(1){
sem_wait(&sem);//Podnosimy semafor
	if(!pthread_mutex_lock(&widelec[2])){
		puts("F2: podnosi lewy widelec");
		while(1)
		if(!pthread_mutex_lock(&widelec[1])){
			puts("F2: podnosi prawy widelec. JE");
			pthread_mutex_unlock(&widelec[1]);
			pthread_mutex_unlock(&widelec[2]);
			SLEEP(6000);
			break;
		}
	}
sem_post(&sem);//Opuszczamy semafor
}
}
void *filozof3() {
while(1){
sem_wait(&sem);//Podnosimy semafor
	if(!pthread_mutex_lock(&widelec[3])){
		puts("F3: podnosi lewy widelec");
		while(1)
		if(!pthread_mutex_lock(&widelec[2])){
			puts("F3: podnosi prawy widelec. JE");
			pthread_mutex_unlock(&widelec[2]);
			pthread_mutex_unlock(&widelec[3]);
			SLEEP(3000);
			break;
		}
	}
sem_post(&sem);//Opuszczamy semafor
}
}
void *filozof4() {
while(1){
sem_wait(&sem);//Podnosimy semafor
	if(!pthread_mutex_lock(&widelec[4])){
		puts("F4: podnosi lewy widelec");
		while(1)
		if(!pthread_mutex_lock(&widelec[3])){
			puts("F4: podnosi prawy widelec. JE");
			pthread_mutex_unlock(&widelec[3]);
			pthread_mutex_unlock(&widelec[4]);
			SLEEP(1500);
			break;
		}
	}
sem_post(&sem);//Opuszczamy semafor
}
}

int main(){
 
sem_init(&sem,0,4); //Inicjacja semaforu zliczajacego do 4

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

