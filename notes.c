/*
::::::::::::::::::   STUDY   :::::::::::::::::::::
Below is a range of functions I need to understand
and use. I want to play around  with each of  them
so  I can  get a good understanding of  how to use
them correctly.

::::::::::::::::::   PROMPT   ::::::::::::::::::::: DONE
char	*readline(const char *prompt);


::::::::::::::::::   MANAGE HISTORY   ::::::::::::::::::::: DONE

void	rl_clear_history(void);
void	add_history(const char *string);
int		rl_on_new_line(void);
int		rl_replace_line(const char *text, int clear_undo);
int		rl_redisplay(void);

::::::::::::::::::   MANAGE FILE   ::::::::::::::::::::: DONE

int		access(const char *pathname, int mode);
int		open(const char *pathname, int flags, ...);
int		close(int fd);
ssize_t read(int fd, void *buf, size_t count);

::::::::::::::::::   MANAGE PROCESS   :::::::::::::::::::::

pid_t	fork(void);
pid_t	wait(int *status);
pid_t	waitpid(pid_t pid, int *status, int options);
pid_t	wait3(int *status, int options, struct rusage *rusage);
pid_t	wait4(pid_t pid, int *status, int options, struct rusage *rusage);

::::::::::::::::::   MANAGE SINGNALS   :::::::::::::::::::::

void	(*signal(int sig, void (*handler)(int)))(int);
int		sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
int		sigemptyset(sigset_t *set);
int		sigaddset(sigset_t *set, int signum);
int		kill(pid_t pid, int sig);

::::::::::::::::::   MANAGE DIRECTORIES   :::::::::::::::::::::

char	*getcwd(char *buf, size_t size);
int		chdir(const char *path);
DIR		*opendir(const char *name);
struct	dirent *readdir(DIR *dirp);
int		closedir(DIR *dirp);

::::::::::::::::::   MANAGE FILE STATUS   :::::::::::::::::::::

int		stat(const char *pathname, struct stat *statbuf);
int		lstat(const char *pathname, struct stat *statbuf);
int		fstat(int fd, struct stat *statbuf);

::::::::::::::::::   MANAGE ERRORS   :::::::::::::::::::::

char	*strerror(int errnum);
void	perror(const char *s);

::::::::::::::::::   TERMINAL INFORMATION   :::::::::::::::::::::

int		ioctl(int fd, unsigned long request, ...);
int		tcsetattr(int fd, int optional_actions, const struct termios *termios_p);
int		tcgetattr(int fd, struct termios *termios_p);
int		tgetent(char *bp, const char *name);
int		tgetflag(const char *id);
int		tgetnum(const char *id);
int		tputs(const char *str, int affcnt, int (*putc)(int));

char	*ttyname(int fd);
char	*tgetstr(const char *id, char **area);
char	*getenv(const char *name);
char	*tgoto(const char *cap, int col, int row);

::::::::::::::::::   OTHER   :::::::::::::::::::::

int		unlink(const char *pathname);
int		execve(const char *pathname, char *const argv[], char *const envp[]);
int		dup2(int oldfd, int newfd);
int		pipe(int pipefd[2]);

*/
