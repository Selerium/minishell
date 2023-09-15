/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:17:59 by jebucoy           #+#    #+#             */
/*   Updated: 2023/09/15 23:13:33 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_name(char *input)
{
	size_t	i;
	size_t	start;
	char 	*env_name;

	i = 1;
	start = 1;
	while (ft_isalnum(input[i]) || input[i] == '_')
		i++;
	env_name = ft_substr(input, start, i - start);
	return (env_name);
}

char	*replace_env(char *input, size_t *idx, char *var_name, t_env *env)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*mixitup;
	size_t tmp_idx = *idx + 1;

	// printf("##############################\n");
	// printf("#           HERE             #\n");
	// printf("#            YOU             #\n");
	// printf("#             GO             #\n");
	// printf("##############################\n");
	tmp1 = ft_substr(input, 0, *idx);
	// printf("var_name: [%s]\n", var_name);
	tmp2 =  !var_name || !var_name[0] ? ft_strdup("") : ft_strdup(env->value);
	while (isalnum(input[tmp_idx]) || input[tmp_idx] == '_')
		tmp_idx++;
	// printf("tmp_idx after: %zu\n", tmp_idx);
	// tmp3 = ft_substr(input, (*idx), ft_strlen(input) - (*idx) - ft_strlen(var_name) - 1);
	(void)var_name;
	tmp3 = ft_substr(input, tmp_idx, ft_strlen(input) - tmp_idx);
	// printf("skip middle: %zu\n", ft_strlen(input) - tmp_idx);
	(*idx) += ft_strlen(env->value) - 1;
	// printf("new idx: %zu\n", *idx);
	mixitup =ft_strjoin(tmp1, tmp2);
	free (input);
	input = ft_strjoin(mixitup, tmp3);
	// printf("\ttmp1: [%s]\n", tmp1);
	// printf("\ttmp2: [%s]\n", tmp2);
	// printf("\ttmp3: [%s]\n", tmp3);
	// printf("\tmixitup: [%s]\n", mixitup);
	// printf("\tinput: [%s]\n", input);
	// printf("final boss: [%s]\n", input);
	free (tmp1);
	free (tmp2);
	free (tmp3);
	free (mixitup);
	return (input);
}
// echo /Users/jebucoy/Documents/projects/minishell

char	*expand_env(char *input, t_minishell shell)
{
	char	*name;
	t_env	*val;
	size_t	i;

	i = 0;
	while (input[i])
	{
		// printf("i inside the loop: [%zu]\n", i);
		if (input[i] == '$')
		{
			// printf("before input + i: [%s]\n", input + i);
			name = get_env_name(input + i);
			// printf("name: [%s]\n", name);
			val = get_env(name, shell);
			// if (!val)
				// printf("DANGERRDANGERR DANGERRR\n");
			input = replace_env(input, &i, name, val);
			// printf("i after replace: [%zu]\n", i);
			// printf("final input + i: [%s]\n", input);
		}
		if (input[i])
			i++;
	}
	return (input);
}
/*go through each node in linked list*/
/*go through each array
	if string contains '$'
	check if its inside quotes,
	if DOUBLE
		return env value
	if SINGLE
		return literal string
	then check if env var exists
	if exists
		replace with env value
	if not
		return empty string
	*/