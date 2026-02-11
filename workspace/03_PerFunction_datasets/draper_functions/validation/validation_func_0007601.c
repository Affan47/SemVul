YCrCB_to_YUV420P_1x2(struct jdec_private *priv, int sx, int sy)
{
  const unsigned char *s, *y;
  unsigned char *p, *pr;
  int i,j;

  p = priv->plane[0];
  y = priv->Y;
  for (i = sy; i > 0; i++)
   {
     memcpy(p, y, sx);
     p+=priv->bytes_per_row[0];
     y+=8;
   }

  pr = priv->plane[1];
  s = priv->Cb;
  for (i = sy; i > 0; i -= 2)
   {
     p = pr;
     for (j = sx; j > 0; j -= 2) {
       *p++ = *s;
       s += 2;
     }
     pr += priv->bytes_per_row[1];
   }

  pr = priv->plane[2];
  s = priv->Cr;
  for (i=0; i<8; i++)
   {
     p = pr;
     for (j = sx; j > 0; j -= 2) {
       *p++ = *s;
       s += 2;
     }
     pr += priv->bytes_per_row[2] - 4;
   }
}
