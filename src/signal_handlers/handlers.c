/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 17:46:32 by matrus            #+#    #+#             */
/*   Updated: 2020/09/18 17:46:33 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

//void	sigchild_handler()
//{
//	int		sigterm;
//
//	printf("g_stat: %d\n", g_last_exec_status);
//	if (WIFSIGNALED(g_last_exec_status))
//	{
//		sigterm = WTERMSIG(g_last_exec_status);
//		ft_putstr_fd("\nQuit:\t", 2);
//		ft_putnbr_fd(sigterm, 2);
//		ft_putchar_fd('\n', 2);
//	}
//}
