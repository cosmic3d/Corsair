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

#include "../corsair.h"

int free_g(t_global *g)
{
	if (g->gcd)
		BN_clear_free(g->gcd);
	if (g->vars.e)
		BN_clear_free(g->vars.e);
	if (g->vars.n)
		BN_clear_free(g->vars.n);
	if (g->vars.q)
		BN_clear_free(g->vars.q);
	if (g->vars2.e)
		BN_clear_free(g->vars2.e);
	if (g->vars2.n)
		BN_clear_free(g->vars2.n);
	if (g->vars2.q)
		BN_clear_free(g->vars2.q);
	return (0);
}

int main(int argc, char **argv)
{
	t_global	g;

	int	i = 1;
	int	j;

	if (error_args(argc, argv) == -1)//Managing argument errors
		return(0);
	//We initialize some variables
	g.vars.factor_found = 0;
	g.vars2.factor_found = 0;
	g.vars.q = BN_new();
	g.gcd = BN_new();
	//We compare every single certificate with each other and try to find a GCD != 1
	while(i < argc - 1 && g.vars.factor_found == 0)
	{
		j = i + 1;
		if (set_ne(&g, argv[i], 0) == -1)//We establish the values for the first certificate
			return (free_g(&g));
		while (j < argc && g.vars2.factor_found == 0)
		{
			if (set_ne(&g, argv[j], 1) == -1)//We establish the values for the second certificate
				return (free_g(&g));
			if (print_ne(&g, argv[i], argv[j]) == -1)//We print the values of both certificates
				return (free_g(&g));
			if (euclides_shit(&g, argv[i], argv[j]) == -1)//We check if there's a GCD != 1 between this two certificates
				return (free_g(&g));
			j++;
			if (g.vars.factor_found != 1 && g.vars2.factor_found != 1)//We free the variables used in case there's no gcd != 1 yet 
			{
				BN_clear_free(g.vars2.n);
				BN_clear_free(g.vars2.e);
			}
		}
		i++;
		if (g.vars.factor_found != 1 && g.vars2.factor_found != 1)//We free the variables used in case there's no gcd != 1 yet 
		{
			BN_clear_free(g.vars.n);
			BN_clear_free(g.vars.e);
		}
	}
	if (g.vars.factor_found == 1 && g.vars2.factor_found == 1)//In case we find a GCD != 1, we start creating the private key
	{
		char *gcd;
		char *q;

		green();
		printf("\n\nA gcd(n1, n2) != 1 has been found!\n\n");
		reset();
		if (get_q(&g) == -1)//We get the q value for creating the private key
			return (free_g(&g));
		gcd = BN_bn2dec(g.gcd);
		q = BN_bn2dec(g.vars.q);
		cpk(gcd, q);//We create and print the private key
		return (free_g(&g));
	}
	else
	{
		yellow();
		printf("\n\nNo gcd(n1, n2) != 1 has been found\n\n");
		reset();
	}
    return (free_g(&g));
}
