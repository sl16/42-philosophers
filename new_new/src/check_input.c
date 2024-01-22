/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 20:16:03 by vbartos           #+#    #+#             */
/*   Updated: 2024/01/22 20:58:03 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Checks the number of command-line arguments.
 *
 * This function checks if the number of command-line arguments is valid.
 * It expects 4 or 5 arguments, where the 5th argument is optional.
 * If the number of arguments is invalid, it exits the program with
 * an error message.
 *
 * @param argc The number of command-line arguments.
 */
void check_args(int argc)
{
	if (argc < 5 || argc > 6)
		ft_exit_error("Use 4 arguments (5th optional).", NULL);
}

/**
 * @brief Checks the format of a command-line argument.
 *
 * This function checks if a command-line argument is a valid digit.
 * It ensures that the argument contains only digits (0-9).
 * If the format is invalid, it exits the program with an error message.
 *
 * @param arg The command-line argument to be checked.
 */
void check_format(char *arg)
{
	int i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			ft_exit_error("Provide digit arguments only.", NULL);
		i++;
	}
}

/**
 * @brief Checks if a command-line argument is a positive integer.
 *
 * This function checks if a command-line argument can be converted to
 * a positive integer. It uses the ft_atoi function to convert the argument
 * to an integer. If the argument is not a positive integer or is bigger than
 * INT_MAX, it exits the program with an error message.
 *
 * @param arg The command-line argument to be checked.
 */
void check_intmax(char *arg)
{
	int num = ft_atoi(arg);
	if (num < 0)
		ft_exit_error("Provide positive values in INT_MAX range only.", NULL);
}

/**
 * @brief Checks specific command-line arguments based on their index.
 *
 * This function checks specific command-line arguments based on their index.
 * It performs different checks depending on the index value (i).
 * If the argument fails the check, it exits the program with an error message.
 *
 * @param arg The command-line argument to be checked.
 * @param i The index of the command-line argument.
 */
void check_values(char *arg, int i)
{
	if (i == 1)
	{
		if (ft_atoi(arg) < 1)
			ft_exit_error("The simulation requires at least 1 philo.", NULL);
	}
	else if (i == 2 || i == 3 || i == 4)
	{
		if (ft_atoi(arg) < 60)
			ft_exit_error("The time values must be at least 60 ms.", NULL);
	}
	else if (i == 5)
	{
		if (ft_atoi(arg) < 1)
			ft_exit_error("There must be at least 1 round.", NULL);
	}
}

/**
 * @brief Checks the validity of command-line arguments.
 *
 * This function checks the validity of command-line arguments.
 * It calls other functions to perform specific checks on each argument.
 * If any of the arguments fail the checks, it exits the program with an error
 * message.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return 0 if all arguments pass the checks, otherwise exits the program.
 */
int check_input(int argc, char **argv)
{
	check_args(argc);
	int i = 1;
	while (argv[i] != NULL)
	{
		check_format(argv[i]);
		check_intmax(argv[i]);
		check_values(argv[i], i);
		i++;
	}
	return 0;
}
