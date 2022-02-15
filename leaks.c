#include <stdlib.h>

void after_main (void) __attribute__ ((destructor)); 
void	after_main(void)
{
	system("leaks a.out");
}
