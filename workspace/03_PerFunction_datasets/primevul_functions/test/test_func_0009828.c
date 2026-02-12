gif_initialise_sprite(gif_animation *gif,
                      unsigned int width,
                      unsigned int height)
{
        unsigned int max_width;
        unsigned int max_height;
        struct bitmap *buffer;


        if ((width <= gif->width) && (height <= gif->height)) {
                return GIF_OK;
        }


        max_width = (width > gif->width) ? width : gif->width;
        max_height = (height > gif->height) ? height : gif->height;


        assert(gif->bitmap_callbacks.bitmap_create);
        buffer = gif->bitmap_callbacks.bitmap_create(max_width, max_height);
        if (buffer == NULL) {
                return GIF_INSUFFICIENT_MEMORY;
        }

        assert(gif->bitmap_callbacks.bitmap_destroy);
        gif->bitmap_callbacks.bitmap_destroy(gif->frame_image);
        gif->frame_image = buffer;
        gif->width = max_width;
        gif->height = max_height;


        gif->decoded_frame = GIF_INVALID_FRAME;
        return GIF_OK;
}
