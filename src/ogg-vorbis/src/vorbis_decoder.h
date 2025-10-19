#include <stdlib.h>
#include "codec.h"

static const unsigned char INIT_PACKET = 0x01;
static const unsigned char COMMENT_PACKET = 0x03;
static const unsigned char SETUP_PACKET = 0x05;

static const unsigned char empty_comment_data[] = { COMMENT_PACKET, 0x76, 0x6f, 0x72, 0x62, 0x69, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };

typedef struct {
    vorbis_dsp_state dsp_state;
    vorbis_block block;
    vorbis_info info;
    vorbis_comment comment;
    ogg_packet current_packet;
    unsigned char received_setup_packets;

    /* input */
    unsigned char *input;
    int *input_len;

    /* output */
    float ***output;
    int *channels;
    long *sample_rate;
    int *samples_decoded;

    int *errors_len;
    char **errors;
    int errors_max;
} OggVorbisDecoder;

static void set_current_packet(
    OggVorbisDecoder *decoder,
    long first_page_flag
);

OggVorbisDecoder *create_decoder(
    /* input */
    unsigned char *input,
    int *input_len,
    /* output */
    float ***output,
    int *channels, // 1 - 255
    long *sample_rate,
    int *samples_decoded,
    char **errors,
    int *errors_len,
    int errors_max
);

void send_setup(
    OggVorbisDecoder *decoder,
    long first_page_flag
);

void init_dsp(OggVorbisDecoder *decoder);

void decode_packets(
    OggVorbisDecoder *decoder
);

void destroy_decoder(
    OggVorbisDecoder *decoder
);