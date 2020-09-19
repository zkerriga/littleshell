/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 18:08:57 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/18 18:08:58 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_manager.h"
#include "libft.h"

static void	write_error_message(int error_code, const char *description)
{
	write(2, "minishell: ", 11);
	description = (description) ? description : strerror(error_code);
	write(2, description, ft_strlen(description));
	write(2, "\n", 1);
}

int		errman(int error_code, const char *description)
{
	int		status;

	status = error_code;
	write_error_message(error_code, description);
	if (error_code == ENOMEM)
		exit(error_code);
	return (status);
}
