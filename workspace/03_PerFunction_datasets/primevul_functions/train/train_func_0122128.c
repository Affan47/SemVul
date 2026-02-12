stbi_inline static int stbi__bit_reverse(int v, int bits)
{
   STBI_ASSERT(bits <= 16);


   return stbi__bitreverse16(v) >> (16-bits);
}
