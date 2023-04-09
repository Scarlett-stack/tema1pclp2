#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include <string.h>
void get_operations(void **operations);
int get_index(char str[])
{
	int index = -1;
	char *q = strtok(str, " ");
	char *q2;
	while (q != NULL) {
		q2 = strtok(NULL, " ");
		// printf("hello : %s\n",q2);
		index = atoi(q2);
		q = strtok(NULL, " "); }
	return index;
}
int main(int argc, char const *argv[])
{ // FILE *g = fopen("almeu.txt","w");
	int nr0 = 0;
	int nr1 = 0;
	FILE *f = fopen(argv[1], "rb"); // este al doilea argument
	/-----------------CITIRE-------------------/
	int nr_senzori;
	fread(&nr_senzori, sizeof(int), 1, f); // citesc nr de senz
    int copie_nr_senzor = nr_senzori;
	// printf("nr_senzori  e : %d\n",nr_senzori);

	sensor *vector = malloc((nr_senzori) * sizeof(sensor));
	// atentie nu retin pointeri ci variabile simple de tip struct
	int j;
	for (j = 0; j < nr_senzori; j++) {

		int tip; // tip de sensor PMU =1 TIRE =0
		fread(&tip, sizeof(tip), 1, f);
		// printf("cine e tip : %d\n",tip);

		if (tip == 1) {
			nr1++;
			vector[j].sensor_type = PMU;
			vector[j].sensor_data = malloc(sizeof(power_management_unit));
			fread(vector[j].sensor_data, sizeof(power_management_unit), 1, f);
			 // nu pune & in fata !!! ca ai seg fault
		} else {
			nr0++;
			vector[j].sensor_type = TIRE;
			vector[j].sensor_data = malloc(sizeof(tire_sensor));
			fread(vector[j].sensor_data, sizeof(tire_sensor), 1, f);
		}
		fread(&vector[j].nr_operations, sizeof(vector[j].nr_operations), 1, f);

		// printf("cate operartii am: %d\n",vector[j].nr_operations);

		int i = vector[j].nr_operations;
		vector[j].operations_idxs = malloc(i*sizeof(int));

		for (i = 0; i < vector[j].nr_operations; i++) {
			fread(&vector[j].operations_idxs[i], sizeof(int), 1, f);
			// printf("ce operatie : %d ",vector[j].operations_idxs[i]);
		}
	}
	/------------	SFARSIT CITIRE-----------------/
	// Acum il rearanjam folosind un alt vector
	sensor *alt_v = malloc(nr_senzori * sizeof(sensor));
	int k = 0;
	for (j = 0; j < nr_senzori; j++) {
		if (vector[j].sensor_type == PMU)
			alt_v[k++] = vector[j];
	}
	for (j = 0; j < nr_senzori; j++) {
		if (vector[j].sensor_type == TIRE)
			alt_v[k++] = vector[j];
	}

	static void (*operations[8])(void *);
	// nebunie de vector de pointeri la functii
	get_operations((void **)operations);
	char command[20] = ""; // ca sa nu citesc inainte de while
	while (strcmp(command, "exit") != 0) {
		fgets(command, 20, stdin);				// am si endl
		command[strcspn(command, "\n")] = '\0'; // scap de el
		// printf("confirm comanda: %s \n", command);
		//  trebuie sa o identific
		// sterge sensori de pe aliexpress
		if (strcmp(command, "clear") == 0) {
			int t, poz;
			for (t = nr_senzori-1; t >= 0; t--) {
				// am doi senzori -> 2 cai
			if (alt_v[t].sensor_type == PMU) {
float s = ((power_management_unit *)(alt_v[t].sensor_data))->voltage;
			if (s < 10 || s > 20) {
						poz = t;
						for (poz = t; poz < nr_senzori - 1; poz++)
							alt_v[poz] = alt_v[poz + 1];
						nr_senzori = nr_senzori - 1;
					} else {
						// avem mai multe restrictii
float r = ((power_management_unit *)(alt_v[t].sensor_data))->current;
						if (r < -100 || r > 100) {
							poz = t;
							for (poz = t; poz < nr_senzori - 1; poz++)
								alt_v[poz] = alt_v[poz + 1];
							nr_senzori = nr_senzori - 1;
						} else {
float l = ((power_management_unit *)(alt_v[t].sensor_data))->power_consumption;
							if (l < 0 || l > 1000) {
								poz = t;
								for (poz = t; poz < nr_senzori - 1; poz++)
									alt_v[poz] = alt_v[poz + 1];
								nr_senzori = nr_senzori - 1;
							} else {
int m = ((power_management_unit *)(alt_v[t].sensor_data))->energy_regen;
								if (m < 0 || m > 100) {
									poz = t;
									for (poz = t; poz < nr_senzori - 1; poz++)
										alt_v[poz] = alt_v[poz + 1];
									nr_senzori = nr_senzori - 1;
								} else {
int e = ((power_management_unit *)(alt_v[t].sensor_data))->energy_storage;
							if (e < 0 || e > 100) {
							poz = t;
							for (poz = t; poz < nr_senzori - 1; poz++)
											alt_v[poz] = alt_v[poz + 1];
										nr_senzori = nr_senzori - 1;
									}
								}
							}
						}
					}
				}
				if (alt_v[t].sensor_type == TIRE) {
float o = ((tire_sensor *)(alt_v[t]).sensor_data)->pressure;
					if (o < 19 || o > 28) {
						for (poz = t; poz < nr_senzori - 1; poz++)
							alt_v[poz] = alt_v[poz + 1];
						nr_senzori = nr_senzori - 1;
					} else {
float w = ((tire_sensor *)(alt_v[t]).sensor_data)->temperature;
						if (w < 0 || w > 120) {
							for (poz = t; poz < nr_senzori - 1; poz++)
								alt_v[poz] = alt_v[poz + 1];
							nr_senzori = nr_senzori - 1;
						} else {
int b = ((tire_sensor *)(alt_v[t]).sensor_data)->wear_level;
							if (b < 0 || b > 100) {
								for (poz = t; poz < nr_senzori - 1; poz++)
									alt_v[poz] = alt_v[poz + 1];
								nr_senzori = nr_senzori - 1;
							}
						}
					}
				}
			}
			alt_v = realloc(alt_v, nr_senzori*sizeof(sensor));
		}
		if (strncmp(command, "analyze", strlen("analyze")) == 0) {
			int y = get_index(command);
			if (y < 0 || y >= nr_senzori)
			printf("Index not in range!\n");
			else {
			int z;
			for (z = 0; z < alt_v[y].nr_operations; z++)
			(*operations[alt_v[y].operations_idxs[z]])(alt_v[y].sensor_data);
			}
		}
		if (strncmp(command, "print", strlen("print")) == 0) {
			// revin ma duc sa citesc
			int x = get_index(command);
			// printf("aici e index : %d\n",x);
			if (x < 0 || x >= nr_senzori) {
				printf("Index not in range!\n");
			} else {
				if (alt_v[x].sensor_type == PMU) {
					printf("Power Management Unit\n");
float volt = ((power_management_unit *)(alt_v[x].sensor_data))->voltage;
float curr = ((power_management_unit *)(alt_v[x].sensor_data))->current;
float pc = ((power_management_unit *)(alt_v[x].sensor_data))->power_consumption;
int en = ((power_management_unit *)(alt_v[x].sensor_data))->energy_regen;
int en2 = ((power_management_unit *)(alt_v[x].sensor_data))->energy_storage;
					printf("Voltage: %.2f\n", volt);
					printf("Current: %.2f\n", curr);
					printf("Power Consumption: %.2f\n", pc);
					printf("Energy Regen: %d%%\n", en);
					printf("Energy Storage: %d%%\n", en2);
				}
				if (alt_v[x].sensor_type == TIRE) {
float pres = ((tire_sensor *)(alt_v[x]).sensor_data)->pressure;
float temp = ((tire_sensor *)(alt_v[x]).sensor_data)->temperature;
int lvl = ((tire_sensor *)(alt_v[x]).sensor_data)->wear_level;
					printf("Tire Sensor\n");
					printf("Pressure: %.2f\n", pres);
					printf("Temperature: %.2f\n", temp);
					printf("Wear Level: %d%%\n", lvl);
if (((tire_sensor *)(alt_v[x]).sensor_data)->performace_score == 0)
						printf("Performance Score: Not Calculated\n");
					else {
int cc = ((tire_sensor *)(alt_v[x]).sensor_data)->performace_score;
					printf("Performance Score: %d\n", cc);
					}
				}
			}
		}
	}
	int i;
	for (i = 0; i < copie_nr_senzor; i++) {
		free(vector[i].operations_idxs);
		free(vector[i].sensor_data);
	}
	free(vector);
	//for (i = 0; i<nr_senzori; i++)
	//free(alt_v[i].operations_idxs);
	free(alt_v);
	fclose(f);
	return 0;
}
