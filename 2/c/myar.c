#define BLOCK_SIZE 1024		// bytes
/*
 * use lstat instead of stat!
 * almost all code for this project is in textbook
 * 71 while numRead read section is helpful
 */
/* must be run before get_next_header */
	lseek(fd, 0, SEEK_SET);
/*
 * assumes file offset only edited by self and check_file()
 * pass in header to get, output header absolute offset
 */
		/* advance past content */
		if ((lseek(fd, atoi(out->ar_size), SEEK_CUR) % 2) == 1) {
			/* ensure an even byte boundary */
			lseek(fd, 1, SEEK_CUR);
		}
/* strip trailing whitespace, if backslash then turn into valid fname */
	/* strip trailing whitespace (and backspaces if enabled) */
	/* null terminate after valid, buffer could have other crap in it */
	assert(ret == SARMAG);
off_t find_header(int fd, char *fname, struct ar_hdr * out)
		hdr_offset = get_next_header(fd, out);
	} while (strcmp(fix_str(out->ar_name, sizeof(out->ar_name), true),
			fname) != 0);
bool create_header(char *fname, struct ar_hdr * out)
	struct stat buf;

	if (lstat(fname, &buf) == -1) {
		return (false);
	}
	/* fill ar_hdr struct */
	snprintf(out->ar_name, sizeof(out->ar_name), "%s/", fname);
	snprintf(out->ar_date, sizeof(out->ar_date), "%llu",
			(long long unsigned int)buf.st_mtime);
	snprintf(out->ar_uid, sizeof(out->ar_uid), "%llu",
			(long long unsigned int)buf.st_uid);
	snprintf(out->ar_gid, sizeof(out->ar_gid), "%llu",
			(long long unsigned int)buf.st_gid);
	snprintf(out->ar_mode, sizeof(out->ar_mode), "%llo",
			(long long unsigned int)(buf.st_mode));
	snprintf(out->ar_size, sizeof(out->ar_size), "%llu",
			(long long unsigned int)buf.st_size);
	memcpy(out->ar_fmag, ARFMAG, sizeof(out->ar_fmag));
	/* strip newlines created by snprintf */
	for (int i = 0; i < sizeof(struct ar_hdr); ++i) {
		if (((char *)out)[i] == '\0') {
			((char *)out)[i] = ' ';
		}
	}
	return (true);
}
bool append_file(int fd, char *fname)
{
	struct ar_hdr *hdr = malloc (sizeof (struct ar_hdr));
	char buf[BLOCK_SIZE];
	int file_fd;
	ssize_t num_read;
	/* seek to end of archive */
	/* each archive file members begins on an even byte boundary */
	if ((lseek(fd, 0, SEEK_END) % 2) == 1) {
		write(fd, "\n", 1);
	}
	/* generate header, add to archive */
	if (create_header(fname, hdr)) {
		write(fd, (char *) hdr, sizeof(struct ar_hdr));
	}
	file_fd = open(fname, O_RDONLY);
	while ((num_read = read(file_fd, buf, BLOCK_SIZE)) > 0) {
		if (write(fd, buf, num_read) != num_read) {
			return (false);
		}
	}
	errno = 0;
	if (close(file_fd) == -1) {
		printf("Error %d on closing %s. Check contents", errno,
		       fname);
	}
	off_t new_end;
	off_t size = end - start;
	lseek(fd, end + 1, SEEK_SET);
		cur = lseek(fd, 0, SEEK_CUR);
		/* jump back to over write previous block */
		lseek(fd, cur - num_read - size - 1, SEEK_SET);
		if (write(fd, buf, num_read) != num_read) {
			return (false);
		lseek(fd, cur + size - 1, SEEK_SET);
	new_end = lseek(fd, 0, SEEK_END) - size - 1;
	ftruncate(fd, new_end);
	tmp = malloc(sizeof(struct ar_hdr));
	file_end =
	    file_start + (off_t) (sizeof(struct ar_hdr) + atoll(tmp->ar_size));
	return (delete_bytes(fd, file_start, file_end));
	// get file header from archive
	// create new file with proper name
	// change new file mode
	// copy relevant lines over
	// delete lines from archive
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
			printf("%s/",
			       fix_str(tmp->ar_uid, sizeof(tmp->ar_uid),
				       false));
			printf("%s     ",
			       fix_str(tmp->ar_gid, sizeof(tmp->ar_gid),
				       false));
			printf("%s ", fix_str(tmp->ar_size, sizeof(tmp->ar_size),
				       false));
		printf("%s\n",
		       fix_str(tmp->ar_name, sizeof(tmp->ar_name), true));
bool append_all(int fd)
{
	return (false);
}

bool interpret_and_call(int fd, char key, int argc, char **argv)
{
	switch (key) {
	case 'q':		// quickly append named files to archive
		for (int i = 3; i < argc; ++i) {
			append_file(fd, argv[i]);
		}
		break;
	case 'x':		// extract named files
		for (int i = 3; i < argc; ++i) {
			extract_file(fd, argv[i]);
		}
		break;
	case 't':		// print a concise table of contents of archive
		print_archive(fd, false);
		break;
	case 'v':		// print a verbose table of contents of archive
		print_archive(fd, true);
		break;
	case 'd':		// delete named files from archive
		for (int i = 3; i < argc; ++i) {
			printf("delete: '%d'", (int) delete_file(fd, argv[i]));
		}
		break;
	case 'A':		// quickly append all "regular" files in the current dir
		assert(argc == 2);
		append_all(fd);
		break;
	case 'w':		// for a timeout, add all modified files to the archive
		//bonus
		assert(argc == 4);
		timeout_add(fd, (time_t) atoi(argv[3]));
		break;
	default:		// unsupported operation
		printf("invalid option -- '%c'\n", key);
		break;
	}

	return (true);
}

	// consider archive init function
		// create an archive file with perms `666` only for q
		// puke otherwise...
		printf("%s: Malformed archive", archive);
	/* handle function calls */
	interpret_and_call(fd, key, argc, argv);
		return (EXIT_FAILURE);