#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"


//Name:Youssef Ahmed AbdelHafez	ID: 20180337

int main(int argc , char * argv[])
{
   int my_rank;		/* rank of process	*/
	int p;			/* number of process	*/

	MPI_Status status;	/* return status for 	*/
				/* recieve		*/

	/* Start up MPI */
	MPI_Init( &argc , &argv );

	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* Find out number of process */
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	if( my_rank == 0)
	{
        int globalSum = 0;
        int i = 0;
        int LB = 0;
        int UB = 0;

		printf("Lower Bound: ");
		scanf("%d", &LB);
		printf("Upper Bound: ");
		scanf("%d", &UB);
    
		int range=0;

		if((UB - LB) % (p - 1) != 0)
           range=(UB - LB) / (p - 1)+(UB - LB) % (p - 1);
        else
            range=(UB - LB) / (p - 1);

        for (i = 1 ; i < p ; i++){
			
          MPI_Send ( &range, 1 ,MPI_INT, i , 0 , MPI_COMM_WORLD );
          MPI_Send ( &LB, 1 ,MPI_INT, i , 0 , MPI_COMM_WORLD );
        }
        for (i = 1 ; i < p ; i++){
          int subSum;
          MPI_Recv(&subSum , 1 ,MPI_INT,i,0,MPI_COMM_WORLD, &status);
          globalSum += subSum;
          printf("Total number of prime numbers in P%d %d\n",i,subSum );
        }
        printf("Total number of prime numbers = %d\n",globalSum );
	}else
	{
    int range=0;
    MPI_Recv(&range , 1 , MPI_INT , 0 , 0 , MPI_COMM_WORLD, &status);
    
    int LB = 0;
    MPI_Recv(&LB , 1 , MPI_INT , 0 , 0 , MPI_COMM_WORLD , &status);
    
    int pUB = LB + range*my_rank;
    int localSum = 0;

    int j=0;
	int pLB = LB + range*(my_rank-1);
	

	int q =0;
	for (q=pLB ; q<pUB ; q++){
			for (j = 2; j < q; j++) {
			    
				if (q % j == 0) {
					break;
				}
			}
			if (j == q) {
				localSum++;	
			}
			
	}

    MPI_Send (&localSum , 1 , MPI_INT , 0 , 0 , MPI_COMM_WORLD);
	}

	/* shutdown MPI */
	MPI_Finalize();
    return 0;
}