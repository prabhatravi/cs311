#include <dirent.h>
#define BLOCK_SIZE 1024		// bytes
	assert((fd >= 0));

	if (lseek(fd, 0, SEEK_SET) != 0)
		return (false);

	if (read(fd, buf, SARMAG) != SARMAG)
		return (false);

	/* Finally, can check to ensure strings are the same */
	if (strncmp(buf, ARMAG, sizeof(buf)) != 0)
	off_t hdr_offset;
	off_t arsize;

	assert((fd >= 0) && (out != NULL));
	if ((hdr_offset = lseek(fd, 0, SEEK_CUR)) == -1)
		return (hdr_offset);

	if ((size_t) (read(fd, buf, sizeof(buf))) != sizeof(buf))
		return (-1);

	/* Try filling the struct with a cast */
	memcpy(out, buf, sizeof(*out));

	/* advance past content */
	arsize = atoll(out->ar_size);
	if ((arsize % 2) == 1)
		++arsize;
	if (lseek(fd, arsize, SEEK_CUR) == -1)
		return (-1);
	return (hdr_offset);
	size_t idx;
	assert((str != NULL) && (len > 0));

	idx = (size_t) (len - 1);
	while (isspace(str[idx]) || (backslash && (str[idx] == '/')))
	int flags = (O_RDWR | O_CREAT | O_EXCL);
	assert(fname != NULL);

	if ((fd = open(fname, flags, 0666)) == -1)
		return (fd);
	/* If error writing to archive, try unlinking it and exit with error */
	if (write(fd, ARMAG, SARMAG) != SARMAG) {
		fd = -1;
		unlink(fname);
	assert((fd >= 0) && (fname != NULL) && (out != NULL));

		if ((hdr_offset = get_next_header(fd, out)) == -1)
	} while (strcmp
		 (fix_str(out->ar_name, (int) sizeof(out->ar_name), true),
		  fname) != 0);
void replace_chars(char *str, int len, char from, char to)
{
	assert((str != NULL) && (len > 0));

	for (int i = 0; i < len; ++i) {
		if (str[i] == from)
			str[i] = to;
	}
}

