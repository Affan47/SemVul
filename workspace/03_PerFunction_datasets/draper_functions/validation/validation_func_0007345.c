edgecalc_f1(int px1, int py1)
{
   using namespace sa_edgecalc_names;

   int      ii, px2, py2, mindist;
   uint     dist2, mindist2;
   int      epx, epy, pxm, pym, dx, dy, inc;
   double   slope;

   mindist = 9999;
   mindist2 = mindist * mindist;
   epx = epy = 0;

   for (ii = 0; ii < sa_Nedge; ii++)
   {
      px2 = sa_edgepx[ii];
      py2 = sa_edgepy[ii];
      dx = px2 - px1;
      dy = py2 - py1;
      dist2 = dx*dx + dy*dy;
      if (dist2 < mindist2) {
         mindist2 = dist2;
         epx = px2;
         mindist = sqrt(dist2);
         epy = py2;
      }
   }

   if (abs(epy - py1) > abs(epx - px1)) {
      slope = 1.0 * (epx - px1) / (epy - py1);
      if (epy > py1) inc = 1;
      else inc = -1;
      for (pym = py1; pym != epy; pym += inc) {
         pxm = px1 + slope * (pym - py1);
         ii = pym * Fww + pxm;
         if (sa_edgedist[ii]) break;
         dx = epx - pxm;
         dy = epy - pym;
         dist2 = sqrt(dx*dx + dy*dy) + 2;
         sa_edgedist[ii] = dist2;
         SB_done++;
      }
   }

   else {
      slope = 1.0 * (epy - py1) / (epx - px1);
      if (epx > px1) inc = 1;
      else inc = -1;
      for (pxm = px1; pxm != epx; pxm += inc) {
         pym = py1 + slope * (pxm - px1);
         ii = pym * Fww + pxm;
         if (sa_edgedist[ii]) break;
         dx = epx - pxm;
         dy = epy - pym;
         dist2 = sqrt(dx*dx + dy*dy) + 2;
         sa_edgedist[ii] = dist2;
         SB_done++;
      }
   }

   return;
}
