#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include <iostream>
#include <algorithm>
#include <cstring>
#include <unistd.h>
#include <fstream>

extern "C" int libmpeg2_main(int argc, char *argv[]);

struct Arguments {
    // char ac_ip_fname[64];
    // char ac_op_fname[64];
    // char ac_op_chksum_fname[64];
    char u4_file_save_flag;
    char u4_chksum_save_flag;
    // char e_output_chroma_format[20];
    short u4_max_frm_ts;
    short u4_num_cores;
    // char i4_degrade_pics;
    // char i4_degrade_type;
    char share_disp_buf;
    char deinterlace;
    char loopback;
    // char display;
    char full_screen;
    char fps;
    short max_wd;
    short max_ht;
    // short max_level;
    // char u4_piclen_flag;
    // char ac_piclen_fname[64];
};

int main(int argc, char ** argv) {

    if (argc != 2) {
        printf("Usage: %s <inputfile>", argv[0]);
        exit(1);
    }

    const char * libmpeg_argv[] = {
        argv[0],
        "-c", "/",
        "--input", argv[1]
    };

    libmpeg2_main(5, (char **) libmpeg_argv);

    return 0;
}