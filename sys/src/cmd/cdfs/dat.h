enum {
	Maxtrack	= 200,
	Ntrack		= Maxtrack+1,
	BScdrom		= 2048,
	BScdda		= 2352,
	BScdxa		= 2336,
	BSmax		= 2352,
	Nalloc		= 12*BScdda,
	DictBlock	= 1,

	/* scsi peripheral device types */
	TypeDA		= 0,		/* Direct Access (SBC) */
	TypeSA		= 1,		/* Sequential Access (SSC-2) */
	TypeWO		= 4,		/* Worm (SBC)*/
	TypeCD		= 5,		/* CD/DVD/BD (MMC-3) */
	TypeMO		= 7,		/* rewriteable Magneto-Optical (SBC) */
	TypeMC		= 8,		/* Medium Changer (SMC-2) */

	TypeNone	= 0,
	TypeAudio,
	TypeAwritable,
	TypeData,
	TypeDwritable,
	TypeDisk,
	TypeBlank,

	/* Cache control bits in page 8 byte 2 */
	Ccrcd	= 1<<0,		/* read cache disabled */
	Ccmf	= 1<<1,		/* multiplication factor */
	Ccwce	= 1<<2,		/* writeback cache enabled */
	Ccsize	= 1<<3, /* use `cache segment size', not `# of cache segments' */
	Ccdisc	= 1<<4,		/* discontinuity */
	Cccap	= 1<<5,		/* caching analysis permitted */
	Ccabpf	= 1<<6,		/* abort pre-fetch */
	Ccic	= 1<<7,		/* initiator control */

	Cwrite	= 1<<0,
	Ccdda	= 1<<1,

	Nblock = 12,
};

typedef struct Buf Buf;
typedef struct Drive Drive;
typedef struct Track Track;
typedef struct Otrack Otrack;
typedef struct Dev Dev;
typedef struct Msf Msf;		/* minute, second, frame */

struct Msf {
	int	m;
	int	s;
	int	f;
};

struct Track
{
	/* initialized while obtaining the toc (gettoc) */
	vlong	size;		/* total size in bytes */
	long	bs;		/* block size in bytes */
	ulong	beg;		/* beginning block number */
	ulong	end;		/* ending block number */
	int	type;
	Msf	mbeg;
	Msf	mend;


	/* initialized by fs */
	char	name[32];
	int	mode;
	int	mtime;
};

struct DTrack
{
	uchar	name[32];
	uchar	beg[4];
	uchar	end[4];
	uchar	size[8];
	uchar	magic[4];
};

struct Otrack
{
	Track	*track;
	Drive	*drive;
	int	nchange;
	int	omode;
	Buf	*buf;

	int	nref;		/* kept by file server */
};

struct Dev
{
	Otrack*	(*openrd)(Drive *d, int trackno);
	Otrack*	(*create)(Drive *d, int bs);
	long	(*read)(Otrack *t, void *v, long n, long off);
	long	(*write)(Otrack *t, void *v, long n);
	void	(*close)(Otrack *t);
	int	(*gettoc)(Drive*);
	int	(*fixate)(Drive *d);
	char*	(*ctl)(Drive *d, int argc, char **argv);
	char*	(*setspeed)(Drive *d, int r, int w);
};

struct Drive
{
	QLock;
	Scsi;

	int	type;
	int	nopen;
	int	firsttrack;
	int	ntrack;
	int	nchange;
	int	changetime;
	int	nameok;
	int	writeok;

	Track	track[Ntrack];
	ulong	cap;
	uchar	blkbuf[BScdda];

	int	maxreadspeed;
	int	maxwritespeed;
	int	readspeed;
	int	writespeed;
	Dev;

	void *aux;		/* kept by driver */
};

struct Buf
{
	uchar	*data;		/* buffer */
	long	off;		/* data[0] at offset off in file */
	int	bs;		/* block size */
	long	ndata;		/* no. valid bytes in data */
	int	nblock;		/* total buffer size in blocks */
	int	omode;		/* OREAD, OWRITE */
	long	(*fn)(Buf*, void*, long, long);	/* read, write */

	/* used only by client */
	Otrack	*otrack;
};

extern int	vflag;
