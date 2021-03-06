// Laba1_PP_C++.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

//use <> - find library from common directory, "" - find library from this project
//omp - inline library (need enable support option in propreties of project)
#include <omp.h>
#include <random>
#include <string>

//for srand
#include <ctime>

//function sleep
#include <Windows.h>

#include <iostream>

const int NN = 99;

//int a[NN][NN];
//int b[NN][NN];
//
////passed values
//bool sMarks[NN][NN];
//bool pMarks[NN][NN];
void main()
{
	setlocale(LC_ALL, "rus");
	int numTask;

	printf("-------------------------------------------------------------------------------\n");
	printf("|                 Enter the number of task (1-5, exit - 0):                   |\n");
	printf("-------------------------------------------------------------------------------\n");
	scanf("%i", &numTask);
	system("cls");

	while (numTask == 1 || numTask == 2 || numTask == 3 || numTask == 4 || numTask == 5)
	{
		if (numTask == 1)
		{
			//task1
			#pragma omp parallel num_threads(5)
			{
				printf("Hello World! from thread %i \n", omp_get_thread_num());
			}

			printf("\n");
			printf("-------------------------------------------------------------------------------\n");
			printf("|                 Enter the number of task (1-5, exit - 0):                   |\n");
			printf("-------------------------------------------------------------------------------\n");
			scanf("%i", &numTask);
			system("cls");
		}
		else if (numTask == 2)
		{
			//task2
			const int S = 10;
			double startTime;
			double endTime;
			double sum = 0;
			double result[4][3];

			//1.1
			printf("-------------------------------------------------------------------------------\n");
			printf("|                           Static(equal execution)                           |\n");
			printf("-------------------------------------------------------------------------------\n");

			#pragma omp parallel for schedule(static) private(startTime, endTime) reduction(+: sum)
			for (int i = 0; i < S; i++)
			{
				startTime = omp_get_wtime();
				Sleep(1);
				endTime = omp_get_wtime();
				sum += (endTime - startTime);
				printf("Thread %i iteration %i for %f miliseconds \n", omp_get_thread_num(), i, (endTime - startTime));
			}
			printf("Total miliseconds %f \n\n", result[0][0] = sum);

			//1.2
			printf("-------------------------------------------------------------------------------\n");
			printf("|                   Static(odd iterations execute longer)                     |\n");
			printf("-------------------------------------------------------------------------------\n");

			sum = 0;
			#pragma omp parallel for schedule(static) private(startTime, endTime) reduction(+: sum)
			for (int i = 0; i < S; i++)
			{
				if (i % 2 == 0)
				{
					startTime = omp_get_wtime();
					Sleep(1);
					endTime = omp_get_wtime();
					sum += (endTime - startTime);
					printf("Thread %i iteration %i for %f miliseconds \n", omp_get_thread_num(), i, (endTime - startTime));
				}
				else
				{
					startTime = omp_get_wtime();
					Sleep(2);
					endTime = omp_get_wtime();
					sum += (endTime - startTime);
					printf("Thread %i iteration %i for %f miliseconds \n", omp_get_thread_num(), i, (endTime - startTime));
				}
			}
			printf("Total miliseconds %f \n\n", result[0][1] = sum);

			//1.3
			printf("-------------------------------------------------------------------------------\n");
			printf("|               Static(first half of iterations execute longer)               |\n");
			printf("-------------------------------------------------------------------------------\n");

			sum = 0;
			#pragma omp parallel for schedule(static) private(startTime, endTime) reduction(+: sum)
			for (int i = 0; i < S; i++)
			{
				if (i <= S / 2)
				{
					startTime = omp_get_wtime();
					Sleep(2);
					endTime = omp_get_wtime();
					sum += (endTime - startTime);
					printf("Thread %i iteration %i for %f miliseconds \n", omp_get_thread_num(), i, (endTime - startTime));
				}
				else
				{
					startTime = omp_get_wtime();
					Sleep(1);
					endTime = omp_get_wtime();
					sum += (endTime - startTime);
					printf("Thread %i iteration %i for %f miliseconds \n", omp_get_thread_num(), i, (endTime - startTime));
				}
			}
			printf("Total miliseconds %f \n\n", result[0][2] = sum);

			//2.1
			printf("-------------------------------------------------------------------------------\n");
			printf("|                           Dynamic(equal execution)                          |\n");
			printf("-------------------------------------------------------------------------------\n");

			sum = 0;
			#pragma omp parallel for schedule(dynamic) private(startTime, endTime) reduction(+: sum)
			for (int i = 0; i < S; i++)
			{
				startTime = omp_get_wtime();
				Sleep(1);
				endTime = omp_get_wtime();
				sum += (endTime - startTime);
				printf("Thread %i iteration %i for %f miliseconds \n", omp_get_thread_num(), i, (endTime - startTime));
			}
			printf("Total miliseconds %f \n\n", result[1][0] = sum);

			//2.2
			printf("-------------------------------------------------------------------------------\n");
			printf("|                   Dynamic(odd iterations execute longer)                    |\n");
			printf("-------------------------------------------------------------------------------\n");

			sum = 0;
			#pragma omp parallel for schedule(dynamic) private(startTime, endTime) reduction(+: sum)
			for (int i = 0; i < S; i++)
			{
				if (i % 2 == 0)
				{
					startTime = omp_get_wtime();
					Sleep(1);
					endTime = omp_get_wtime();
					sum += (endTime - startTime);
					printf("Thread %i iteration %i for %f miliseconds \n", omp_get_thread_num(), i, (endTime - startTime));
				}
				else
				{
					startTime = omp_get_wtime();
					Sleep(2);
					endTime = omp_get_wtime();
					sum += (endTime - startTime);
					printf("Thread %i iteration %i for %f miliseconds \n", omp_get_thread_num(), i, (endTime - startTime));
				}
			}
			printf("Total miliseconds %f \n\n", result[1][1] = sum);

			//2.3
			printf("-------------------------------------------------------------------------------\n");
			printf("|               Dynamic(first half of iterations execute longer)              |\n");
			printf("-------------------------------------------------------------------------------\n");

			sum = 0;
			#pragma omp parallel for schedule(dynamic) private(startTime, endTime) reduction(+: sum)
			for (int i = 0; i < S; i++)
			{
				if (i <= S / 2)
				{
					startTime = omp_get_wtime();
					Sleep(2);
					endTime = omp_get_wtime();
					sum += (endTime - startTime);
					printf("Thread %i iteration %i for %f miliseconds \n", omp_get_thread_num(), i, (endTime - startTime));
				}
				else
				{
					startTime = omp_get_wtime();
					Sleep(1);
					endTime = omp_get_wtime();
					sum += (endTime - startTime);
					printf("Thread %i iteration %i for %f miliseconds \n", omp_get_thread_num(), i, (endTime - startTime));
				}
			}
			printf("Total miliseconds %f \n\n", result[1][2] = sum);

			//3.1
			printf("-------------------------------------------------------------------------------\n");
			printf("|                           Guided(equal execution)                           |\n");
			printf("-------------------------------------------------------------------------------\n");

			sum = 0;
			#pragma omp parallel for schedule(guided) private(startTime, endTime) reduction(+: sum)
			for (int i = 0; i < S; i++)
			{
				startTime = omp_get_wtime();
				Sleep(1);
				endTime = omp_get_wtime();
				sum += (endTime - startTime);
				printf("Thread %i iteration %i for %f miliseconds \n", omp_get_thread_num(), i, (endTime - startTime));
			}
			printf("Total miliseconds %f \n\n", result[2][0] = sum);

			//3.2
			printf("-------------------------------------------------------------------------------\n");
			printf("|                   Guided(odd iterations execute longer)                     |\n");
			printf("-------------------------------------------------------------------------------\n");

			sum = 0;
			#pragma omp parallel for schedule(guided) private(startTime, endTime) reduction(+: sum)
			for (int i = 0; i < S; i++)
			{
				if (i % 2 == 0)
				{
					startTime = omp_get_wtime();
					Sleep(1);
					endTime = omp_get_wtime();
					sum += (endTime - startTime);
					printf("Thread %i iteration %i for %f miliseconds \n", omp_get_thread_num(), i, (endTime - startTime));
				}
				else
				{
					startTime = omp_get_wtime();
					Sleep(2);
					endTime = omp_get_wtime();
					sum += (endTime - startTime);
					printf("Thread %i iteration %i for %f miliseconds \n", omp_get_thread_num(), i, (endTime - startTime));
				}
			}
			printf("Total miliseconds %f \n\n", result[2][1] = sum);

			//3.3
			printf("-------------------------------------------------------------------------------\n");
			printf("|                Guided(first half of iterations execute longer)              |\n");
			printf("-------------------------------------------------------------------------------\n");

			sum = 0;
			#pragma omp parallel for schedule(guided) private(startTime, endTime) reduction(+: sum)
			for (int i = 0; i < S; i++)
			{
				if (i <= S / 2)
				{
					startTime = omp_get_wtime();
					Sleep(2);
					endTime = omp_get_wtime();
					sum += (endTime - startTime);
					printf("Thread %i iteration %i for %f miliseconds \n", omp_get_thread_num(), i, (endTime - startTime));
				}
				else
				{
					startTime = omp_get_wtime();
					Sleep(1);
					endTime = omp_get_wtime();
					sum += (endTime - startTime);
					printf("Thread %i iteration %i for %f miliseconds \n", omp_get_thread_num(), i, (endTime - startTime));
				}
			}
			printf("Total miliseconds %f \n\n", result[2][2] = sum);

			//4.1
			printf("-------------------------------------------------------------------------------\n");
			printf("|                           Runtime(equal execution)                          |\n");
			printf("-------------------------------------------------------------------------------\n");

			sum = 0;
			#pragma omp parallel for schedule(runtime) private(startTime, endTime) reduction(+: sum)
			for (int i = 0; i < S; i++)
			{
				startTime = omp_get_wtime();
				Sleep(1);
				endTime = omp_get_wtime();
				sum += (endTime - startTime);
				printf("Thread %i iteration %i for %f miliseconds \n", omp_get_thread_num(), i, (endTime - startTime));
			}
			printf("Total miliseconds %f \n\n", result[3][0] = sum);

			//4.2
			printf("-------------------------------------------------------------------------------\n");
			printf("|                   Runtime(odd iterations execute longer)                    |\n");
			printf("-------------------------------------------------------------------------------\n");

			sum = 0;
			#pragma omp parallel for schedule(runtime) private(startTime, endTime) reduction(+: sum)
			for (int i = 0; i < S; i++)
			{
				if (i % 2 == 0)
				{
					startTime = omp_get_wtime();
					Sleep(1);
					endTime = omp_get_wtime();
					sum += (endTime - startTime);
					printf("Thread %i iteration %i for %f miliseconds \n", omp_get_thread_num(), i, (endTime - startTime));
				}
				else
				{
					startTime = omp_get_wtime();
					Sleep(2);
					endTime = omp_get_wtime();
					sum += (endTime - startTime);
					printf("Thread %i iteration %i for %f miliseconds \n", omp_get_thread_num(), i, (endTime - startTime));
				}
			}
			printf("Total miliseconds %f \n\n", result[3][1] = sum);

			//4.3
			printf("-------------------------------------------------------------------------------\n");
			printf("|               Runtime(first half of iterations execute longer)              |\n");
			printf("-------------------------------------------------------------------------------\n");

			sum = 0;
			#pragma omp parallel for schedule(runtime) private(startTime, endTime) reduction(+: sum)
			for (int i = 0; i < S; i++)
			{
				if (i <= S / 2)
				{
					//very important inizialize local variables!
					startTime = omp_get_wtime();
					Sleep(2);
					endTime = omp_get_wtime();
					sum += (endTime - startTime);
					printf("Thread %i iteration %i for %f miliseconds \n", omp_get_thread_num(), i, (endTime - startTime));
				}
				else
				{
					startTime = omp_get_wtime();
					Sleep(1);
					endTime = omp_get_wtime();
					sum += (endTime - startTime);
					printf("Thread %i iteration %i for %f miliseconds \n", omp_get_thread_num(), i, (endTime - startTime));
				}
			}
			printf("Total miliseconds %f \n\n", result[3][2] = sum);

			//table of results
			std::string name[] = { "Static ", "Dynamic", "Guided ", "Runtime" };
			printf("------------------------------------------------------------\n");
			for (int i = 0; i < 4; i++)
			{
				printf("|  %s  | \t", name[i].c_str());
				for (int j = 0; j < 3; j++)
				{
					printf("%f   |\t", result[i][j]);
				}
				printf("\n");
				printf("------------------------------------------------------------\n");
			}

			printf("\n");
			printf("-------------------------------------------------------------------------------\n");
			printf("|                 Enter the number of task (1-5, exit - 0):                   |\n");
			printf("-------------------------------------------------------------------------------\n");
			scanf("%i", &numTask);
			system("cls");
		}
		else if (numTask == 3)
		{
			//task3 (summary of elements of array with using critical section and reduction, compare time execute)
			const int N = 100000;
			double m[N];

			//fill array random values (also may use srand(time(0)))
			for (int i = 0; i < (sizeof(m) / sizeof(double)); i++)
				m[i] = rand() % 10 + 1;

			printf("-------------------------------------------------------------------------------\n");
			printf("|                                  Using reduction                            |\n");
			printf("-------------------------------------------------------------------------------\n");

			//shared variables
			double sum = 0;
			int i;
			double startTimeRed = omp_get_wtime();
			#pragma omp parallel for reduction(+:sum)
			for (i = 0; i < N; i++)
			{
				sum += m[i];
			}
			double endTimeRed = omp_get_wtime();
			printf("Sum %f for %lf miliseconds \n\n", sum, (endTimeRed - startTimeRed));

			//separator
			printf("-------------------------------------------------------------------------------\n");
			printf("|                            Using critical sections                          |\n");
			printf("-------------------------------------------------------------------------------\n");

			//shared variables
			sum = 0;
			double startTimeCrit = omp_get_wtime();
			#pragma omp parallel for
			for (int i = 0; i < N; i++)
			{
				#pragma omp critical
				{
					sum += m[i];
				}
			}
			double endTimeCrit = omp_get_wtime();
			printf("Sum %f for %lf miliseconds \n", sum, endTimeCrit - startTimeCrit);

			printf("\n");
			printf("-------------------------------------------------------------------------------\n");
			printf("|                 Enter the number of task (1-5, exit - 0):                   |\n");
			printf("-------------------------------------------------------------------------------\n");
			scanf("%i", &numTask);
			system("cls");
		}
		else if (numTask == 4)
		{
			//task4 (example of using barrier synchonisation)

			int a = 0;
			#pragma omp parallel num_threads(3)
			{
				#pragma omp atomic
				a++;

				//#pragma omp barrier
				#pragma omp single
				{
					std::cout << a << std::endl;
				}
			}

			printf("\n");
			printf("-------------------------------------------------------------------------------\n");
			printf("|                 Enter the number of task (1-5, exit - 0):                   |\n");
			printf("-------------------------------------------------------------------------------\n");
			scanf("%i", &numTask);
			system("cls");
		}
		else if (numTask == 5)
		{
			//task5 (parallel loop)
			int a[NN][NN];
			int b[NN][NN];

			//passed values
			bool sMarks[NN][NN];
			bool pMarks[NN][NN];

			
			//filling values of array and labels by default
			for (size_t i = 0; i < NN; i++)
			{
				for (size_t j = 0; j < NN; j++)
				{
					a[i][j] = 0;
					sMarks[i][j] = false;
				}
			}

			for (size_t i = 0; i < NN; i++)
			{
				for (size_t j = 0; j < 2; j++)
				{
					a[i][j] = i + j;
					sMarks[i][j] = true;
				}
			}

			for (size_t i = 0; i < 2; i++)
			{
				for (size_t j = 0; j < NN; j++)
				{
					a[i][j] = i + j;
					sMarks[i][j] = true;
				}
			}
							
			//copy values of array and their labels for parallel calculations
			for (size_t i = 0; i < NN; i++)
			{
				for (size_t j = 0; j < NN; j++)
				{
					b[i][j] = a[i][j];
					pMarks[i][j] = sMarks[i][j];
				}					
			}

			/*printf("-------------------------------------------------------------------------------\n");
			printf("|                                 Input matrix                                |\n");
			printf("-------------------------------------------------------------------------------\n");
			for (size_t i = 0; i < N; i++)
			{
				for (size_t j = 0; j < N; j++)
				{
					printf("%d \t", a[i][j]);
				}
				printf("\n");
			}	*/		
			
			//sequential
			double startTimeSeqLoop= omp_get_wtime();
			int si = 2;
			while (si <= NN - 1)
			//	si = NN - 2;
			{
				for (int i = 2; i < si + 2; i++)
				{
					for (int j = 2; j < si + 2; j++)
					{
						//check on repeat
						if (sMarks[i][j] == false)
						{
							a[i][j] = a[i - 2][j] + a[i][j - 2];
							sMarks[i][j] = true;
						}
					}
				}
				si += 2;
			}
			//Sleep(1);
			double endTimeSeqLoop = omp_get_wtime();
			printf("Sequential for %lf miliseconds \n", endTimeSeqLoop - startTimeSeqLoop);

			//sequential output
			printf("-------------------------------------------------------------------------------\n");
			printf("|                        Output matrix (sequential)                           |\n");
			printf("-------------------------------------------------------------------------------\n");
			for (size_t i = NN - 5; i < NN; i++)
			{
				for (size_t j = NN - 5; j < NN; j++)
				{
					printf("%d \t", a[i][j]);
				}
				printf("\n\n");
			}

			//parallel
			double startTimeParLoop = omp_get_wtime();
			int c;
			int pi = 2;
			while (pi <= NN + (NN-4))
			{   //int maxi=min(NN,pi+2);
				#pragma omp parallel for schedule(static, 1) private(c)
				for (int i = 2; i < pi + 2; i++)
				{
					c = 0; 
					for (int j = 2; j < pi + 2; j++)
					{
						if (i < NN && j < NN)
						{
							//check on repeat
							if (pMarks[i][j] == false)
							{
								if (c < 2)
								{
									c++;
									b[i][j] = b[i - 2][j] + b[i][j - 2];
									pMarks[i][j] = true;
								}
							}							
						}
						else
						{
							c = 2;
						}
					}
				}
				pi +=2;
			}
			//Sleep(1);
			double endTimeParLoop = omp_get_wtime();
			printf("Parallel for %lf miliseconds \n", endTimeParLoop - startTimeParLoop);

			//parallel output
			printf("-------------------------------------------------------------------------------\n");
			printf("|                           Output matrix(parallel)                           |\n");
			printf("-------------------------------------------------------------------------------\n");
			for (size_t i = NN - 5; i < NN; i++)
			{
				for (size_t j = NN - 5; j < NN; j++)
				{
					printf("%d \t", b[i][j]);
				}
				printf("\n\n");
			}			

			printf("\n");
			printf("-------------------------------------------------------------------------------\n");
			printf("|                 Enter the number of task (1-5, exit - 0):                   |\n");
			printf("-------------------------------------------------------------------------------\n");
			scanf("%i", &numTask);
			system("cls");
		}
	}
}





//int a = 0;
//#pragma omp parallel num_threads(3)
//{
//	#pragma omp atomic
//	a++;
//	//#pragma omp barrier
//	#pragma omp single
//	{
//		std::cout << a << std::endl;
//	}
//}

/*int TID;
time_t t1, t2;

#pragma omp parallel private(TID,t1)
{
TID = omp_get_thread_num();
if (TID < omp_get_num_threads() / 2)
Sleep(5000);

t1 = time(NULL);
printf("Thread %d before barrier at %s \n", omp_get_thread_num(), ctime(&t1));

#pragma omp barrier

t2 = time(NULL);
printf("Thread %d after barrier at %s \n", omp_get_thread_num(), ctime(&t2));
}*/