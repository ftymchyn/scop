#include "scop.h"

int	main(void)
{
	t_scop	scop;

	create_context(&scop, 1280, 720);
	register_events(&scop);
	loop(&scop);
	destroy_context(&scop);
	return (0);
}