/*
 * Source.c
 *
 *  Created on: Sep 21, 2019
 *      Author: Artem
 */

/*#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
typedef long long int ll;
const ll n = 200;

int    DelSymbols  (char*  from, char* sym);
ll     CountLines  (char*  st);
char** CreateArray (char*  st, ll NumOfStr);
int    IsLine      (char*  line);
int    Compare     (char*  s1, char* s2);
int    quiksort    (char** s, ll* id, ll first, ll last);
int    Parse       (char** s, ll* id, ll length);
int PrintRaveToFile(char** s, ll* id, FILE* wf, ll NumOfLines);*/

/*int main(){
	ll CouLine = 0;
	//char file_name[200];
	//scanf()
	CouLine  = CountLines ("EvgeniyOnegin.txt"); // scanf file name || input args
	char **s = CreateArray("EvgeniyOnegin.txt", CouLine);
	ll *id = (ll*)malloc(CouLine * sizeof(ll));
	assert(s  != NULL);
	assert(id != NULL);
	for(int i = 0; i < CouLine; i++){ //Fill support array
		id[i] = i;
	}

	//Sort test and print it
	FILE* wf = fopen("Output.txt", "w");
	quiksort(s, id, 0, CouLine - 1); // WARNING: change id-s
	for(ll i = 0; i < CouLine; i++){
		if(i % 14 == 0 && i != 0) fprintf(wf, "\n"); //const variable
		fprintf(wf, "%s", s[id[i]]);
	}
	fprintf(wf, "-----------------------------\n");
	fprintf(wf, "\n");

	//Generate and print rave text
	PrintRaveToFile(s, id, wf, CouLine); // WARNING: change id-s

	//Print to file original text
	for(ll i = 0; i < CouLine; i++){
		if(i % 14 == 0) fprintf(wf, "\n");
		fprintf(wf, "%s", s[i]);
	}
	fclose(wf);

	//Clear space
	free(id);
	for(int i = 0; i < CouLine; i++){
		free(s[i]);
	}
	free(s);
	return 0;
}

ll CountLines(char* s){
	FILE *f = fopen(s, "r"); //check nullptr
	assert(f != NULL);
	char buff[n];
	//char buff[n] ={}; //in cpp works
	assert(buff != NULL); //необязательно
	ll CouLine = 0;

	while(fgets(buff, n, f) != NULL){
		if(! IsLine(buff)) continue;
		CouLine++;
	}
	fclose(f);
	return CouLine;
}

char** CreateArray(char* st, ll NumOfStr){ //check input params (nullptr)
	char **s = (char**)calloc(NumOfStr, sizeof(char*));//sizeof(char *)
	assert(s != NULL);
	char buff[n];
	int length = 0;
	FILE* rf = fopen(st, "r");
	assert(rf != NULL);
	int id = 0;

	while(fgets(buff, n, rf) != NULL){
		length = strlen(buff);
		while(buff[0] == ' '){
			for(int j = 0; j < length; j++){
				buff[j] = buff[j + 1];
			}
			buff[length - 1] = '\0';
			length--;
		}

		if(! IsLine(buff)) continue;
		if(id >= NumOfStr){
			for(ll i = 0; i < NumOfStr; i++) free(s[i]);
			free(s);
			return 0;
		}
		s[id] = (char*)calloc(length + 1, sizeof(char));
		assert(s[id] != NULL);

		strcpy(s[id], buff);
		s[id][length] = '\0';
		id++;
	}
	fclose(rf);
	return s;
	//strchr - парсинг по char
}

int DelSymbols(char* from, char* sym){
	assert(from != NULL);
	assert(sym  != NULL);

	int i = 0,
		j = 0,
		l = 0;
	int flag = 1;
	for(;i < strlen(from); i++){
		flag = 1;
		for(j = 0; j < strlen(sym); j++){
			if(from[i] == sym[j]) flag = 0; //break
		}

		if(flag){
			from[l] = from[i];
			l++;
		}
	}
	from[l]     = '\n';
	from[l + 1] = '\0';
	return 0;
}

//Don`t accept names of chapters (like XIV) and empty lines
int IsLine(char* line){
	char* a = calloc(n, sizeof(char));
	assert(a);
	strcpy(a, line);
	a[strlen(line)] = '\0';
	if(strcmp(a, "\n") == 0){
		free(a);
		return 0;
	}

	DelSymbols(a, " ,-\"()`\'");

	if (a[0] == '\n'){
		free(a);
		return 0;
	}
	int flag = 0;
	int j    = 0;
	while((a[j] == 'X')
	||    (a[j] == 'L')
	||    (a[j] == 'I')
	||    (a[j] == 'V')){
		j++;
		flag = 1;
	}
	if(flag && a[j] == '\n')
	{
		free(a);
		return 0;
	}
	free(a);
	return 1;
}

int Compare(char* s1, char* s2){ //Compare two strings
	assert(s1 != NULL);
	assert(s2 != NULL);
	if(s1 == s2) return 0;
	int len = 0;

	if(strlen(s1) <= strlen(s2)) len = strlen(s1); //save lens first time and then use
	else len = strlen(s2);
	int i = 0;
	while(s1[i] == s2[i]) {
		i++;
		if(i == len) break;
	}

	if(strlen(s1) == i && strlen(s2) == i) return 0;
	if(strlen(s1) == i) return -1;
	if(strlen(s2) == i) return 1;
	if(s1[i] == ' ' || s1[i] == '\n')  return -1;
	if(s2[i] == ' ' || s2[i] == '\n')  return 1;
	if(s1[i] > s2[i]) return 1;
	if(s1[i] < s2[i]) return -1;
	return 1;
}

int quiksort(char** s, ll* id, ll first, ll last){ //check input args
	if(first >= last) return 1;
	ll  p1  = first;
	ll  p2  = last;
	ll  mid = (first + last) / 2;
	char* middle = s[id[mid]];
	assert(middle != NULL);
	int bool = 0;

	while(p1 <= p2){
		while((bool = Compare(middle, s[id[p1]])) == 1) p1++;
		while((bool = Compare(s[id[p2]], middle)) == 1) p2--;
		if(p1 > p2) break;
		ll sup = id[p1];
		id[p1] = id[p2];
		id[p2] = sup;
		p1++;
		p2--;
	}

	quiksort(s, id, first, p2);
	quiksort(s, id, p1, last);
	return 0;
}

int Parse(char** s, ll* id, ll length){ // Parse the Onegin`s rhyme
	int j = 0;
	ll i1 = 0;
	for(ll i = 0; i < length; i++){
		if(j == 2 || j == 3  || j == 5  || j == 6
		|| j == 7 || j == 10 || j == 11 || j == 13){
			j++;
			continue;
		}
		if(j == 14) j = 0;

		if(j == 0){
			id[i1] = i;
			i1++;
			id[i1] = i + 2;
			i1++;
		}
		if(j == 1){
			id[i1] = i;
			i1++;
			id[i1] = i + 2;
			i1++;
		}
		if(j == 4){
			for(int k = 0; k < 4; k++){
				id[k + i1] = i + k;
			}
			i1 += 4;
		}
		if(j == 8){
			id[i1] = i;
			i1++;
			id[i1] = i + 3;
			i1++;
		}
		if(j == 9){
			id[i1] = i;
			i1++;
			id[i1] = i + 1;
			i1++;
		}
		if(j == 12){
			id[i1] = i;
			i1++;
			id[i1] = i + 1;
			i1++;
		}
		j++;
	}
	return 1;
}

int PrintRaveToFile(char** s, ll* id, FILE* wf, ll NumOfLines){
	assert(s  != NULL);
	assert(id != NULL);
	assert(wf != NULL);
	Parse(s, id, NumOfLines);

	//Generate Rave
	for(ll i = 0; i < NumOfLines / 2; i++){
		ll nl = rand() % NumOfLines;
		while(id[nl] == -1) nl = rand() % NumOfLines;
		if(nl % 2 == 1) nl--;
		if(i  % 6 == 0 && i != 0) fprintf(wf, "\n");
		fprintf(wf, "%s", s[id[nl]]);
		fprintf(wf, "%s", s[id[nl + 1]]);
		id[nl] = -1;
		id[nl + 1] = -1;
	}
	fprintf(wf, "-----------------------------\n");
	return 0;
}*/

/*int quiksort(char** s, ll* id, ll number){
	supel(s, id, 0, number - 1, number);
	return 1;
}*/

/*int supel(char** s, ll* id, ll first, ll last, ll number){
	if(first >= last) return 1;
	ll* id2 = (ll*) calloc(number, sizeof(ll));
	ll  mid = (first + last) / 2;
	ll  p1  = first;
	ll  p2  = last;
	int bool = 0;
for(int i = first; i < last + 1; i++){
		if(i == mid) continue;
		bool = Compare(s[id[i]], s[id[mid]]);
		if(bool == 1){
			id2[p2] = id[i];
			p2--;
		}
		else{
			id2[p1] = id[i];
			p1++;
		}
	}
	id2[p1] = id[mid];
for(int i = first; i < last + 1; i++){
		id[i] = id2[i];
	}
	free(id2);
	supel(s, id, first, p2, number);
	supel(s, id, p1, last, number);
	return 1;
}*/
