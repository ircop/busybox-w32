/* vi: set sw=4 ts=4: */
#include "internal.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>

#ifndef BB_INIT
#undef BB_FEATURE_LINUXRC
#endif

static int been_there_done_that = 0;

/* It has been alledged that doing such things can
 * help reduce binary size when staticly linking,
 * of course with glibc, this is unlikely as long
 * as we use things like printf -- perhaps a printf
 * replacement may be in order 
 */
#if 0
void exit(int status) __attribute__ ((noreturn));
void exit(int status)
{
	_exit(status);
};
void abort(void) __attribute__ ((__noreturn__));
void abort(void)
{
	_exit(0);
};
int atexit(void (*__func) (void))
{
	_exit(0);
};
void *__libc_stack_end;
#endif

static const struct Applet applets[] = {

#ifdef BB_BASENAME				//usr/bin/basename
	{"basename", basename_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_BUSYBOX				//bin
	{"busybox", busybox_main, _BB_DIR_BIN},
#endif
#ifdef BB_BLOCK_DEVICE			//sbin
	{"block_device", block_device_main, _BB_DIR_SBIN},
#endif
#ifdef BB_CAT					//bin
	{"cat", cat_main, _BB_DIR_BIN},
#endif
#ifdef BB_CHMOD_CHOWN_CHGRP		//bin
	{"chmod", chmod_chown_chgrp_main, _BB_DIR_BIN},
#endif
#ifdef BB_CHMOD_CHOWN_CHGRP		//bin
	{"chown", chmod_chown_chgrp_main, _BB_DIR_BIN},
#endif
#ifdef BB_CHMOD_CHOWN_CHGRP		//bin
	{"chgrp", chmod_chown_chgrp_main, _BB_DIR_BIN},
#endif
#ifdef BB_CHROOT				//sbin
	{"chroot", chroot_main, _BB_DIR_SBIN},
#endif
#ifdef BB_CLEAR					//usr/bin
	{"clear", clear_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_CHVT					//usr/bin
	{"chvt", chvt_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_CP_MV					//bin
	{"cp", cp_mv_main, _BB_DIR_BIN},
#endif
#ifdef BB_CP_MV					//bin
	{"mv", cp_mv_main, _BB_DIR_BIN},
#endif
#ifdef BB_DATE					//bin
	{"date", date_main, _BB_DIR_BIN},
#endif
#ifdef BB_DD					//bin
	{"dd", dd_main, _BB_DIR_BIN},
#endif
#ifdef BB_DF					//bin
	{"df", df_main, _BB_DIR_BIN},
#endif
#ifdef BB_DIRNAME				//usr/bin
	{"dirname", dirname_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_DMESG					//bin
	{"dmesg", dmesg_main, _BB_DIR_BIN},
#endif
#ifdef BB_DU					//bin
	{"du", du_main, _BB_DIR_BIN},
#endif
#ifdef BB_DUTMP					//usr/sbin
	{"dutmp", dutmp_main, _BB_DIR_USR_SBIN},
#endif
#ifdef BB_ECHO					//bin
	{"echo", echo_main, _BB_DIR_BIN},
#endif
#ifdef BB_FBSET					//usr/sbin
	{"fbset", fbset_main, _BB_DIR_USR_SBIN},
#endif
#ifdef BB_FDFLUSH				//bin
	{"fdflush", fdflush_main, _BB_DIR_BIN},
#endif
#ifdef BB_FIND					//usr/bin
	{"find", find_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_FREE					//usr/bin
	{"free", free_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_FREERAMDISK			//sbin
	{"freeramdisk", freeramdisk_main, _BB_DIR_SBIN},
#endif
#ifdef BB_DEALLOCVT				//usr/bin
	{"deallocvt", deallocvt_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_FSCK_MINIX			//sbin
	{"fsck.minix", fsck_minix_main, _BB_DIR_SBIN},
#endif
#ifdef BB_MKFS_MINIX			//sbin
	{"mkfs.minix", mkfs_minix_main, _BB_DIR_SBIN},
#endif
#ifdef BB_GREP					//bin
	{"grep", grep_main, _BB_DIR_BIN},
#endif
#ifdef BB_HALT					//sbin
	{"halt", halt_main, _BB_DIR_SBIN},
#endif
#ifdef BB_HEAD					//bin
	{"head", head_main, _BB_DIR_BIN},
#endif
#ifdef BB_HOSTID				//usr/bin
	{"hostid", hostid_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_HOSTNAME				//bin
	{"hostname", hostname_main, _BB_DIR_BIN},
#endif
#ifdef BB_INIT					//sbin
	{"init", init_main, _BB_DIR_SBIN},
#endif
#ifdef BB_INSMOD				//sbin
	{"insmod", insmod_main, _BB_DIR_SBIN},
#endif
#ifdef BB_FEATURE_LINUXRC		//
	{"linuxrc", init_main, _BB_DIR_ROOT},
#endif
#ifdef BB_KILL					//bin
	{"kill", kill_main, _BB_DIR_BIN},
#endif
#ifdef BB_KILLALL				//usr/bin
	{"killall", kill_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_LENGTH				//usr/bin
	{"length", length_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_LN					//bin
	{"ln", ln_main, _BB_DIR_BIN},
#endif
#ifdef BB_LOADACM				//usr/bin
	{"loadacm", loadacm_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_LOADFONT				//usr/bin
	{"loadfont", loadfont_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_LOADKMAP				//sbin
	{"loadkmap", loadkmap_main, _BB_DIR_SBIN},
#endif
#ifdef BB_LS					//bin
	{"ls", ls_main, _BB_DIR_BIN},
#endif
#ifdef BB_LSMOD					//sbin
	{"lsmod", lsmod_main, _BB_DIR_SBIN},
#endif
#ifdef BB_MAKEDEVS				//sbin
	{"makedevs", makedevs_main, _BB_DIR_SBIN},
#endif
#ifdef BB_MATH					//usr/bin
	{"math", math_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_MKDIR					//bin
	{"mkdir", mkdir_main, _BB_DIR_BIN},
#endif
#ifdef BB_MKFIFO				//usr/bin
	{"mkfifo", mkfifo_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_MKNOD					//bin
	{"mknod", mknod_main, _BB_DIR_BIN},
#endif
#ifdef BB_MKSWAP				//sbin
	{"mkswap", mkswap_main, _BB_DIR_SBIN},
#endif
#ifdef BB_MNC					//usr/bin
	{"mnc", mnc_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_MORE					//bin
	{"more", more_main, _BB_DIR_BIN},
#endif
#ifdef BB_MOUNT					//bin
	{"mount", mount_main, _BB_DIR_BIN},
#endif
#ifdef BB_MT					//bin
	{"mt", mt_main, _BB_DIR_BIN},
#endif
#ifdef BB_NSLOOKUP				//usr/bin
	{"nslookup", nslookup_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_PING					//bin
	{"ping", ping_main, _BB_DIR_BIN},
#endif
#ifdef BB_POWEROFF				//sbin
	{"poweroff", poweroff_main, _BB_DIR_SBIN},
#endif
#ifdef BB_PRINTF				//usr/bin
	{"printf", printf_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_PS					//bin
	{"ps", ps_main, _BB_DIR_BIN},
#endif
#ifdef BB_PWD					//bin
	{"pwd", pwd_main, _BB_DIR_BIN},
#endif
#ifdef BB_REBOOT				//sbin
	{"reboot", reboot_main, _BB_DIR_SBIN},
#endif
#ifdef BB_RM					//bin
	{"rm", rm_main, _BB_DIR_BIN},
#endif
#ifdef BB_RMDIR					//bin
	{"rmdir", rmdir_main, _BB_DIR_BIN},
#endif
#ifdef BB_RMMOD					//sbin
	{"rmmod", rmmod_main, _BB_DIR_SBIN},
#endif
#ifdef BB_SED					//bin
	{"sed", sed_main, _BB_DIR_BIN},
#endif
#ifdef BB_SH					//bin
	{"sh", shell_main, _BB_DIR_BIN},
#endif
#ifdef BB_SFDISK				//sbin
	{"fdisk", sfdisk_main, _BB_DIR_SBIN},
#ifdef BB_SFDISK				//sbin
#endif
	{"sfdisk", sfdisk_main, _BB_DIR_SBIN},
#endif
#ifdef BB_SLEEP					//bin
	{"sleep", sleep_main, _BB_DIR_BIN},
#endif
#ifdef BB_SORT					//bin
	{"sort", sort_main, _BB_DIR_BIN},
#endif
#ifdef BB_SYNC					//bin
	{"sync", sync_main, _BB_DIR_BIN},
#endif
#ifdef BB_SYSLOGD				//sbin
	{"syslogd", syslogd_main, _BB_DIR_SBIN},
#endif
#ifdef BB_LOGGER				//usr/bin
	{"logger", logger_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_LOGNAME				//usr/bin
	{"logname", logname_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_SWAPONOFF				//sbin
	{"swapon", swap_on_off_main, _BB_DIR_SBIN},
#endif
#ifdef BB_SWAPONOFF				//sbin
	{"swapoff", swap_on_off_main, _BB_DIR_SBIN},
#endif
#ifdef BB_TAIL					//usr/bin
	{"tail", tail_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_TAR					//bin
	{"tar", tar_main, _BB_DIR_BIN},
#endif
#ifdef BB_TELNET				//usr/bin
	{"telnet", telnet_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_TEST					//usr/bin
	{"[", test_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_TEST					//usr/bin
	{"test", test_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_TEE					//bin
	{"tee", tee_main, _BB_DIR_BIN},
#endif
#ifdef BB_TOUCH					//usr/bin
	{"touch", touch_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_TR					//usr/bin
	{"tr", tr_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_TRUE_FALSE			//bin
	{"true", true_main, _BB_DIR_BIN},
#endif
#ifdef BB_TRUE_FALSE			//bin
	{"false", false_main, _BB_DIR_BIN},
#endif
#ifdef BB_TTY					//usr/bin
	{"tty", tty_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_UMOUNT				//bin
	{"umount", umount_main, _BB_DIR_BIN},
#endif
#ifdef BB_UNAME					//bin
	{"uname", uname_main, _BB_DIR_BIN},
#endif
#ifdef BB_UPTIME				//usr/bin
	{"uptime", uptime_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_UNIQ					//bin
	{"uniq", uniq_main, _BB_DIR_BIN},
#endif
#ifdef BB_UPDATE				//sbin
	{"update", update_main, _BB_DIR_SBIN},
#endif
#ifdef BB_WC					//usr/bin
	{"wc", wc_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_WHOAMI				//usr/bin
	{"whoami", whoami_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_YES					//usr/bin
	{"yes", yes_main, _BB_DIR_USR_BIN},
#endif
#ifdef BB_GUNZIP				//bin
	{"zcat", gunzip_main, _BB_DIR_BIN},
#endif
#ifdef BB_GUNZIP				//bin
	{"gunzip", gunzip_main, _BB_DIR_BIN},
#endif
#ifdef BB_GZIP					//bin
	{"gzip", gzip_main, _BB_DIR_BIN},
#endif
	{0}
};



int main(int argc, char **argv)
{
	char				*s;
	char				*name;
	const struct Applet	*a		= applets;

	for (s = name = argv[0]; *s != '\0';) {
		if (*s++ == '/')
			name = s;
	}

	*argv = name;

	while (a->name != 0) {
		if (strcmp(name, a->name) == 0) {
			int status;

			status = ((*(a->main)) (argc, argv));
			if (status < 0) {
				fprintf(stderr, "%s: %s\n", a->name, strerror(errno));
			}
			fprintf(stderr, "\n");
			exit(status);
		}
		a++;
	}
	exit(busybox_main(argc, argv));
}


int busybox_main(int argc, char **argv)
{
	int col = 0;

	argc--;
	argv++;

	if (been_there_done_that == 1 || argc < 1) {
		const struct Applet *a = applets;

		fprintf(stderr, "BusyBox v%s (%s) multi-call binary -- GPL2\n\n",
				BB_VER, BB_BT);
		fprintf(stderr, "Usage: busybox [function] [arguments]...\n");
		fprintf(stderr, "   or: [function] [arguments]...\n\n");
		fprintf(stderr,
				"\tMost people will create a link to busybox for each\n"
				"\tfunction name, and busybox will act like whatever you invoke it as.\n");
		fprintf(stderr, "\nCurrently defined functions:\n");

		while (a->name != 0) {
			col +=
				fprintf(stderr, "%s%s", ((col == 0) ? "\t" : ", "),
						(a++)->name);
			if (col > 60 && a->name != 0) {
				fprintf(stderr, ",\n");
				col = 0;
			}
		}
		fprintf(stderr, "\n\n");
		exit(-1);
	} else {
		/* If we've already been here once, exit now */
		been_there_done_that = 1;
		return (main(argc, argv));
	}
}

/*
Local Variables:
c-file-style: "linux"
c-basic-offset: 4
tab-width: 4
End:
*/
