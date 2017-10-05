#include <stdio.h>
#include <stdlib.h>

#include "KMeans.h"

int main(){
	int dimension_data	= 2;
	int number_cluster	= 4;
	int number_data		= 100;

	double **data = new double*[number_data];

	FILE *file;

	KMeans kmeans = KMeans(dimension_data, number_cluster);

	for(int i = 0;i < number_data;i++){
		double position[] = {0.25, 0.75};

		data[i]		= new double[dimension_data];
		data[i][0]	= 0.25 * rand() / RAND_MAX - 0.125 + position[(i % 2)];
		data[i][1]	= 0.25 * rand() / RAND_MAX - 0.125 + position[(i % 4) / 2];
	}

	for(int i = 0;;i++){
		double movements_centroids;
		
		if(i == 0) kmeans.Initialize(number_data, data);

		movements_centroids = kmeans.Cluster(number_data, data);

		printf("step %d	%lf\n", i + 1, movements_centroids);
		if(movements_centroids == 0) break;
	}

	printf("\ncentroids\n");
	for(int i = 0;i < number_cluster;i++){
		printf("%d: ", i);

		for(int j = 0;j < dimension_data;j++){
			printf("%lf ", kmeans.centroid[i][j]);
		}
		printf("\n");
	}

	file = fopen("result.txt", "wt");

	for(int j = 0;j < number_cluster;j++){
		for(int i = 0;i < number_data;i++){
			if(kmeans.Classify(data[i]) == j){
				fprintf(file, "%d %lf %lf\n", kmeans.Classify(data[i]), data[i][0], data[i][1]);
			}
		}
	}
	fclose(file);

	for(int i = 0;i < number_data;i++){
		delete[] data[i];
	}
	delete[] data;

	return 0;
}
