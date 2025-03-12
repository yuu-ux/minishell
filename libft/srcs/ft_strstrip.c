/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 23:06:05 by yehara            #+#    #+#             */
/*   Updated: 2024/09/30 21:59:50 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstrip(const char *s1, int (*is_delim)(int))
{
	size_t		re_len;
	const char	*trim_front;
	const char	*trim_end;
	char		*buf;

	if (s1 == NULL || is_delim == NULL)
		return (NULL);
	trim_front = s1;
	while (*trim_front && is_delim(*trim_front))
		trim_front++;
	trim_end = s1 + ft_strlen(s1) - 1;
	while (trim_end > trim_front && is_delim(*trim_end))
		trim_end--;
	re_len = trim_end - trim_front + 1;
	buf = malloc((re_len + 1) * sizeof(char));
	if (buf == NULL)
		return (NULL);
	ft_strlcpy(buf, trim_front, re_len + 1);
	buf[re_len] = '\0';
	return (buf);
}
