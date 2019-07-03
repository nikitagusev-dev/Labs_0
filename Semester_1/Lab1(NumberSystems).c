#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void beforePoint(char s[100], int a, int b) 
{
	unsigned long long sum = 0;
	unsigned long long sys = 1;
	int d = 0, f = 0;
	char str[100];
	    
	for (int i=strlen(s)-1; i>=0; i--)
	{
		if ((s[i] - 48 >= 0) && (s[i] - 48 <= 9)) 
		{
			sum = sum + (s[i] - 48)*sys;
			sys *= a;
		}
		else if ((s[i] - 55 >= 10) && (s[i] - 55 <= 15))
		{
			sum = sum + (s[i] - 55)*sys;
			sys *= a;
		}
	}

	do
	{
		if (sum%b <= 9)
		{
			str[d] = (char)((sum % b)+48);
			sum /= b;
			d += 1;
		}
		else if ((sum%b >= 10) && (sum%b <= 15)) 
		{
			str[d] = (char)((sum % b) + 55);
			sum /= b;
			d += 1;
		}

		f = f + 1;
	} while (sum > 0);

	for (int j = f - 1; j >= 0; j--)
	{
		printf("%c", str[j]);
	}
	
}

void afterPoint(char w[100], int a, int b)
{
	double num = 0, sys = (double)1 / a;
	char str[100] = { '\0' };
	int k;

	for (size_t i = 0; i <= strlen(w); i++)
	{
		if ((w[i] - 48 >= 0) && (w[i] - 48 <= 9))
		{
			num = num + (w[i] - 48)*sys;
			sys = sys * (double)1 / a;
		}
		else if ((w[i] - 55 >= 10) && (w[i] - 55 <= 15))
		{
			num = num + ((w[i] - 55))*sys;
			sys = sys * (double)1 / a;
		}
	}

	k = 0;

	do
	{
		num = num * b;
		if (num >= 10)
		{
			str[k] = (int)trunc(num) + 55;
		}
		else
		{
			str[k] = (int)trunc(num) + 48;
		}
		if (num >= 1)
		{
			num = num - (int)trunc(num);
		}
		k = k + 1;
	} 	while (((num - trunc(num)) != 0.0) && (strlen(str) <= 12));

	for (int i = 0; i < k; i++)
	{
		printf("%c", str[i]);
	}
}

int main()
{
	int b1, b2, divide = 0, tch = 0, check = 0;
	char str[100];
	char arBef[100] = { '\0' };
	char arAft[100] = { '\0' };
	
	scanf("%d %d", &b1, &b2);
	scanf("%s", str);
	
	for (size_t i = 0; i < strlen(str); i++)
	{
		if (str[i] >= 'a')
		{
			str[i] = str[i] - 'a' + 'A';
		}
	}

	if (((b1 < 2) || (b1 > 16)) || ((b2 < 2) || (b2 > 16)))
	{
		printf("bad input");
	}
	else
	{
		for (size_t j = 0; j < strlen(str); j++)
		{
			if (str[j] == '.')
			{
				tch = tch + 1;
			}
			else if (((str[j] - 48 >= 0) && (str[j] - 48 < b1)) || ((str[j] - 55 >= 0) && (str[j] - 55 < b1)))
			{
				check = check + 1;
			}
		}
		if (tch > 0)
		{
			for (size_t j = 0; j < strlen(str); j++)
			{
				if (str[j] == '.')
				{
					divide = divide + j;
				}
			}
		}

		if ((divide > 0) && (tch == 1) && (check == strlen(str) - 1) && (str[0] != '.') && (str[strlen(str) - 1] != '.'))
		{
			for (int i = 0; i < divide; i++)
			{
				arBef[i] = str[i];
			}
			for (size_t s = divide + 1; s < strlen(str); s++) 
			{
				arAft[s - divide - 1] = str[s];
			}
			beforePoint(arBef, b1, b2);
			printf(".");
			afterPoint(arAft, b1, b2);			
		}
		else if ((divide == 0) && (tch == 0) && (check == strlen(str)))
		{
			beforePoint(str, b1, b2);
		}
		else 
		{
			printf("bad input");
		}
	}
	
	return 0;
}
