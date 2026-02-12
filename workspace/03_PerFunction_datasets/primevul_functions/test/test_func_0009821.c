gif_result gif_initialise(gif_animation *gif, size_t size, unsigned char *data)
{
        const unsigned char *gif_data;
        unsigned int index;
        gif_result return_value;


        gif->buffer_size = size;
        gif->gif_data = data;

        if (gif->lzw_ctx == NULL) {
                lzw_result res = lzw_context_create(
                                (struct lzw_ctx **)&gif->lzw_ctx);
                if (res != LZW_OK) {
                        return gif_error_from_lzw(res);
                }
        }


        if (gif->buffer_size < GIF_STANDARD_HEADER_SIZE) {
                return GIF_INSUFFICIENT_DATA;
        }


        gif_data = gif->gif_data + gif->buffer_position;


        if (gif->buffer_position == 0) {


                gif->frame_image = NULL;
                gif->frames = NULL;
                gif->local_colour_table = NULL;
                gif->global_colour_table = NULL;


                gif->frame_count = 0;
                gif->frame_count_partial = 0;
                gif->decoded_frame = GIF_INVALID_FRAME;


                if (strncmp((const char *) gif_data, "GIF", 3) != 0) {
                        return GIF_DATA_ERROR;
                }
                gif_data += 3;


                gif_data += 3;


                gif->width = gif_data[0] | (gif_data[1] << 8);
                gif->height = gif_data[2] | (gif_data[3] << 8);
                gif->global_colours = (gif_data[4] & GIF_COLOUR_TABLE_MASK);
                gif->colour_table_size = (2 << (gif_data[4] & GIF_COLOUR_TABLE_SIZE_MASK));
                gif->background_index = gif_data[5];
                gif->aspect_ratio = gif_data[6];
                gif->loop_count = 1;
                gif_data += 7;


                if (((gif->width == 640) && (gif->height == 480)) ||
                    ((gif->width == 640) && (gif->height == 512)) ||
                    ((gif->width == 800) && (gif->height == 600)) ||
                    ((gif->width == 1024) && (gif->height == 768)) ||
                    ((gif->width == 1280) && (gif->height == 1024)) ||
                    ((gif->width == 1600) && (gif->height == 1200)) ||
                    ((gif->width == 0) || (gif->height == 0)) ||
                    ((gif->width > 2048) || (gif->height > 2048))) {
                        gif->width = 1;
                        gif->height = 1;
                }


                gif->global_colour_table = calloc(GIF_MAX_COLOURS, sizeof(unsigned int));
                gif->local_colour_table = calloc(GIF_MAX_COLOURS, sizeof(unsigned int));
                if ((gif->global_colour_table == NULL) ||
                    (gif->local_colour_table == NULL)) {
                        gif_finalise(gif);
                        return GIF_INSUFFICIENT_MEMORY;
                }


                gif->global_colour_table[0] = GIF_PROCESS_COLOURS;


                if (gif->buffer_size == (GIF_STANDARD_HEADER_SIZE + 1)) {
                        if (gif_data[0] == GIF_TRAILER) {
                                return GIF_OK;
                        } else {
                                return GIF_INSUFFICIENT_DATA;
                        }
                }


                if ((gif->frames = (gif_frame *)malloc(sizeof(gif_frame))) == NULL) {
                        gif_finalise(gif);
                        return GIF_INSUFFICIENT_MEMORY;
                }
                gif->frame_holders = 1;


                assert(gif->bitmap_callbacks.bitmap_create);
                gif->frame_image = gif->bitmap_callbacks.bitmap_create(gif->width, gif->height);
                if (gif->frame_image == NULL) {
                        gif_finalise(gif);
                        return GIF_INSUFFICIENT_MEMORY;
                }


                gif->buffer_position = gif_data - gif->gif_data;
        }


        if (gif->global_colour_table[0] == GIF_PROCESS_COLOURS) {

                if (gif->global_colours) {
                        if (gif->buffer_size < (gif->colour_table_size * 3 + GIF_STANDARD_HEADER_SIZE)) {
                                return GIF_INSUFFICIENT_DATA;
                        }
                        for (index = 0; index < gif->colour_table_size; index++) {


                                unsigned char *entry = (unsigned char *) &gif->
                                                       global_colour_table[index];

                                entry[0] = gif_data[0];
                                entry[1] = gif_data[1];
                                entry[2] = gif_data[2];
                                entry[3] = 0xff;

                                gif_data += 3;
                        }
                        gif->buffer_position = (gif_data - gif->gif_data);
                } else {


                        unsigned int *entry = gif->global_colour_table;

                        entry[0] = 0x00000000;

                        ((unsigned char *) entry)[3] = 0xff;

                        entry[1] = 0xffffffff;
                }
        }


        while ((return_value = gif_initialise_frame(gif)) == GIF_WORKING);


        if ((return_value == GIF_INSUFFICIENT_MEMORY) ||
            (return_value == GIF_DATA_ERROR)) {
                return return_value;
        }


        if ((return_value == GIF_INSUFFICIENT_DATA) &&
            (gif->frame_count_partial > 0)) {
                return GIF_INSUFFICIENT_FRAME_DATA;
        }


        return return_value;
}
