/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:02:03 by jidler            #+#    #+#             */
/*   Updated: 2025/05/11 13:25:49 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	parse_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

long	parse_digits(const char *str, int *i)
{
	long	result;

	result = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		result = result * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (result);
}

long	ft_strtol(const char *str, char **endptr)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	sign = parse_sign(str, &i);
	if (str[i] < '0' || str[i] > '9')
	{
		if (endptr)
			*endptr = (char *)str;
		return (0);
	}
	result = parse_digits(str, &i);
	if (endptr)
		*endptr = (char *)(str + i);
	return (result * sign);
}
