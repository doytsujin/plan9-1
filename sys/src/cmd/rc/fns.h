void	Abort(void);
void	Closedir(int);
int	Creat(char*);
int	Dup(int, int);
int	Dup1(int);
int	Eintr(void);
int	Executable(char*);
void	Execute(word*,  word*);
void	Exit(char*);
int	Globsize(char*);
int	Isatty(int);
void	Memcpy(char*, char*, long);
void	Noerror(void);
int	Opendir(char*);
long	Read(int, char*, long);
int	Readdir(int, char*, int);
long	Seek(int, long, long);
void	Trapinit(void);
void	Unlink(char*);
void	Updenv(void);
void	Vinit(void);
int	Waitfor(int, int);
long	Write(int, char*, long);
int	advance(void);
int	back(int);
void	cleanhere(char*);
void	codefree(code*);
int	compile(tree*);
char *	list2str(word*);
int	count(word*);
void	deglob(char*);
void	dotrap(void);
void	freenodes(void);
void	freewords(word*);
void	globlist(void);
int	idchr(int);
void	itoa(char*, long);
void	kinit(void);
int	match(char*, char*, int);
int	matchfn(char*, char*);
void	panic(char*, int);
void	poplist(void);
void	popword(void);
void	pprompt(void);
void	pushlist(void);
void	pushredir(int, int, int);
void	pushword(char*);
void	readhere(void);
void	setstatus(char*);
void	setvar(char*, word*);
void	skipnl(void);
void	start(code*, int, var*);
int	truestatus(void);
void	usage(char*);
int	wordchr(int);
void	yyerror(char*);
int	yylex(void);
int	yyparse(void);
