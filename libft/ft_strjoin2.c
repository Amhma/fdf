/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:34:51 by amahla            #+#    #+#             */
/*   Updated: 2022/05/31 15:46:19 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	ft_slen(char const *str)
{
	int	i;

	i = 0;
	while (str && *(str + i))
		i++;
	return (i);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*dst;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	dst = malloc((ft_slen(s1) + ft_slen(s2) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	while (s1 && *(s1 + j))
		*(dst + i++) = *(s1 + j++);
	j = 0;
	while (s2 && *(s2 + j))
		*(dst + i++) = *(s2 + j++);
	*(dst + i) = '\0';
	if (s1)
		free(s1);
	return (dst);
}
