ui_init(int argc,char **argv)
{
if(!use_ui)
  {
  non_ui_init();
  return;
  }

used_curses_ui=1;

initscr();
cbreak(); noecho();
curs_set(0);
keypad(stdscr,TRUE);
nodelay(stdscr,1);


if(COLS<80 || LINES<13)
  {
  ui_end();
  fprintf(stderr,"aylet: "
  		"sorry, need a terminal with at least 80 cols and 13 lines.\n");
  exit(1);
  }

frame_y=(LINES-13)/2;

clearscreen();
}
