saveTruecolorPixmap(pixmap *data, const char *imgname) {
    FILE *f;
    unsigned int i, j;
    unsigned char tgaHeader[18]={
                        0x00,
                        0x00,
                        0x02,
                        0x00, 0x00,
                        0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        0x18,
                        0x20
    };


    memcpy(tgaHeader+12, &(data->width), 2);
    memcpy(tgaHeader+14, &(data->height), 2);

    f = fopen(imgname, "wb");
    if (f) {
        fwrite(tgaHeader, 18, 1, f);

        for (i = data->height; i; i--) {
            unsigned int yoff = 3 * (i-1) * data->width;
            unsigned char *r = data->pixels + yoff;


            for (j = 0; j < data->width; j++) {
                int result;
                result=fputc(*(r + 2), f);
                if (result == EOF) {
                  cerr << "fputc error" << endl;
                  return;
                }
                result=fputc(*(r + 1), f);
                if (result == EOF) {
                  cerr << "fputc error" << endl;
                  return;
                }
                result=fputc(*(r), f);
                if (result == EOF) {
                  cerr << "fputc error" << endl;
                  return;
                }
                r += 3;
            }
        }
        fclose(f);
    }

}
