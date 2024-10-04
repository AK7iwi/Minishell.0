/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:41:20 by diguler           #+#    #+#             */
/*   Updated: 2024/10/04 14:24:06 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Gérer les redirections (pipes et fichiers)
// Gérer les processus enfants et les commandes internes
// Gérer les erreurs et les signaux
// Optimiser la libération des ressources et la modularité du code

void	exec_command(char **env, t_cmd *cmd)
{
	char	*path;
	char	**find_the_path;

	find_the_path = find_path(env);
	path = valid_path(find_the_path, cmd->args[0]);
	if (execve(path, cmd->args, env) == -1)
	{
		ft_putstr_fd("Command not found : ", 2);
		ft_putendl_fd(cmd->args[0], 2);
		free_tab(find_the_path);
		exit(EXIT_FAILURE);
	}
}

// void exec_pipeline(t_cmd *cmds, char **env)
// {
//     int tube[2];
//     pid_t pid;
//     int fd_in = 0;
//     int i = 0;
//     printf("arg 1 : %s\n", cmds->args[0]);
//     while (cmds->args[i] != NULL)
//     {
//         if (cmds->args[i + 1] != NULL)
//             create_pipe(tube);
//         pid = fork();
//         handle_fork(pid, env, cmds, fd_in, tube);
//         if (pid > 0)
//         {
//             wait(NULL);
//             close(tube[1]);
//             if(fd_in != 0)
//                 close(fd_in);
//             fd_in = tube[0];
//         }
//         i++;
//     }
// }

char *find_command_in_path(char *cmd)
{
    char *path_env = getenv("PATH");
    char **paths = ft_split(path_env, ':');  // Split la variable PATH avec ':'
    char *full_path;
    int i = 0;
    while (paths[i])
    {
        full_path = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(full_path, cmd);

        // Vérifier si le fichier existe et est exécutable
        if (access(full_path, X_OK) == 0)
            return full_path;

        i++;
    }
    return NULL;  // Si le fichier n'est pas trouvé dans les répertoires du PATH
}


void exec_cmd(char **args, char **env)
{
    char *cmd_path = find_command_in_path(args[0]);
    if (cmd_path == NULL)
    {
        fprintf(stderr, "command not found: %s\n", args[0]);
        exit(EXIT_FAILURE);
    }
    if (execve(cmd_path, args, env) == -1)
    {
        perror("execve");
        exit(EXIT_FAILURE);
    }
}


void exec_ast_pipeline(t_ast *ast, char **env)
{
    int tube[2];      
    pid_t pid; 
    int fd_in = 0;  
    int status; 

    if (ast == NULL)
        return;

    if (ast->type == AST_OPERATOR && ast->operator.type == AST_PIPE)
    {
        if (pipe(tube) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) 
        {
            dup2(tube[1], STDOUT_FILENO);
            close(tube[0]); 
            close(tube[1]);
            exec_ast_pipeline(ast->operator.left, env);
        }
        else 
        {
            waitpid(pid, &status, 0);

            fd_in = tube[0];
            close(tube[1]); 

            pid = fork();
            if (pid == -1)
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }

            if (pid == 0) 
            {
                dup2(fd_in, STDIN_FILENO);
                close(fd_in);

                exec_ast_pipeline(ast->operator.right, env);
                exit(EXIT_SUCCESS);  
            }
            else
            {
                waitpid(pid, &status, 0);
                close(fd_in);
            }
        }
    }
    else if (ast->type == AST_COMMAND)
    {
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
            exec_cmd(ast->cmd.args, env); 
        else 
            waitpid(pid, &status, 0);
    }
}

void exec_pipeline(t_ast *ast, char **env)
{
    int tube[2];
    pid_t pid;
    int fd_in = 0;

    if (ast == NULL)
        return;

    if (ast->type == AST_OPERATOR && ast->operator.type == AST_PIPE)
    {
        create_pipe(tube);

        pid = fork();
        if (pid == 0) 
        {
            dup2(tube[1], STDOUT_FILENO);
            close(tube[0]); 
            close(tube[1]);

            exec_ast_pipeline(ast->operator.left, env);
            exit(EXIT_SUCCESS); 
        }
        else if (pid > 0) 
        {
            wait(NULL);

            fd_in = tube[0];
            close(tube[1]);

            pid = fork();
            if (pid == 0) 
            {
                dup2(fd_in, STDIN_FILENO);
                close(fd_in); 
                exec_ast_pipeline(ast->operator.right, env);
                exit(EXIT_SUCCESS);
            }
            else
            {
                wait(NULL);
                close(fd_in);
            }
        }
    }
    else if (ast->type == AST_COMMAND)
    {
        pid = fork();
        if (pid == 0) 
        {
            exec_cmd(ast->cmd.args, env);
            perror("exec_cmd");
            exit(EXIT_FAILURE);
        }
        else if (pid > 0) 
            wait(NULL); 
    }
}
