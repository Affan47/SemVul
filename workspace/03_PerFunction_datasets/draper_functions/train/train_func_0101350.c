pdp_resample_halve(s16 *src_image, s16 *dst_image, s32 src_w, s32 src_h)
{

    int dst_x,dst_y;
    int src_x = 0;
    int src_y = 0;
    int dst_w = src_w >> 1;
    int dst_h = src_h >> 1;
    s32 tmp1,tmp2,tmp3,tmp4;


    for(dst_y = 0; dst_y < dst_h * dst_w; dst_y += dst_w){
	for (dst_x = 0; dst_x < dst_w; dst_x++){

	    tmp1 = (s32)src_image[src_y + src_x];
	    tmp2 = (s32)src_image[src_y + src_x + 1];
	    tmp3 = (s32)src_image[src_y + src_x + src_w];
	    tmp4 = (s32)src_image[src_y + src_x + src_w + 1];

	    tmp1 += tmp2;
	    tmp3 += tmp4;

	    src_x += 2;

	    dst_image[dst_x+dst_y] = (s16)((tmp1 + tmp3)>>2);
	}
	src_y += src_w << 1;
	src_x = 0;
    }
}
