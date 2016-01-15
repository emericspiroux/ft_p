/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: espiroux <espiroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/01 10:40:55 by jbalestr          #+#    #+#             */
/*   Updated: 2015/03/04 12:36:55 by espiroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		init_qsort(int l, int r, int *i, int *j)
{
	*i = l;
	*j = r;
	return ((*i + *j) / 2);
}

void			ft_quicksort(char **items, int left, int right)
{
	int		i;
	int		j;
	char	*x;
	char	*temp;

	x = items[init_qsort(left, right, &i, &j)];
	while (i <= j)
	{
		while (ft_strcmp(items[i], x) < 0 && i < right)
			i++;
		while (ft_strcmp(items[j], x) > 0 && j > left)
			j--;
		if (i <= j)
		{
			temp = ft_strdup(items[i]);
			ft_strcpy(items[i++], items[j]);
			ft_strcpy(items[j--], temp);
			free(temp);
		}
	}
	if (left < j)
		ft_quicksort(items, left, j);
	if (i < right)
		ft_quicksort(items, i, right);
}
