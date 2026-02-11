_angle_get(Evas_Coord xx1,
           Evas_Coord yy1,
           Evas_Coord xx2,
           Evas_Coord yy2)
{
   double a, xx, yy, rt = (-1);

   xx = fabs(xx2 - xx1);
   yy = fabs(yy2 - yy1);

   if (((int)xx) && ((int)yy))
     {
        rt = a = RAD2DEG(atan(yy / xx));
        if (xx1 < xx2)
          {
             if (yy1 < yy2) rt = 360 - a;
             else rt = a;
          }
        else
          {
             if (yy1 < yy2) rt = 180 + a;
             else rt = 180 - a;
          }
     }

   if (rt < 0)
     {
        if (((int)xx))
          {
             if (xx2 < xx1) rt = 180;
             else rt = 0.0;
          }
        else
          {
            if (yy2 < yy1) rt = 90;
            else rt = 270;
          }
     }


   rt = 450 - rt;
   if (rt >= 360) rt -= 360;

   return rt;
}
