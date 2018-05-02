/*kompilacja: gcc -o prog prog.c -lm -lpthread */
#define _REENTRANT    
#include <pthread.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	
#define NUM_THREADS 3

	
	//licznik do petli
	int i;
	//wczytany argument x
	float x;
	//tablica id watkow
	pthread_t tid[NUM_THREADS];   
	//funkcja usypiajaca watki   
	void sleeping(pthread_t);
	
	//funkcje ktore sa przydzielone watkom
	void *cos_x(void *); 
	void *log_x(void *); 
	void *pow_x(void *); 
	
	//wyniki poszczegolnych operacji
	float x_cos;
	float x_log;
	float x_pow;

	//tablica wynikow i suma
	float wyniki[NUM_THREADS];
	float suma;


	int main(int argc, char *argv[])
	{
		
		//jesli liczba argumentow jest mniejsza od 2
		if(argc!=2)
		{
		printf("Wczytano niepoprawna ilosc argumentow\n");
		return 1;
		}
		
		//sprawdzanie czy x jest liczba dodatnia
		x=atof(argv[1]);
		if(x<=0)
		{
			printf("Wczytano wartosc mniejsza od zera\n");
			return 1;
		}
		
		//tworzenie watkow
		pthread_create(&tid[0], NULL, cos_x, (void *) &x);
		pthread_create(&tid[1], NULL, log_x, (void *) &x);
		pthread_create(&tid[2], NULL, pow_x, (void *) &x);
		
		for(i=0; i<NUM_THREADS; i++)
			pthread_join(tid[i], NULL);
		
		//wyliczanie sumy i drukowanie na ekran
		suma=0;
		for(i=0; i<NUM_THREADS; i++)
		{
			suma=suma+wyniki[i];
		}
		
		printf("Suma cos(x)+log(x)+x^3: %f\n", suma);
		

	}  
	
	//cos(x)
	void *cos_x(void *arg)
	{
	x_cos = *(float*)arg;
	x_cos = cos(x_cos);

	sleeping(pthread_self());

	printf("cos(x):      %f\n", x_cos);
	wyniki[0] = x_cos;

	return (NULL);
	}

	//log10(x)
	void *log_x(void *arg)
	{
	x_log = *(float*)arg;
	x_log = log10(x_log);

	sleeping(pthread_self());
	printf("log(x):      %f\n", x_log);

	wyniki[1] = x_log;
	
	return (NULL);
	}
	
	//x^3
	void *pow_x(void *arg)
	{
	x_pow = *(float*)arg;
	x_pow = pow(x_pow, 3.0);

	sleeping(pthread_self());

	printf("x^3:         %f\n", x_pow);
	wyniki[2] = x_pow;

	return (NULL);
	}

	//sleeping - watek spi liczbe sekund taka jak identyfikator watku
	void sleeping(pthread_t t_time)
	{
	printf("Watek id: %d spi %ds...\n", t_time, t_time);
	sleep(t_time);
	printf("Watek id: %d wybudzony\n", t_time);
	 
	}

