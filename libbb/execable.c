/* vi: set sw=4 ts=4: */
/*
 * Utility routines.
 *
 * Copyright (C) 2006 Gabriel Somlo <somlo at cmu.edu>
 *
 * Licensed under GPLv2 or later, see file LICENSE in this tarball for details.
 */

#include "libbb.h"

/* check if path points to an executable file;
 * return 1 if found;
 * return 0 otherwise;
 */
int FAST_FUNC execable_file(const char *name)
{
	struct stat s;
	if (ENABLE_PLATFORM_MINGW32) {
		int len = strlen(name);
		return len >= 4 && !strcasecmp(name+len-4, ".exe") &&
			!stat(name, &s) && S_ISREG(s.st_mode);
	}
	return (!access(name, X_OK) && !stat(name, &s) && S_ISREG(s.st_mode));
}

/* search (*PATHp) for an executable file;
 * return allocated string containing full path if found;
 *  PATHp points to the component after the one where it was found
 *  (or NULL),
 *  you may call find_execable again with this PATHp to continue
 *  (if it's not NULL).
 * return NULL otherwise; (PATHp is undefined)
 * in all cases (*PATHp) contents will be trashed (s/:/NUL/).
 */
#if !ENABLE_PLATFORM_MINGW32
#define next_path_sep(s) strchr(s, ':')
#endif

char* FAST_FUNC find_execable(const char *filename, char **PATHp)
{
	char *p, *n;

	p = *PATHp;
	while (p) {
		n = next_path_sep(p);
		if (n)
			*n++ = '\0';
		if (*p != '\0') { /* it's not a PATH="foo::bar" situation */
			p = concat_path_file(p, filename);
			if (execable_file(p)) {
				*PATHp = n;
				return p;
			}
			if (ENABLE_PLATFORM_MINGW32) {
				int len = strlen(p);
				if (len > 4 && !strcasecmp(p+len-4, ".exe"))
					; /* nothing, already tested by find_execable() */
				else {
					char *np = xmalloc(len+4+1);
					memcpy(np, p, len);
					memcpy(np+len, ".exe", 4);
					np[len+4] = '0';
					if (execable_file(np)) {
						*PATHp = n;
						return np;
					}
				}
			}
			free(p);
		}
		p = n;
	} /* on loop exit p == NULL */
	return p;
}

/* search $PATH for an executable file;
 * return 1 if found;
 * return 0 otherwise;
 */
int FAST_FUNC exists_execable(const char *filename)
{
	char *path = xstrdup(getenv("PATH"));
	char *tmp = path;
	char *ret = find_execable(filename, &tmp);
	free(path);
	if (ret) {
		free(ret);
		return 1;
	}
	return 0;
}

#if ENABLE_FEATURE_PREFER_APPLETS
/* just like the real execvp, but try to launch an applet named 'file' first
 */
int FAST_FUNC bb_execvp(const char *file, char *const argv[])
{
	return execvp(find_applet_by_name(file) >= 0 ? bb_busybox_exec_path : file,
					argv);
}
#endif
