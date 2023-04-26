#include "main.h"

/**
 * check_fd - checks the success of the open system call
 * @fd: file descriptor of the open system call
 * @ptr: array of strings
 * Return: 0 if fd succeds, else 1
 */
int check_fd(int fd, char **ptr)
{
	if (fd == -1)
	{
		if (errno == EACCES)
			exit(126);
		if (errno == ENOENT)
		{
			err_puts(ptr[0]);
			err_puts(": 0: Can't open ");
			err_puts(ptr[1]);
			err_putc('\n');
			err_putc(BUFF_FLUSH);
			exit(127);
		}
		return (1);
	}
	return (0);
}

/**
 * main - entry point to program
 * @ac: number of command line arguments
 * @av: string array of command line arguments
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (check_fd(fd, av))
			return (EXIT_FAILURE);
		info->readfd = fd;
	}
	fill_env_list(info);
	hist_read(info);
	loop_hsh(info, av);
	return (EXIT_SUCCESS);
}
