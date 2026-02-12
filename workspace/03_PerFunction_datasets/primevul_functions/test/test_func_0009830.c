static gif_result gif_skip_frame_extensions(gif_animation *gif)
{
        const unsigned char *gif_data, *gif_end;
        ssize_t gif_bytes;
        ssize_t block_size;


        gif_data = (const unsigned char *)(gif->gif_data + gif->buffer_position);
        gif_end = (const unsigned char *)(gif->gif_data + gif->buffer_size);
        gif_bytes = (gif_end - gif_data);


        while (gif_data < gif_end && gif_data[0] == GIF_EXTENSION_INTRODUCER) {
                ++gif_data;
                if (gif_data >= gif_end) {
                        return GIF_INSUFFICIENT_FRAME_DATA;
                }


                switch(gif_data[0]) {
                case GIF_EXTENSION_COMMENT:


                        ++gif_data;
                        break;

                default:


                        if (gif_data + 1 >= gif_end) {
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
