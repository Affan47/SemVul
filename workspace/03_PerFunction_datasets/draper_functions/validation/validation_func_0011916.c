eina_strbuf_ltrim(Eina_Strbuf *buf)
{
   unsigned char *c = buf->buf;

   while (buf->len > 0 && isspace(*c))
     {
        c++;
        buf->len--;
     }
   memmove(buf->buf, c, buf->len);
   ((unsigned char *)buf->buf)[buf->len] = '\0';
}
