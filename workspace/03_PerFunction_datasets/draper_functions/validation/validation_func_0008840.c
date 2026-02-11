__ecereNameSpace__ecere__gfx__drivers__BLIT_B888(struct __ecereNameSpace__ecere__com__Instance * src, struct __ecereNameSpace__ecere__com__Instance * dst, int dx, int dy, int sx, int sy, int w, int h)
{
int y;
unsigned int adddest = ((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)dst + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->stride, addsource = ((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)src + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->stride;
unsigned char * source = ((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)src + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->picture + sy * addsource + sx;
unsigned int * dest = (unsigned int *)((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)dst + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->picture + dy * adddest + dx;
unsigned int * palette = ((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)src + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->palette;
int x;

adddest -= w;
addsource -= w;
for(y = 0; y < h; y++)
{
for(x = 0; x < w; x++)
{
*dest = (palette[*source]);
source++;
dest++;
}
;
source += addsource;
dest += adddest;
}
}
