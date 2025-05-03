#include "../include/cub3d.h"
#include <stdio.h>

int	main(int argc, char *argv[])
{
	(void)argc;
	int result = validate_map(argv[1]);
	printf("validate_map returned: %d\n", result);
	return result;
}
