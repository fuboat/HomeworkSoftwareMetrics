#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "./include/mpeg2.h"

static void sample1 (FILE * mpgfile)
{
#define BUFFER_SIZE 4096
    uint8_t buffer[BUFFER_SIZE];
    mpeg2dec_t * decoder;
    const mpeg2_info_t * info;
    const mpeg2_sequence_t * sequence;
    mpeg2_state_t state;
    size_t size;
    int framenum = 0;

    decoder = mpeg2_init ();
    if (decoder == NULL) {
	fprintf (stderr, "Could not allocate a decoder object.\n");
	exit (1);
    }
    info = mpeg2_info (decoder);

    size = (size_t)-1;
    do {
	state = mpeg2_parse (decoder);
	sequence = info->sequence;
	switch (state) {
	case STATE_BUFFER:
	    size = fread (buffer, 1, BUFFER_SIZE, mpgfile);
	    mpeg2_buffer (decoder, buffer, buffer + size);
	    break;
	case STATE_SLICE:
	case STATE_END:
	case STATE_INVALID_END:
	default:
	    break;
	}
    } while (size);

    mpeg2_close (decoder);
}

int main (int argc, char ** argv)
{
    FILE * mpgfile;

    if (argc > 1) {
	mpgfile = fopen (argv[1], "rb");
	if (!mpgfile) {
	    fprintf (stderr, "Could not open file \"%s\".\n", argv[1]);
	    exit (1);
	}
    } else {
        printf("error, use ./* file_name instead.\n");
        return 1;
    }
    sample1 (mpgfile);

    return 0;
}