bool create_header(char *fname, struct ar_hdr *out)
	assert((fname != NULL) && (out != NULL));

		 (long long unsigned int) buf.st_mtime);
		 (long long unsigned int) buf.st_uid);
		 (long long unsigned int) buf.st_gid);
		 (long long unsigned int) (buf.st_mode));
		 (long long unsigned int) buf.st_size);

	replace_chars((char *) out, sizeof(struct ar_hdr), '\0', ' ');

	struct ar_hdr *hdr = malloc(sizeof(struct ar_hdr));
	assert((fd >= 0) && (fname != NULL));

	if ((lseek(fd, 0, SEEK_END) % 2) == 1)

	} else {
		return (false);

	/* copy contents */
		if (write(fd, buf, num_read) != num_read)

	/* catch errors */
		return (false);
	assert((size > 0) && (fd >= 0));



		if (write(fd, buf, num_read) != num_read)


	off_t file_start;
	assert((fd >= 0) && (fname != NULL));

	    file_start + (off_t) (sizeof(struct ar_hdr) +
				  atoll(tmp->ar_size));
	free(tmp);
	char buf[BLOCK_SIZE];
	off_t content_start;
	off_t cur;
	off_t file_start;
	off_t file_end;
	int new_fd;
	ssize_t num_read;
	ssize_t read_size;
	mode_t perm;
	struct ar_hdr *tmp;

	assert((fd >= 0) && (fname != NULL));

	/* get file header from archive */
	tmp = malloc(sizeof(struct ar_hdr));
	file_start = find_header(fd, fname, tmp);
	content_start = (file_start + sizeof(struct ar_hdr));
	file_end = content_start + (off_t) (atoll(tmp->ar_size));

	/* create new file with proper name and mode */
	perm = (mode_t) strtol(tmp->ar_mode, NULL, 8);

	new_fd = open(fix_str(tmp->ar_name, sizeof(tmp->ar_name), true),
		      (O_WRONLY | O_CREAT | O_EXCL), perm);
	if (new_fd == -1) {
		return (false);
	}

	/* copy relevant lines over */
	cur = lseek(fd, content_start, SEEK_SET);
	read_size = BLOCK_SIZE;
	if ((cur + read_size) > file_end) {
		read_size = file_end - cur;
	}
	while ((num_read = read(fd, buf, read_size)) > 0) {
		write(new_fd, buf, num_read);
		cur += num_read;
		if ((cur + read_size) > file_end) {
			read_size = file_end - cur;
		}
	}

	/* delete lines from archive */
	delete_bytes(fd, file_start, file_end);
	/* close new file */
	close(new_fd);

	assert((octal != NULL));

		 ((perm & S_IRUSR) ? 'r' : '-'),
		 ((perm & S_IWUSR) ? 'w' : '-'),
		 ((perm & S_IXUSR) ? ((perm & S_ISUID) ? 's' : 'x') :
		  ((perm & S_ISUID) ? 'S' : '-')),
		 ((perm & S_IRGRP) ? 'r' : '-'),
		 ((perm & S_IWGRP) ? 'w' : '-'),
		 ((perm & S_IXGRP) ? ((perm & S_ISGID) ? 's' : 'x') :
		  ((perm & S_ISGID) ? 'S' : '-')),
		 ((perm & S_IROTH) ? 'r' : '-'),
		 ((perm & S_IWOTH) ? 'w' : '-'),
		 ((perm & S_IXOTH) ? ((perm & S_ISVTX) ? 't' : 'x') :
		  ((perm & S_ISVTX) ? 'S' : '-')));
	assert((epoch != NULL));

	assert((fd >= 0));

			/* print additional file information */
			printf("%s ",
			printf("%6s ",
			       fix_str(tmp->ar_size, sizeof(tmp->ar_size),
		/* always print file names */
	assert((fd >= 0));
bool append_all(int fd, char *self)
	DIR *cur_dir;
	struct dirent *entry;

	assert((fd >= 0) && (self != NULL));

	errno = 0;
	cur_dir = opendir(".");

	if (cur_dir == NULL) {
		return (false);
	}
	while ((entry = readdir(cur_dir)) != NULL) {
		if ((entry->d_type == DT_REG)
		    && (strcmp(entry->d_name, self) != 0)) {
			append_file(fd, entry->d_name);
		}
	}

	return (true);
}

void usage(void)
{
	printf("\nCS 311 Project 2: UNIX File I/O\n"
	       "-h  print this help\n"
	       "-q  quickly append named files to archive\n"
	       "-x  extract named files\n"
	       "-t  print a concise table of contents of the archive\n"
	       "-v  print a verbose table of contents of the archive\n"
	       "-d  delete named files from archive\n"
	       "-A  quickly append all ``regular'' files in the current dir\n"
	       "-w  for a given timeout, add all modified files to archive\n");

	assert((fd >= 0) && (cnt > 0) && (args != NULL));

		/* quickly append named files to archive */
	case 'h':
		break;
				ret &= append_file(fd, args[i]);
		/* extract named files from archive */
		/* print a concise table of contents of archive */
		/* print a verbose table of contents of archive */
		/* delete named files from archive */
		/* quickly append all "regular" files in the current dir */
		if (cnt == 3) {
			ret = append_all(fd, args[2]);
		/* for a timeout, add all modified files to the archive */
		/* unsupported operation */
bool check_args(int argc, char **argv)
{
	assert((argc > 0) && (argv != NULL));

	/* Syntax "myar key afile name ..." where afile=archive, key=opt */
	if (strlen(argv[1]) != 2) {
		printf("%s: Incorrectly sized key/option\n", argv[1]);
		return (false);
	}
	if (argv[1][0] != '-') {
		printf("%s: Invalid key (missing '-'?)\n", argv[1]);
		return (false);
	}
	if (argc < 3) {
		if (argv[1][1] != 'h') {
			printf("%d: Missing at least one argument\n",
			       argc);
		}
		return (false);
	}
	for (int i = 3; i < argc; ++i) {
		if (strlen(argv[i]) > 15) {
			printf("%s: Filename is too long.", argv[i]);
			return (false);
		}
	}

	return (true);
}

	/* check input argument validity */
	if (!check_args(argc, argv)) {
		usage();
		return (EXIT_FAILURE);
	}
		} else {
			printf("%s: Error opening archive\n", archive);
			return (EXIT_FAILURE);
		printf("%s: Malformed archive\n", archive);
		printf("-%c: Error occurred during execution\n", key);
		printf("%d: Error on archive close, data loss?\n", errno);
