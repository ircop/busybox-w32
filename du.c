/*
 * Mini du implementation for busybox
 *
 *
 * Copyright (C) 1999 by Lineo, inc.
 * Written by John Beppu <beppu@lineo.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */

#include "internal.h"
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdio.h>
#if 0
#include <unistd.h>
#include <sys/stat.h>
#endif

static const char du_usage[] =
"Usage: du [OPTION]... [FILE]...\n";

typedef void (Display)(size_t, char *);

static void
print(size_t size, char *filename)
{
    fprintf(stdout, "%-7d %s\n", (size >> 1), filename);
}

/* tiny recursive du */
static size_t
du(char *filename)
{
    struct stat statbuf;
    size_t	sum;

    if ((lstat(filename, &statbuf)) != 0) { return 0; }
    sum = statbuf.st_blocks;

    if (S_ISDIR(statbuf.st_mode)) {
	DIR		*dir;
	struct dirent	*entry;

	dir = opendir(filename);
	if (!dir) { return 0; }
	while ((entry = readdir(dir))) {
	    char newfile[512];
	    char *name = entry->d_name;

	    if (  (strcmp(name, "..") == 0)
	       || (strcmp(name, ".")  == 0)) 
	    { continue; }

	    sprintf(newfile, "%s/%s", filename, name);
	    sum += du(newfile);
	}
	closedir(dir);
	print(sum, filename);
    }
    return sum;
}

int 
du_main(int argc, char **argv)
{
    int i;
    char opt;

    /* parse argv[] */
    for (i = 1; i < argc; i++) {
	if (argv[i][0] == '-') {
	    opt = argv[i][1];
	    switch (opt) {
		case 's':
		    break;
		case 'h':
		    usage(du_usage);
		    break;
		default:
		    fprintf(stderr, "du: invalid option -- %c\n", opt);
		    usage(du_usage);
	    }
	} else {
	    break;
	}
    }

    /* go through remaining args (if any) */
    if (i >= argc) {
	du(".");
    } else {
	for ( ; i < argc; i++) {
	    printf("%-7d %s\n", du(argv[i]) >> 1, argv[i]);
	}
    }

    exit(0);
}

/* $Id: du.c,v 1.3 1999/12/10 06:45:42 andersen Exp $ */
