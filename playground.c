#include <libc.h>

typedef struct s {
	char c2;
	int i;
	char c;
} t_s;

int main(int argc, char const *argv[])
{
	// t_s k;
	printf("%lu", sizeof(t_s));
	return 0;
}
