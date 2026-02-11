LoadGfxObjPalette(char *name)
{
    uint32_t palette[256 * 3 + 2];
    FILE *fh;
    uint32_t i;
    uint16_t temp, depth;

    if ((fh = fopen(name, "rb"))) {
        fread_u32(fh);
        fread_u16(fh);
        fread_u16(fh);

        temp = fread_u16(fh);
        depth = 1 << min(8, temp);

        for (i = 0; i < depth * 3; i++)
            palette[i + 1] = (uint32_t)fread_u8(fh) << 24;

        palette[0] = (uint32_t)depth << 16;
        palette[depth * 3 + 1] = 0;
        os_load_palette(palette);

        D(bug("Loaded %ld colors from gfx_t %s\n", depth, name));

        fclose(fh);
    }
}
