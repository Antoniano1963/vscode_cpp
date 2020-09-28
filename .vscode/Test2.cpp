#include <cstdio>
#include <string>

int main()
{
	char* format1 = "%s %d\n";
	printf(format1, "hello", 10, 1);
	printf_s(format1, "hello", 10, 1);

	char* format2 = "%s %d %d %d %s\n";
	printf(format2, "hello", 10, 1);
	printf_s(format2, "hello", 10, 1);

	return 0;
} 