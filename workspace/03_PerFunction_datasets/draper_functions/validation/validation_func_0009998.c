update_frame(void) {
    int row, col;
    uint32_t *input_fb=(uint32_t *)(xwd_file+xwd_size-(FRAME_H*FRAME_W*4));
    if((void*)input_fb<(void*)xwd_file) {
        fprintf(stderr, "Error: Illegal input file size.\n");
        exit(1);
    }
    msync(xwd_file, xwd_size, MS_SYNC);
    for(row=0;row<FRAME_H;row++) {
        for(col=0;col<FRAME_W;col++) {
            uint32_t p32=input_fb[row*FRAME_W+col];
            grey_fb[row][col]=
                ((p32>>0)&0xff)*0.3
               +((p32>>8)&0xff)*0.3
               +((p32>>16)&0xff)*0.3;
        }
    }
    ledwand_draw_image(&ledwand, (uint8_t *) grey_fb, sizeof grey_fb);
}
