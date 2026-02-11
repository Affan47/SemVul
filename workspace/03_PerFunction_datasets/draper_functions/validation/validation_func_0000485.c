init( const char* a, const char* b, const char* c )
{
  tdialogbox::init();
  windowstyle |= dlg_notitle;
  int wdth = gettextwdth ( a, schriften.arial8 ) ;
  if ( wdth > 280 )
     xsize = wdth + 20;
  else
     xsize = 300;

  ysize = 100;
  addbutton(b,10,60,xsize/2-5,90,0,1,1,true);
  addbutton(c,xsize/2+5,60,xsize-10,90,0,1,2,true);

  x1 = (640 - xsize) / 2;
  y1 = (480 - ysize) / 2;

  buildgraphics();
  activefontsettings.font = schriften.arial8;
  activefontsettings.justify = centertext;
  activefontsettings.length = xsize - 20;
  activefontsettings.background = 255;
  if ( actmap && actmap->actplayer >= 0 )
     activefontsettings.color = actmap->actplayer * 8 + 20;
  else
     activefontsettings.color = 20;
  mousevisible ( false );
  showtext2(a,x1 + 10,y1 + 15);
  mousevisible ( true );
  result = 0;
}
