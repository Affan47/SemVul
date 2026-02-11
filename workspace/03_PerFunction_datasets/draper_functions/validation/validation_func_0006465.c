redraw(void)
{
  if (owner()->mapped()==MSTrue)
   {
     int ht=highlightThickness();
     XFillRectangle(display(),window(),
                    (armed()==MSTrue)?selectGC():backgroundShadowGC(),
                    ht,ht,width()-(ht<<1),height()-(ht<<1));

     if(highlighted()==MSTrue) drawHighlight();
     else undrawHighlight();
     if (pixmap()==0) drawLabel();
     else drawPixmap();

     (armed()==MSTrue)?drawSunken():drawRaised();
   }
}
