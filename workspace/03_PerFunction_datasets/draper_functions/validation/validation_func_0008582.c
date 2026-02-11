UpdateHighscores (void)
{
  int i, entry;
  Highscore_entry new_entry;
  char *tmp_name;
  BFont_Info *prev_font;
  struct tm *timeinfo;
  time_t tsec;
  float score;
  SDL_Rect dst;
  int h;

  score = RealScore;


  RealScore = 0.0;
  ShowScore = 0.0;


  if (score <= 0)
    return;

  Me.status = DEBRIEFING;


  entry = 0;
  while ( (entry < num_highscores) && (Highscores[entry]->score >= score) )
    entry ++;

  if (entry == num_highscores)
    return;


  free (Highscores[num_highscores-1]);


  for (i=num_highscores-1; i> entry; i--)
    Highscores[i] = Highscores[i-1];


  new_entry = MyMalloc (sizeof(highscore_entry));

  prev_font = GetCurrentFont();
  SetCurrentFont (Highscore_BFont);

  Assemble_Combat_Picture ( 0);
  MakeGridOnScreen (&User_Rect);
  Set_Rect (dst, UserCenter_x - Portrait_Rect.w/2, UserCenter_y - Portrait_Rect.h/2,
	    Portrait_Rect.w, Portrait_Rect.h);
  SDL_BlitSurface (pic999, NULL, ne_screen, &dst);
  h = FontHeight (Para_BFont);
  DisplayText ("Great Score !",  dst.x - h, dst.y - h, &User_Rect);
  DisplayText ("Enter your name: ",  dst.x - 5*h, dst.y + dst.h, &User_Rect);
  SDL_Flip (ne_screen);

  SDL_SetClipRect (ne_screen, NULL);
  tmp_name = GetString (MAX_NAME_LEN, 2);
  strcpy (new_entry->name, tmp_name);
  free (tmp_name);
  printf_SDL(ne_screen, -1, -1, "\n");

  tsec = time (NULL);
  timeinfo = gmtime (&tsec);
  sprintf (new_entry->date, "%02d/%02d/%02d", timeinfo->tm_mday, timeinfo->tm_mon +1,
	   timeinfo->tm_year-100);

  new_entry->score = score;
  Highscores[entry] = new_entry;

  SetCurrentFont (prev_font);

  return;

}
