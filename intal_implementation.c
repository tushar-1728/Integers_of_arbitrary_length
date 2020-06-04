#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"

// Multiply INTAL1 by a single digit integer NUM
static char* simple_multiply(char *intal1, int num){
	size_t len = strlen(intal1);
	char *result = (char*)calloc(len + 1, sizeof(char));
	int result_index = len - 1;
	int sum = 0;
	int carry = 0;
	for (int i = len - 1; i >= 0; --i) {
		sum = (intal1[i] - 48) * num + carry;
		carry = sum / 10;
		result[result_index--] = (sum % 10) + 48;
 	}
 	if (carry) {
 		char *temp = (char*)calloc(len + 2, sizeof(char));
 		temp[0] = carry + 48;
 		strcat(temp, result);
 		free(result);
 		result = temp;
 		return result;
 	}
 	else {
	 	return result;
 	}
}

// Left-shift INTAL1 by given OFFSET, adds zeros at the end. 
static char* shift_left(char *intal1, int offset){
	size_t len = strlen(intal1);
	size_t result_len = len + offset;
	char *result = (char*)calloc(result_len + 1, sizeof(char));
	strcpy(result, intal1);
	while(offset--){
		strcat(result, "0");
	}
	return result;
}

// Swaps the value of intal A and B
static void swap(char **a, char **b){
	char *temp;
	temp = *a;
	*a = *b;
	*b = temp;
}


static int partition(char **arr, int l, int r){
	int i = l + 1;
	int j = r;
	int flag = 0;
	char *pivot = (char*)calloc(1001, sizeof(char));
	strcpy(pivot, arr[l]);
	while (i < j){
		while (intal_compare(arr[i], pivot) < 0) {
			++i;
		}
		while(intal_compare(arr[j], pivot) > 0){
			j--;
		}
		if (i < j) {
			flag = 1;
			swap(&arr[i++], &arr[j--]);
		}
	}
	if (flag) {
		swap(&arr[l], &arr[j]);
	}
	free(pivot);
	return j;
}


static void quicksort(char **arr, int l, int r){
	if (l < r) {
		int p = partition(arr, l, r);
		quicksort(arr, l, p - 1);
		quicksort(arr, p + 1, r);
	}
}


char* intal_add(const char* intal1, const char* intal2){
	size_t len1 = strlen(intal1);
	size_t len2 = strlen(intal2);
	size_t result_len = len1 > len2? len1 + 1 : len2 + 1;
	char *result = (char*)calloc(result_len, sizeof(char));
	int intal1_index = len1 - 1;
	int intal2_index = len2 - 1;
	int result_index = result_len - 1;
	result[result_index--] = '\0';
	int sum = 0;
	int carry = 0;
	while (intal1_index >= 0 && intal2_index >= 0) {
		sum = (intal1[intal1_index--] + intal2[intal2_index--] + carry) % 48;
		carry = 48 + sum / 10;
		result[result_index--] = 48 + sum % 10;
	}
	while (intal1_index >= 0) {
		sum = (intal1[intal1_index--] + carry) % 48;
		carry = 48 + sum / 10;
		result[result_index--] = 48 + sum % 10;
	}
	while (intal2_index >= 0) {
		sum = (intal2[intal2_index--] + carry) % 48;
		carry = 48 + sum / 10;
		result[result_index--] = 48 + sum % 10;
	}
	if (carry - 48) {
		char *temp = (char*)calloc(result_len + 1, sizeof(char));
		temp[0] = carry;
		strcat(temp, result);
		free(result);
		result = temp;
		return result;
	}
	else {
		return result;
	}
}


int intal_compare(const char* intal1, const char* intal2){
	if (strlen(intal1) > strlen(intal2)) {
		return 1;
	}
	else if (strlen(intal1) < strlen(intal2)) {
		return -1;
	}
	else {
		for (int i = 0; i < strlen(intal1); ++i) {
			if (intal1[i] > intal2[i]) {
				return 1;
			}
			else if (intal1[i] < intal2[i]) {
				return -1;
			}
		}
		return 0;
	}
}


