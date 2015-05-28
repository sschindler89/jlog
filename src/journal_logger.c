#include <stdio.h>
#include <sys/uio.h>
#include <systemd/sd-journal.h>

int main(int argc, char *argv[]){
	if (argc==1) {
		printf("usage: journal_logger [FIELD]\n"
			"whereas a FIELD has to be valid journal meta format,\n"
			"see http://www.freedesktop.org/software/systemd/man/systemd.journal-fields.html\n"
			"example: journal_logger MESSAGE=\"Hello World\" META1=entry1\n");
		return 1;
	}
	int rc;

	struct iovec iov[argc-1];
	int i;
	for (i = 1; i < argc; i++)
	{
		iov[i-1].iov_base = argv[i];
		iov[i-1].iov_len  = strlen(argv[i]);
	}

	rc = sd_journal_sendv(iov, argc-1);
	if (rc!=0){
		perror("sd_journal_send");
		printf("some error with the journal API occured\n");
	}
	return 0;
}