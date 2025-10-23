
#include "minishell.h"

void	ft_envdelone(t_env *env)
{
	if (env)
	{
		free(env->key);
		if (env->value)
			free(env->value);
		free(env);
	}
}
