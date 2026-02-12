gif_initialise_frame_extensions(gif_animation *gif, const int frame)
{
        const unsigned char *gif_data, *gif_end;
        ssize_t gif_bytes;
        ssize_t block_size;


        gif_data = (const unsigned char *)(gif->gif_data + gif->buffer_position);
        gif_end = (const unsigned char *)(gif->gif_data + gif->buffer_size);


        while (gif_data < gif_end && gif_data[0] == GIF_EXTENSION_INTRODUCER) {
                ++gif_data;
                if ((gif_bytes = (gif_end - gif_data)) < 1) {
                        return GIF_INSUFFICIENT_FRAME_DATA;
                }


                switch (gif_data[0]) {
                case GIF_EXTENSION_GRAPHIC_CONTROL:


                        if (gif_bytes < 6) {
                                return GIF_INSUFFICIENT_FRAME_DATA;
                        }

                        gif->frames[frame].frame_delay = gif_data[3] | (gif_data[4] << 8);
                        if (gif_data[2] & GIF_TRANSPARENCY_MASK) {
                                gif->frames[frame].transparency = true;
                                gif->frames[frame].transparency_index = gif_data[5];
                        }
                        gif->frames[frame].disposal_method = ((gif_data[2] & GIF_DISPOSAL_MASK) >> 2);


                        if (gif->frames[frame].disposal_method == GIF_FRAME_QUIRKS_RESTORE) {
                                gif->frames[frame].disposal_method = GIF_FRAME_RESTORE;
                        }
                        gif_data += (2 + gif_data[1]);
                        break;

                case GIF_EXTENSION_APPLICATION:


                        if (gif_bytes < 17) {
                                return GIF_INSUFFICIENT_FRAME_DATA;
                        }
                        if ((gif_data[1] == 0x0b) &&
                            (strncmp((const char *) gif_data + 2,
                                     "NETSCAPE2.0", 11) == 0) &&
                            (gif_data[13] == 0x03) &&
                            (gif_data[14] == 0x01)) {
                                gif->loop_count = gif_data[15] | (gif_data[16] << 8);
                        }
                        gif_data += (2 + gif_data[1]);
                        break;

                case GIF_EXTENSION_COMMENT:


                        ++gif_data;
                        break;

                default:


                        if (gif_bytes < 2) {
                                return GIF_INSUFFICIENT_FRAME_DATA;
                        }
                        gif_data += (2 + gif_data[1]);
                }


                gif_bytes = (gif_end - gif_data);
                block_size = 0;
                while (gif_data < gif_end && gif_data[0] != GIF_BLOCK_TERMINATOR) {
                        block_size = gif_data[0] + 1;
                        if ((gif_bytes -= block_size) < 0) {
                                return GIF_INSUFFICIENT_FRAME_DATA;
                        }
                        gif_data += block_size;
                }
                ++gif_data;
        }


        gif->buffer_position = (gif_data - gif->gif_data);
        return GIF_OK;
}
