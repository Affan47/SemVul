overlap(data_set *d, int sort[], int n, int it, csw *sw)
{ int i,j,flag,cross,crosstoo;
  long a,b,e,f,a2,b2,e2,f2,psmax;
  char sname[100],s[100];
  flag = 0;
  cross = 0;
  psmax = d->psmax;
  a = ts[it].start;
  b = ts[it].stop;
  if (b < a)
   { a2 = a - psmax;
     b2 = b;
     b += psmax;
     cross = 1; }
  j = -1;
  while (++j < n)
   { i = sort[j];
     if (i == it) continue;
     e = ts[i].start;
     f = ts[i].stop;
     crosstoo = 0;
     if (f < e)
      { e2 = e - psmax;
        f2 = f;
        f += psmax;
        crosstoo = 1; }
     if (a <= f)
      if (b >= e)
       goto OV;
     if (crosstoo)
      if (a <= f2)
       if (b >= e2)
        goto OV;
     if (cross)
      { if (a2 <= f)
         if (b2 >= e)
          goto OV;
        if (crosstoo)
         if (a2 <= f2)
          if (b2 >= e2)
           goto OV; }
     continue;
     OV:
     if (!flag) fputc('\n',sw->f);
     name(ts+i,sname,1,sw);
     location(s,ts+i,sw,sname);
     fprintf(sw->f,"Overlap with %d: %s\n", j+1,s);
     flag = 1; }
 if (flag) fputc('\n',sw->f); }
