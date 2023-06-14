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
    std::string input;
    input.assign(std::istreambuf_iterator<char>(std::cin), std::istreambuf_iterator<char>());

    Arguments arguments;

    memset(&arguments, 0, sizeof(Arguments));
    memcpy(&arguments, input.data(), std::min(sizeof(Arguments), input.length()));

    std::string 
    // ac_ip_fname = std::string(arguments.ac_ip_fname, 64),
    u4_file_save_flag = std::to_string(arguments.u4_file_save_flag),
    u4_chksum_save_flag = std::to_string(arguments.u4_chksum_save_flag),
    u4_max_frm_ts = std::to_string(arguments.u4_max_frm_ts),
    u4_num_cores = std::to_string(arguments.u4_num_cores),
    // i4_degrade_pics = std::to_string(arguments.i4_degrade_pics),
    // i4_degrade_type = std::to_string(arguments.i4_degrade_type),
    share_disp_buf = std::to_string(arguments.share_disp_buf),
    deinterlace = std::to_string(arguments.deinterlace),
    loopback = std::to_string(arguments.loopback),
    full_screen = std::to_string(arguments.full_screen),
    fps = std::to_string(arguments.fps),
    max_wd = std::to_string(arguments.max_wd),
    max_ht = std::to_string(arguments.max_ht);
    // max_level = std::to_string(arguments.max_level);

    std::string libmpeg_inputfilecontent = input.substr(std::min(sizeof(Arguments), input.length()));
    std::string inputfilepathname = "/tmp/" + std::to_string(getppid());
    {
        std::ofstream of(inputfilepathname);
        of.write(libmpeg_inputfilecontent.data(), libmpeg_inputfilecontent.length());
    }

    const char * libmpeg_argv[] = {
        argv[0],
        "-c", "/",
        "--input", inputfilepathname.data(),
        "--save_output", u4_file_save_flag.data(),
        "--save_chksum", u4_chksum_save_flag.data(),
        "--num_frames", u4_max_frm_ts.data(),
        "--num_cores", u4_num_cores.data(),
        "--share_display_buf", share_disp_buf.data(),
        "--deinterlace", deinterlace.data(),
        "--loopback", loopback.data(),
        "--fullscreen", full_screen.data(),
        "--fps", fps.data(),
        "--max_wd", max_wd.data(),
        "--max_ht", max_ht.data()
    };

    libmpeg2_main(27, (char **) libmpeg_argv);

    return 0;
}