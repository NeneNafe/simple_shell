#include "shell.h"

/**
 * main - entry point of the simple shell
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	infor_t info[] = { INFO_init };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));
	if (argc == 2)
	{
		fd = open(argv[1], 0_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCESS)
				exit(126);
			if (errno == ENOENT)
			{
				_nputs(argv[0]);
				_nputs(": 0: Can't open");
				_nputs(argv[1]);
				_cputchar('\n');
				_cputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_hist(info);
	shell_loop(info, argv);
	return (EXIT_SUCCESS);
}
