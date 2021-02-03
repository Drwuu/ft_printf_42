/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwourms <lwourms@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 14:54:25 by lwourms           #+#    #+#             */
/*   Updated: 2021/02/01 17:04:20 by lwourms          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_dot(t_datas *datas)
{
	int	dot;
	int	str_size;

	str_size = ft_strlen(datas->str);
	if (datas->d_conv && datas->dot <= str_size)
		(datas->str[0] == '0') ? (dot = 0) : (dot = str_size);
	else if (datas->d_conv)
		dot = datas->dot;
	else if (datas->dot >= str_size)
		dot = str_size;
	else
		dot = datas->dot;
	if (dot < 0)
	{
		datas->minus = 1;
		dot *= -1;
	}
	if (datas->str[0] == '-' && !(datas->d_conv && datas->dot <= str_size))
		dot += 1;
	return (dot);
}

static int	get_field(t_datas *datas, int dot)
{
	int	field;
	int	str_size;

	str_size = ft_strlen(datas->str);
	if (datas->c_conv)
		field = datas->field - 1;
	else if (datas->is_dot)
		field = datas->field - dot;
	else
		field = datas->field - str_size;
	return (field);
}

static void	print_str(int dot, int field, t_datas *datas, int *charNbr)
{
	int	str_size;

	str_size = ft_strlen(datas->str);
	(datas->zero && !datas->is_dot) ? print_zeros(field, datas, charNbr) : 0;
	if (datas->is_dot && !datas->c_conv)
		print_dot(dot, datas, charNbr);
	else
	{
		if (datas->c_conv && datas->str[0] == '\0')
		{
			ft_putchar_fd('\0', 1);
			*charNbr += 1;
		}
		else
		{
			if (datas->zero && datas->str[0] == '-')
				ft_putstr_at_fd(datas->str, 1, str_size, 1);
			else
				ft_putstr_fd(datas->str, 1);
			*charNbr += str_size;
		}
	}
}

void		print_process(t_list *lst, int *charNbr)
{
	t_datas	*datas;
	int		dot;
	int		field;

	while (lst)
	{
		datas = lst->content;
		dot = get_dot(datas);
		field = get_field(datas, dot);
		if (!datas->minus)
			print_field(field, datas, charNbr);
		print_str(dot, field, datas, charNbr);
		if (datas->minus)
			print_field(field, datas, charNbr);
		free(datas->str);
		lst = lst->next;
	}
}