char* intal_diff(const char* intal1, const char* intal2){
	int compare = intal_compare(intal1, intal2);
	if (compare == 0) {
		char *res = (char*)calloc(2, sizeof(char));
		res[0] = '0';
		return res;
	}
	else {
		size_t len1 = strlen(intal1);
		size_t len2 = strlen(intal2);
		char *temp1, *temp2;
		if (compare == 1){
			temp1 = (char*)malloc(sizeof(char) * (len1 + 1));
			temp2 = (char*)malloc(sizeof(char) * (len2 + 1));
			strcpy(temp1, intal1);
			strcpy(temp2, intal2);
		}
		else if (compare == -1) {
			temp1 = (char*)malloc(sizeof(char) * (len2 + 1));
			temp2 = (char*)malloc(sizeof(char) * (len1 + 1));
			strcpy(temp1, intal2);
			strcpy(temp2, intal1);
		}
		len1 = strlen(temp1);
		len2 = strlen(temp2);
		size_t result_len = len1 > len2 ? len1 + 1 : len2 + 1;
		char *result = (char*)malloc(sizeof(char) * result_len);
		int temp1_index = len1 - 1;
		int temp2_index = len2 - 1;
		int result_index = result_len - 1;
		result[result_index--] = '\0';
		int sum = 0;
		int carry = 0;
		while (temp1_index >= 0 && temp2_index >= 0) {
			sum = 48 + temp1[temp1_index--] - temp2[temp2_index--] - carry;
			if(sum < 48){
				sum += 10;
				carry = 1;
			}
			else {
				carry = 0;
			}
			result[result_index--] = sum;
		}
		while (temp1_index >= 0) {
			sum = temp1[temp1_index--] - carry;
			if (sum < 48) {
				sum += 10;
				carry = 1;
			}
			else {
				carry = 0;
			}
			result[result_index--] = sum;
		}
		free(temp1);
		free(temp2);
		if (result[0] == 48) {
			int i = 0;
			while (result[i] == 48) {
				++i;
			}
			result_len -= i;
			char *temp = (char*)calloc(result_len, sizeof(char));
			strcpy(temp, result + i);
			free(result);
			result = temp;
			return result;
		}
		else {
			return result;
		}
	}
}


char* intal_multiply(const char* intal1, const char* intal2){
	if (strcmp(intal1, "0") == 0 || strcmp(intal2, "0") == 0) {
		char *result = (char*)calloc(2, sizeof(char));
		result[0] = '0';
		return result;
	}
	size_t len1, len2;
	char *temp1, *temp2;
	int compare = intal_compare(intal1, intal2);
	if (compare == 1) {
		len1 = strlen(intal1);
		len2 = strlen(intal2);
		temp1 = (char*)malloc(sizeof(char) * (len1 + 1));
		temp2 = (char*)malloc(sizeof(char) * (len2 + 1));
		strcpy(temp1, intal1);
		strcpy(temp2, intal2);
	}
	else {
		len1 = strlen(intal2);
		len2 = strlen(intal1);
		temp1 = (char*)malloc(sizeof(char) * (len1 + 1));
		temp2 = (char*)malloc(sizeof(char) * (len2 + 1));
		strcpy(temp1, intal2);
		strcpy(temp2, intal1);
	}
	char *result = (char*)calloc(2, sizeof(char));
	result[0] = '0';
	char *partial_result;
	char *partial_sum;
	char *temp;
	for (int i = len2 - 1; i >= 0; --i) {
		partial_result = simple_multiply(temp1, temp2[i] - 48);
		partial_sum = shift_left(partial_result, len2 - 1 - i);
		free(partial_result);
		temp = intal_add(result, partial_sum);
		free(partial_sum);
		free(result);
		result = temp;
	}
	free(temp1);
	free(temp2);
	return result;
}


char* intal_mod(const char* intal1, const char* intal2){
	size_t len1 = strlen(intal1);
	size_t len2 = strlen(intal2);
	size_t length;
	int flag = 0;
	char *temporary;
	char *temp1 = (char*)calloc(len1 + 1, sizeof(char));
	strcpy(temp1, intal1);
	while (intal_compare(temp1, intal2) >= 0) {
		char *temp2 = (char*)calloc(len2 + 1, sizeof(char));
		strcpy(temp2, intal2);
		while (intal_compare(temp2, temp1) < 0) {
			temporary = simple_multiply(temp2, 2);
			free(temp2);
			temp2 = temporary;
		}
		temporary = intal_diff(temp2, temp1);
		free(temp1);
		free(temp2);
		temp1 = temporary;
		flag = (flag + 1) % 2;
	}
	length = strlen(temp1);
	if (temp1[length - 1] == 48) {
		return temp1;
	}
	if(flag == 1){
		temporary = intal_diff(intal2, temp1);
		free(temp1);
	}
	return temporary;
}


