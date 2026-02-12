static int stbi__parse_zlib_header(stbi__zbuf *a)
{
   int cmf   = stbi__zget8(a);
   int cm    = cmf & 15;

   int flg   = stbi__zget8(a);
   if (stbi__zeof(a)) return stbi__err("bad zlib header","Corrupt PNG");
   if ((cmf*256+flg) % 31 != 0) return stbi__err("bad zlib header","Corrupt PNG");
   if (flg & 32) return stbi__err("no preset dict","Corrupt PNG");
   if (cm != 8) return stbi__err("bad compression","Corrupt PNG");

   return 1;
}
