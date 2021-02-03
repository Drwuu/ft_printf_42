/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_conv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwourms <lwourms@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 14:44:47 by lwourms           #+#    #+#             */
/*   Updated: 2021/02/01 17:08:20 by lwourms          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_list	**get_digits(char c, t_datas *datas, t_list **list, va_list ap)
{
	t_list	**lst;
	char	*nb;

	datas->d_conv = 1;
	if (c == 'u')
		if (!(nb = ft_itoa_ui(va_arg(ap, unsigned int))))
			return (NULL);
	if (c == 'x')
		if (!(nb = ft_itoa_base("0123456789abcdef", va_arg(ap, unsigned int))))
			return (NULL);
	if (c == 'X')
		if (!(nb = ft_itoa_base("0123456789ABCDEF", va_arg(ap, unsigned int))))
			return (NULL);
	if (c == 'd' || c == 'i')
		if (!(nb = ft_itoa(va_arg(ap, int))))
			return (NULL);
	if (!(lst = fill_list(datas, list, nb, ft_strdup)))
		return (NULL);
	free(nb);
	return (lst);
}

static t_list	*get_char(char c, t_datas *datas, char *s, t_list **list)
{
	t_list	*new_el;

	if (!s)
		return (NULL);
	if (c == '%')
	{
		free(s);
		if (!(datas->str = ft_char_to_str('%')))
			return (NULL);
	}
	else if (c == 'c')
		datas->str = s;
	if (!(new_el = ft_lstnew(datas)))
		return (NULL);
	ft_lstadd_back(list, new_el);
	datas->c_conv = 1;
	return (new_el);
}

int				get_conversions(char c, t_datas **datas, t_list **lst, \
va_list ap)
{
	if (c == 's')
		if (!(lst = fill_list(*datas, lst, va_arg(ap, char *), ft_strdup)))
			return (-1);
	if (c == 'p') // not usable
		if (!(lst = fill_list(*datas, lst, ft_itoa_base("0123456789abcdef", \
		va_arg(ap, unsigned int)), ft_strdup)))
			return (-1);
	if (c == 'd' || c == 'i' || \
	c == 'u' || c == 'x' || c == 'X')
		if (!(lst = get_digits(c, *datas, lst, ap)))
			return (-1);
	//dprintf(1, "conv proc s = %c\n", c);
	if (c == '%' || c == 'c')
		if (!(*lst = get_char(c, *datas, ft_char_to_str(va_arg(ap, int)), \
		lst)))
			return (-1);
	if (c == '\0')
		free (*datas);
	return (1);
}

t_list			*get_no_conv(char *s, t_list **list)
{
	t_list	*new_el;
	t_datas *datas;

	//dprintf(1, "no conv\n");
	if (!s)
		return (NULL);
	if (!(datas = init_datas()))
		return (NULL);
	if (!((datas)->str = s))
		return (NULL);
	if (!(new_el = ft_lstnew(datas)))
		return (NULL);
	ft_lstadd_back(list, new_el);
	return (new_el);
}