char* intal_pow(const char* intal1, unsigned int n){
	if (n == 0) {
		char *result = (char*)calloc(2, sizeof(char));
		result[0] = '1';
		return result;
	}
	else if (n == 1 || intal_compare(intal1, "1") <= 0) {
		char *result = (char*)calloc(strlen(intal1) + 1, sizeof(char));
		strcpy(result, intal1);
		return result;
	}
	else {
		char *result;
		char *temp;
		char **temp_arr = (char**)calloc(12, sizeof(char*));
		int *index_arr = (int*)calloc(12, sizeof(int));
		temp_arr[0] = (char*)calloc(strlen(intal1) + 1, sizeof(char));
		index_arr[0] = 1;
		strcpy(temp_arr[0], intal1);
		unsigned int i, j, diff, length;
		for (i = 2, j = 1; i <= n; i *= 2, j++) {
			temp_arr[j] = intal_multiply(temp_arr[j - 1], temp_arr[j - 1]);
			index_arr[j] = i;
		}
		i = i / 2;
		length = --j;
		result = (char*)calloc(strlen(temp_arr[j]) + 1, sizeof(char));
		strcpy(result, temp_arr[j]);
		if (i != n) {
			diff = n - i;
			while (diff != 0) {
				while (diff < index_arr[length]) {
					--length;
				}
				temp = intal_multiply(result, temp_arr[length]);
				free(result);
				result = temp;
				diff -= index_arr[length];
			}

		}
		for (i = 0; i <= j; ++i) {
			free(temp_arr[i]);
		}
		free(temp_arr);
		free(index_arr);
		return result;
	}
}


char* intal_gcd(const char* intal1, const char* intal2){
	int compare = intal_compare(intal1, intal2);
	if (compare == 0) {
		char* result = (char*)calloc(strlen(intal1) + 1, sizeof(char));
		strcpy(result, intal1);
		return result;
	}
	else {
		char *temp1;
		char *temp2;
		size_t len1 = strlen(intal1);
		size_t len2 = strlen(intal2);
		char *temporary;
		if (compare == 1) {
			temp1 = (char*)calloc(len1 + 1, sizeof(char));
			temp2 = (char*)calloc(len2 + 1, sizeof(char));
			strcpy(temp1, intal1);
			strcpy(temp2, intal2);
		}
		else {
			temp1 = (char*)calloc(len2 + 1, sizeof(char));
			temp2 = (char*)calloc(len1 + 1, sizeof(char));
			strcpy(temp1, intal2);
			strcpy(temp2, intal1);
		}
		while (intal_compare(temp1, "1") >= 0 && intal_compare(temp2, "1") >= 0) {
			temporary = intal_mod(temp1, temp2);
			free(temp1);
			temp1 = temp2;
			temp2 = temporary;
		}
		if (intal_compare(temp1, "1") == 0) {
			char *result = (char*)calloc(strlen(temp2) + 1, sizeof(char));
			strcpy(result, temp2);
			free(temp1);
			free(temp2);
			return result;
		}
		else{
			char *result = (char*)calloc(strlen(temp1) + 1, sizeof(char));
			strcpy(result, temp1);
			free(temp1);
			free(temp2);
			return result;
		}
	}
}


char* intal_fibonacci(unsigned int n){
	char *result = (char*)calloc(1001, sizeof(char));
	if (n == 0) {
		strcpy(result, "0");
		return result;
	}
	else if (n == 1) {
		strcpy(result, "1");
		return result;
	}
	else {
		unsigned int i;
		char *temp;
		char *prev_result = (char*)calloc(1001, sizeof(char));
		strcpy(prev_result, "0");
		strcpy(result, "1");
		for (i = 2; i < n; ++i) {
			temp = intal_add(result, prev_result);
			free(prev_result);
			prev_result = result;
			result = temp;
		}
		temp = intal_add(result, prev_result);
		free(prev_result);
		free(result);
		result = temp;
		return result;
	}
}


