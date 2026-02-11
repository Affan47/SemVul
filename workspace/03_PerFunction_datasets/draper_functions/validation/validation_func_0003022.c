vga_8planes_copyarea(struct fb_info *info, const struct fb_copyarea *area)
{
        char oldindex = getindex();
        char oldmode = setmode(0x41);
        char oldop = setop(0);
        char oldsr = setsr(0xf);
        int height, line_ofs, x;
	u32 sx, dx, width;
	char __iomem *dest;
	char __iomem *src;

        height = area->height;

        sx = area->sx / 4;
        dx = area->dx / 4;
        width = area->width / 4;

        if (area->dy < area->sy || (area->dy == area->sy && dx < sx)) {
                line_ofs = info->fix.line_length - width;
                dest = info->screen_base + dx + area->dy * info->fix.line_length;
                src = info->screen_base + sx + area->sy * info->fix.line_length;
                while (height--) {
                        for (x = 0; x < width; x++) {
                                readb(src);
                                writeb(0, dest);
                                src++;
                                dest++;
                        }
                        src += line_ofs;
                        dest += line_ofs;
                }
        } else {
                line_ofs = info->fix.line_length - width;
                dest = info->screen_base + dx + width +
			(area->dy + height - 1) * info->fix.line_length;
                src = info->screen_base + sx + width +
			(area->sy + height - 1) * info->fix.line_length;
                while (height--) {
                        for (x = 0; x < width; x++) {
                                --src;
                                --dest;
                                readb(src);
                                writeb(0, dest);
                        }
                        src -= line_ofs;
                        dest -= line_ofs;
                }
        }

        setsr(oldsr);
        setop(oldop);
        setmode(oldmode);
        setindex(oldindex);
}
