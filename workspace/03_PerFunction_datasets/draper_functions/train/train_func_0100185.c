arrowhead(unit x, unit y, unit xx, unit yy, double angle, colour filled)
{
uschar fill[12];
double s = sin(angle);
double c = cos(angle);

unit x1 = (unit)((double)yy*s*0.5);
unit y1 = (unit)((double)yy*c*0.5);
unit x2 = (unit)((double)xx*c);
unit y2 = (unit)((double)xx*s);

fprintf(out_file, "<path d=\"M %s %s\n", fixed(x - bbox[0]),
  fixed(-y + bbox[1]));

rline(x1, -y1);
rline(x2 - x1, y2 + y1);
rline(-x2 -x1, y1 - y2);
rline(x1, -y1);

if (samecolour(filled, unfilled)) Ustrcpy(fill, "\"none\"");
  else sprintf(CS fill, "\"#%02X%02X%02X\"",
    (filled.red   * 255)/1000,
    (filled.green * 255)/1000,
    (filled.blue  * 255)/1000);

fprintf(out_file,
  "\" fill=%s stroke=\"#000000\" stroke-width=\"0.4\"/>\n", fill);
}
