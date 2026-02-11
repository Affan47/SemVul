calc_gamma( float n, float d )
{
     int ret;

     ret = 255.0 * n / d + 0.5;
     if (ret > 255)
          ret = 255;
     else if (ret < 0)
          ret = 0;

     return ret;
}
