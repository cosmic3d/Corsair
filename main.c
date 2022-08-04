/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 16:27:22 by jenavarr          #+#    #+#             */
/*   Updated: 2022/07/22 16:27:26 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corsair.h"

int main(int argc, char **argv)
{
	t_global	g;


	int	i = 1;
	int	j;

	if (error_args(argc, argv) == -1)//Comprobamos errores de argumentos
		return(0);
	g.vars.factor_found = 0;
	g.vars2.factor_found = 0;
	g.vars.n = BN_new();
	g.vars2.n = BN_new();
	g.vars.e = BN_new();
	g.vars2.e = BN_new();
	g.gcd = BN_new();
	//Comparamos todos los certificados hasta que veamos que el mcd de algunos es distinto de 1
	while(i < argc - 1 && g.vars.factor_found == 0)
	{
		j = i + 1;
		if (set_ne(&g, argv[i], 0) == -1)
				return (0);
		while (j < argc && g.vars2.factor_found == 0)
		{
			if (set_ne(&g, argv[j], 1) == -1)
				return (0);
			if (print_ne(&g, argv[i], argv[j]) == -1)
				return (0);
			if (euclides_shit(&g, argv[i], argv[j]) == -1)
				return (0);
			j++;
		}
		i++;
	}
	if (g.vars.factor_found == 1 && g.vars2.factor_found == 1)
	{
		green();
		printf("\n\nA gcd(n1, n2) != 1 has been found!\n\n");
		reset();
	}
	else
	{
		yellow();
		printf("\n\nNo gcd(n1, n2) != 1 has been found\n\n");
		reset();
	}
    return (0);
}