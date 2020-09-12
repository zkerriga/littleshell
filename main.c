/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:58:02 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/12 14:58:06 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int loop(char **envp)
{
	char	*cmd_line;
	char	*clean_cmd_line;
	t_list	*cmd_list;
	int		status;

	status = 1; //TODO: сделать штуку, которая отчистит терминал
	while (status)
	{
		write(1, "$> ", 3);
		cmd_line = read_line();
		clean_cmd_line = clear_comand_line(cmd_line);
		cmd_list = parse_comands(clean_cmd_line);
		status = exec_all_comands(cmd_list);
		free(cmd_line);
		free(clean_cmd_line);
		ft_list_clear(cmd_list);
	}
}

int main(int ac, char **av, char **envp)
{
	loop(envp);
	return (0);
}
