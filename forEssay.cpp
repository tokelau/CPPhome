char str[13] = "Привет, мир!";

char str[] = "Привет, мир!";

str[5] = "И"; //так нельзя
str[5] = "Привет, человек!"; //так нельзя

int N = 17;
char* str = new char[N];
char arr[] = "Привет, мир!";

for (int i = 0; i < 16; i++)
  str[i] = arr[i];

str[9] = 'э';
