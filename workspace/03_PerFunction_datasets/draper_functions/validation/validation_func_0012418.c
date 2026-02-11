swapn8b(void *dst, const void *src, size_t nn)
{
        char *op = dst;
        const char *ip = src;


#  ifndef FLOAT_WORDS_BIGENDIAN
        while(nn > 1)
        {
                op[0] = ip[7];
                op[1] = ip[6];
                op[2] = ip[5];
                op[3] = ip[4];
                op[4] = ip[3];
                op[5] = ip[2];
                op[6] = ip[1];
                op[7] = ip[0];
                op[8] = ip[15];
                op[9] = ip[14];
                op[10] = ip[13];
                op[11] = ip[12];
                op[12] = ip[11];
                op[13] = ip[10];
                op[14] = ip[9];
                op[15] = ip[8];
                op += 16;
                ip += 16;
                nn -= 2;
        }
        while(nn-- != 0)
        {
                op[0] = ip[7];
                op[1] = ip[6];
                op[2] = ip[5];
                op[3] = ip[4];
                op[4] = ip[3];
                op[5] = ip[2];
                op[6] = ip[1];
                op[7] = ip[0];
                op += 8;
                ip += 8;
        }
#  else
        while(nn-- != 0)
        {
                op[0] = ip[3];
                op[1] = ip[2];
                op[2] = ip[1];
                op[3] = ip[0];
                op[4] = ip[7];
                op[5] = ip[6];
                op[6] = ip[5];
                op[7] = ip[4];
                op += 8;
                ip += 8;
        }
#  endif
}
