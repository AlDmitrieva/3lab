#include <stdlib.h>

#include <stdio.h>
#include <string.h>




typedef struct person {
	char name[20];
	char surname[20];
	char sex[8];
	char position[20];
	unsigned int salary;
} person;

void set_data(char s[], int* k, char field[])
{

	int i = *k;
	while ((s[i] == ',') || (s[i] == '\"'))
	{
		i++;
	}
	int j = 0;
	while (s[i] != '\"')
	{
		field[j] = s[i];
		i++;
		j++;
	}
	field[j] = '\0';
	*k = i;
}




int main(int argc, char* argv[]) {
	FILE* fp;
	char s[255];

	int n = 0, i;
	person* data = NULL;
	person tmp;

	if (argc != 3) {
		printf("CSV scanner. Counts median salary on choosen position.\n Usage:\n csv.exe <filename> <position>\n");
		return 2;
	}

	if (NULL == (fp = fopen(argv[1], "r"))) {
		fprintf(stderr, "cannot open file '%s'", argv[1]);
		return 1;
	}
	if (!(fopen_s(&fp, argv[1], "r"))) {
		fgets(s, 255, fp);
		while (!feof(fp)) {
			fgets(s, 255, fp);
			data = (person*)realloc(data, (n + 1) * sizeof(person));
			i = 0;
			set_data(s, &i, data[n].name);
			set_data(s, &i, data[n].surname);
			set_data(s, &i, data[n].sex);
			set_data(s, &i, data[n].position);
			sscanf_s(&s[i + 3], "%d", &data[n].salary);
			n++;
		}
		fclose(fp);
	}



	unsigned int* sal = NULL;

	sal = (unsigned int*)realloc(sal, sizeof(unsigned int));
	int k = 0;
	if (sal != NULL) {
		for (int f = 0; f < n - 1; f++) {
			if (0 == strcmp(data[f].position, argv[2])) {
				sal[k] = data[f].salary;
				sal = (unsigned int*)realloc(sal, (k + 2) * sizeof(unsigned int));
				k++;
			}
		}
	}

	for (int i = 0; i < k; i++) {
		for (int j = k; j > i; j--) {
			if (sal[j - 1] > sal[j]) {
				unsigned int tmp = sal[j - 1];
				sal[j - 1] = sal[j];
				sal[j] = tmp;
			}
		}
	}
	if (k % 2 == 1) {
		printf("The median salary is: %d ", sal[k / 2]);
	}

	else {
		int med = (sal[k / 2] + sal[(k / 2) - 1]) / 2;
		printf("The median salary is: %d", med);
	}



}