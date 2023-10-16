/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 08:01:05 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/16 08:17:26 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>



int main(int argc, char **argv, char **env)
{
    (void) argv;
    (void) env;
    if (argc < 5)
    {
        perror ("error on argv");
        return (EXIT_FAILURE);
    }
    return (0);
}
