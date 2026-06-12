#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

int		main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	char	*input;

	input = ttyname(1);

	printf("%s\n", input);

	printf("%d\n", ttyslot());

	// ioctl(int fd, unsigned long request, ...);

	return (0);
}

/*

::::::::::::::::::   TERMINAL INFORMATION   ::::::::::::::::::

char	*ttyname(int fd);

Return the name of a termianl. What does this actually mean? I
need to understand character device files or something?

Learning character device files.

There are many types of files
	- Regular files
	- Character device files
	- Block device files
	- Directory files

/dev/pts
crw--w---- 1 user	tty  136, 0  date  0
crw--w---- 1 user	tty  136, 1  date  1
crw--w---- 1 user	tty  136, 2  date  2
c--------- 1 root	root   5, 2	 date  ptmx

^^^^^^^^^^^^^^^^^^^^^^^^^^
What am I looking at here?

So character device files. I need to undestand this more.

::::::::::::::::::   READLINE FUNCTION   ::::::::::::::::::

This function returns the text of the line read. So I shou-
ld be able to  store the line  and then  print it out. Lets
try.

UNDERTSTANDING CC FLAGS
	+ -L	: where to search for libraries
	+ -l	: which libary to link againsts
	+ -I	: where to find header files

Specifically  for  the -l flag . Some libraries are "shared
libraries" on  the  system  so  if I use the -l flag flowed
by the name  of the  library then I  am able to include the
libary when compling.

::::::::::::::::::   CONTROLING OTHER DEVICES   ::::::::::::::::::

open() → connect to the device
read() / write() → move data
ioctl() → control the device
ioctl  ----> stands for Input & Output Control

EXAMPLE

@ fd 		:	The file descriptor of the process
@ TCGETS	:	This is a constant from the device driver
@ &settings	:	The address to the struct. This struct will be filled with the
				current  settings of  the device driver. I can them manipulate
				these values and send them back.

int	ioctl(fd, TCGETS, &settings);





*/
