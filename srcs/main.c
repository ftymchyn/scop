#include "scop.h"

int	main(void)
{
	t_scop	scop;

	create_context(&scop, 1000, 1000);
	loop(&scop);
	destroy_context(&scop);
	return (0);
}