char* intal_factorial(unsigned int n){
	char *result = (char*)calloc(1001, sizeof(char));
	sprintf(result, "%u", n);
	char *prev_result = intal_diff(result, "1");
	char *temp;
	unsigned int i = 0;
	for (i = 0; i < n - 1; ++i){
		temp = intal_multiply(result, prev_result);
		// printf("print(%s * %s == %s)\n", result, prev_result, temp);
		free(result);
		result = temp;
		temp = intal_diff(prev_result, "1");
		free(prev_result);
		prev_result = temp;
	}
	free(prev_result);
	return result;
}


char* intal_bincoeff(unsigned int n, unsigned int k){
	char **temp_arr = (char**)calloc(k + 1, sizeof(char*));
	char *result = (char*)calloc(1001, sizeof(char));
	char *temporary;
	unsigned int i, j, min;
	for (i = 0; i < k + 1; ++i) {
		temp_arr[i] = (char*)calloc(1001, sizeof(char));
		temp_arr[i][0] = '0';
	}
	temp_arr[0][0] = '1';
	for (i = 1; i <= n; ++i) {
		if (i <= k) {
			min = i;
		}
		else {
			min = k;
		}
		for (j = min; j > 0; --j) {
			temporary = intal_add(temp_arr[j], temp_arr[j - 1]);
			strcpy(temp_arr[j], temporary);
			free(temporary);
		}
	}
	strcpy(result, temp_arr[k]);
	for (i = 0; i < k + 1; ++i) {
		free(temp_arr[i]);
	}
	free(temp_arr);
	return result;
}


int intal_max(char **arr, int n){
	int max_index = 0;
	char *max = (char*)calloc(1001, sizeof(char));
	strcpy(max, arr[0]);
	for (int i = 0; i < n; ++i) {
		if (intal_compare(max, arr[i]) == -1) {
			strcpy(max, arr[i]);
			max_index = i;
		}
	}
	free(max);
	return max_index;
}


int intal_min(char **arr, int n){
	int min_index = 0;
	char *min = (char*)calloc(1001, sizeof(char));
	strcpy(min, arr[0]);
	for (int i = 1; i < n; ++i) {
		if (intal_compare(min, arr[i]) == 1) {
			strcpy(min, arr[i]);
			min_index = i;
		}
	}
	free(min);
	return min_index;
}


int intal_search(char **arr, int n, const char* key){
	for (int i = 0; i < n; ++i) {
		if (strcmp(key, arr[i]) == 0) {
			return i;
		}
	}
	return - 1;
}


int intal_binsearch(char **arr, int n, const char* key){
	int low, high, mid;
	low = 0;
	high = n;
	while (low < high) {
		mid = low + (high - low) / 2;
		if (intal_compare(arr[mid], key) >= 0) {
			high = mid;
		}
		else if (intal_compare(arr[mid], key) == -1) {
			low = mid;
		}
	}
	if (intal_compare(arr[low], key) == 0) {
		return low;
	}
	return -1;
}
 


void intal_sort(char **arr, int n){
	quicksort(arr, 0, n-1);
}


char* coin_row_problem(char **arr, int n){
	char **table = (char**)calloc(n, sizeof(char*));
	char *result = (char*)calloc(1001, sizeof(char));
	char *temp;
	for (int i = 0; i < n; ++i) {
		table[i] = (char*)calloc(1001, sizeof(char));
		table[i][0] = '0';
	}
	char *sum = (char*)calloc(1001, sizeof(char));
	strcpy(table[0], arr[0]);
	if (intal_compare(arr[1], table[0]) >= 0) {
		strcpy(table[1], arr[1]);
	}
	else {
		strcpy(table[1], table[0]);
	}
	for (int i = 2; i < n; ++i){
		temp = intal_add(arr[i], table[i - 2]);
		strcpy(sum, temp);
		free(temp);
		if (intal_compare(table[i - 1], sum) >= 0) {
			strcpy(table[i], table[i - 1]);
		}
		else {
			strcpy(table[i], sum);
		}
	}
	free(sum);
	strcpy(result, table[n - 1]);
	for (int i = 0; i < n; ++i) {
		free(table[i]);
	}
	free(table);
	return result;
}