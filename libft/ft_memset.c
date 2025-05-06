/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidler <jidler@student.42tokyo.jp >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:16:41 by adrgutie          #+#    #+#             */
/*   Updated: 2025/05/06 11:33:59 by jidler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*b_ptr;

	b_ptr = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		b_ptr[i] = c;
		i++;
	}
	return (b);
}

// int	main(int argc, char *argv[])
// {
// 	if (argc > 3)
// 	{
// 		size_t	g = atoi(argv[3]);
// 		char *dst = argv[1];
// 		char *dst2 = malloc(ft_strlen(dst) + 1);
// 		strcpy(dst2, dst);
// 		const char src = argv[2][0];
// 		printf("return: %s\n", memset(dst, src, g));
// 		printf("return: %s\n", ft_memset(dst2, src, g));
// 	}
// }