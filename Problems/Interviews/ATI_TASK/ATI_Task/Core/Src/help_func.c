/*
 * help_func.c
 *
 *  Created on: Feb 10, 2021
 *      Author: Hazem
 */
void str_empty(char str[]){
	int i=0;
	while(str[i] != '\0'){
		str[i] = '\0';
		i++;
	}
}

int len_str(char str[]){
	int len = 0;
	while(str[len++] !='\0');
	return len-1;
}

int find_str(char str1[],char str2[]){
	int match=0;

	int strlen = len_str(str1);
	int test=0;

	for(int i=0;((str2[i+strlen-1] != '\0') | (str2[i+strlen] != '\0')) & (match==0);i++){
		for(int j=0;j<=strlen;j++){
			if(str1[j] == str2[i+j]){
				test++;
				if(test== strlen){
					match=1;
				}
			}
		}
		test=0;
	}

	return match;
}

int find_strL(char str1[],char str2[]){
	int res=0;
	if((len_str(str1) == len_str(str2)) & find_str(str1, str2)){
		res = 1;
	}
	return res;
}

void concatenate(char str1[], char str2[]){
	int i=0;
	int j=0;
	while(str1[i++]!='\0');

	i--;
	while(str2[j]!='\0'){
		str1[i+j] = str2[j];
		j++;
	}
}

void int2char(int num, char str[]){
	char lstr[30];
	int cnt=0;
	int div=10;
	int j=0;

	while(num>=div){
		lstr[cnt] = num % div + 0x30;
		num/=10;
		cnt++;
	}
	lstr[cnt] = num+0x30;
	for(j=cnt;j >= 0;j--){
		str[cnt-j] = lstr[j];
	}
}

int char2int(char str[]){
	int res=0;
	int stop = 0;
	int strlen = len_str(str);
	int j=0;
	char check[2]={0};

	for(j=0;j<strlen;j++){
		check[0] = str[j];
		if(find_str(check,"0123456789") == 0){
			stop=1;
			break;
		}
	}
	if(stop==0){
		for(j=0;j<strlen;j++){
			res  = res*10 + (str[j] - 0x30);
		}
	}

	return res;
}
