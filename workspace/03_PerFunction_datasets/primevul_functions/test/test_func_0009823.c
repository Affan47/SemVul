static gif_result gif_initialise_frame(gif_animation *gif)
{
        int frame;
        gif_frame *temp_buf;

        const unsigned char *gif_data, *gif_end;
        ssize_t gif_bytes;
        unsigned int flags = 0;
        unsigned int width, height, offset_x, offset_y;
        ssize_t block_size, colour_table_size;
        bool first_image = true;
        gif_result return_value;
        bool premature_eof = false;


        frame = gif->frame_count;


        gif_data = (const unsigned char *)(gif->gif_data + gif->buffer_position);
        gif_end = (const unsigned char *)(gif->gif_data + gif->buffer_size);
        gif_bytes = (gif_end - gif_data);


        if ((gif_bytes > 0) && (gif_data[0] == GIF_TRAILER)) {
                return GIF_OK;
        }


        if (gif_bytes < 6) {
                return GIF_INSUFFICIENT_DATA;
        }


        if (frame > 262143)
                return GIF_FRAME_DATA_ERROR;


        if ((int)gif->frame_holders <= frame) {

                temp_buf = (gif_frame *)realloc(gif->frames, (frame + 1) * sizeof(gif_frame));
                if (temp_buf == NULL) {
                        return GIF_INSUFFICIENT_MEMORY;
                }
                gif->frames = temp_buf;
                gif->frame_holders = frame + 1;
        }


        gif->frames[frame].frame_pointer = gif->buffer_position;
        gif->frames[frame].display = false;
        gif->frames[frame].virgin = true;
        gif->frames[frame].disposal_method = 0;
        gif->frames[frame].transparency = false;
        gif->frames[frame].frame_delay = 0;
        gif->frames[frame].redraw_required = false;


        if (gif->decoded_frame == frame) {
                gif->decoded_frame = GIF_INVALID_FRAME;
        }


        gif->buffer_position = gif_data - gif->gif_data;
        return_value = gif_initialise_frame_extensions(gif, frame);
        if (return_value != GIF_OK) {
                return return_value;
        }
        gif_data = (gif->gif_data + gif->buffer_position);
        gif_bytes = (gif_end - gif_data);


        if ((gif_bytes = (gif_end - gif_data)) < 1) {
                return GIF_INSUFFICIENT_FRAME_DATA;
        }

        if (gif_data[0] == GIF_TRAILER) {
                gif->buffer_position = (gif_data - gif->gif_data);
                gif->frame_count = frame + 1;
                return GIF_OK;
        }


        if (gif_data[0] != GIF_IMAGE_SEPARATOR) {
                return GIF_FRAME_DATA_ERROR;
        }


        if (gif_bytes < 10) {
                return GIF_INSUFFICIENT_FRAME_DATA;
        }
        offset_x = gif_data[1] | (gif_data[2] << 8);
        offset_y = gif_data[3] | (gif_data[4] << 8);
        width = gif_data[5] | (gif_data[6] << 8);
        height = gif_data[7] | (gif_data[8] << 8);


        if (!first_image) {
                if (gif->frames[frame].redraw_x > offset_x) {
                        gif->frames[frame].redraw_width += (gif->frames[frame].redraw_x - offset_x);
                        gif->frames[frame].redraw_x = offset_x;
                }

                if (gif->frames[frame].redraw_y > offset_y) {
                        gif->frames[frame].redraw_height += (gif->frames[frame].redraw_y - offset_y);
                        gif->frames[frame].redraw_y = offset_y;
                }

                if ((offset_x + width) > (gif->frames[frame].redraw_x + gif->frames[frame].redraw_width)) {
                        gif->frames[frame].redraw_width = (offset_x + width) - gif->frames[frame].redraw_x;
                }

                if ((offset_y + height) > (gif->frames[frame].redraw_y + gif->frames[frame].redraw_height)) {
                        gif->frames[frame].redraw_height = (offset_y + height) - gif->frames[frame].redraw_y;
                }
        } else {
                first_image = false;
                gif->frames[frame].redraw_x = offset_x;
                gif->frames[frame].redraw_y = offset_y;
                gif->frames[frame].redraw_width = width;
                gif->frames[frame].redraw_height = height;
        }


        gif->frames[frame].redraw_required = ((gif->frames[frame].disposal_method == GIF_FRAME_CLEAR) ||
                                                (gif->frames[frame].disposal_method == GIF_FRAME_RESTORE));


        if (gif_initialise_sprite(gif, (offset_x + width), (offset_y + height))) {
                return GIF_INSUFFICIENT_MEMORY;
        }


        flags = gif_data[9];
        colour_table_size = 2 << (flags & GIF_COLOUR_TABLE_SIZE_MASK);


        gif_data += 10;
        gif_bytes = (gif_end - gif_data);
        gif->frame_count_partial = frame + 1;


        if (flags & GIF_COLOUR_TABLE_MASK) {
                gif_data += 3 * colour_table_size;
                if ((gif_bytes = (gif_end - gif_data)) < 0) {
                        return GIF_INSUFFICIENT_FRAME_DATA;
                }
        }


        if (gif_bytes < 1) {
                return GIF_INSUFFICIENT_FRAME_DATA;
        }
        if (gif_data[0] > LZW_CODE_MAX) {
                return GIF_DATA_ERROR;
        }


        gif_data++;
        --gif_bytes;


        block_size = 0;
        while (block_size != 1) {
                if (gif_bytes < 1) return GIF_INSUFFICIENT_FRAME_DATA;
                block_size = gif_data[0] + 1;

                if ((ssize_t)(gif_bytes - block_size) < 0) {


                        if (gif_bytes >= 2) {
                                gif_bytes = 1;
                                ++gif_data;
                                premature_eof = true;
                                break;
                        } else {
                                return GIF_INSUFFICIENT_FRAME_DATA;
                        }
                } else {
                        gif_bytes -= block_size;
                        gif_data += block_size;
                }
        }


        gif->buffer_position = gif_data - gif->gif_data;
        gif->frame_count = frame + 1;
        gif->frames[frame].display = true;


        if (gif_bytes < 1) {
                return GIF_INSUFFICIENT_FRAME_DATA;
        } else {
                if (premature_eof || gif_data[0] == GIF_TRAILER) {
                        return GIF_OK;
                }
        }
        return GIF_WORKING;
}
