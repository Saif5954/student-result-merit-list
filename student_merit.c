#include <stdio.h>
#include <string.h>

struct Student {
	char name[50];
	int roll;
	int m1, m2, m3;
	int total;
};

// Comparison function
int compare(struct Student a, struct Student b) {
	if (a.total != b.total)
		return b.total - a.total;   // Descending total

	if (a.m1 != b.m1)
		return b.m1 - a.m1;         // Subject priority
		
	if (a.m2 != b.m2)
        return b.m2 - a.m2;

    if (a.m3 != b.m3)
        return b.m3 - a.m3;

	if (a.roll != b.roll)
		return a.roll - b.roll;     // Smaller roll first

	return strcmp(a.name, b.name);  // Alphabetical
}

// Merge function
void merge(struct Student arr[], int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;

	struct Student L[n1], R[n2];

	for (int i = 0; i < n1; i++)
		L[i] = arr[left + i];

	for (int j = 0; j < n2; j++)
		R[j] = arr[mid + 1 + j];

	int i = 0, j = 0, k = left;

	while (i < n1 && j < n2) {
		if (compare(L[i], R[j]) <= 0) {
			arr[k] = L[i];
			i++;
		} else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		arr[k++] = L[i++];
	}

	while (j < n2) {
		arr[k++] = R[j++];
	}
}

// Merge Sort
void mergeSort(struct Student arr[], int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}
int main() {
	int n;
	printf("Enter number of students: ");
	scanf("%d", &n);

	struct Student s[n];

	// Input
	for (int i = 0; i < n; i++) {
		printf("\nStudent %d\n", i + 1);

		printf("Enter Name: ");
		scanf(" %[^\n]", s[i].name);

		printf("Enter Roll Number: ");
		scanf("%d", &s[i].roll);

		printf("Enter marks (3 subjects): ");
		scanf("%d %d %d", &s[i].m1, &s[i].m2, &s[i].m3);

		s[i].total = s[i].m1 + s[i].m2 + s[i].m3;
	}

	// Sorting
	mergeSort(s, 0, n - 1);

	// Output
	printf("\n--- Merit List ---\n");
	printf("Rank\tName\tRoll\tTotal\n");

	for (int i = 0; i < n; i++) {
		printf("%d\t%s\t%d\t%d\n", i + 1, s[i].name, s[i].roll, s[i].total);
	}

	return 0;
}
