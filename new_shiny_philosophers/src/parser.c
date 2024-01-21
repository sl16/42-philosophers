/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 20:16:03 by vbartos           #+#    #+#             */
/*   Updated: 2024/01/21 23:57:10 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	check_args(int argc)
{
	if (argc < 5 || argc > 6)
		ft_exit_error("Use 4 arguments (5th optional).", NULL);
}

void	check_format(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			ft_exit_error("Provide digit arguments only.", NULL);
		i++;
	}
}

void	check_intmax(char *arg)
{
	int	num;

	num = ft_atoi(arg);
	if (num < 0)
		ft_exit_error("Provide a valid number.", NULL);
}


int	parser(int argc, char **argv)
{
	int	i;

	
	check_args(argc);
	i = 1;
	while (argv[i] != NULL)
	{
		check_format(argv[i]);
		check_intmax(argv[i]);
		i++;
	}
	
	//parse the values into the struct

}