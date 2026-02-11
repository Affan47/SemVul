gregoriotex_write_rare (FILE * f,
			gregorio_glyph *
			current_glyph,
			int i, char type,
			gregorio_note * current_note, char rare)
{

  char height = 0;
  char number = 0;


  gregoriotex_find_sign_number (current_glyph, i,
				type, TT_V_EPISEMUS, current_note,
				&number, &height, NULL);

  switch (rare)
    {
    case _ACCENTUS:
      fprintf (f, "\\greaccentus{%c}{%d}%%\n", current_note->pitch, number);
      break;
    case _ACCENTUS_REVERSUS:
      fprintf (f, "\\grereversedaccentus{%c}{%d}%%\n", current_note->pitch, number);
      break;
    case _CIRCULUS:
      fprintf (f, "\\grecirculus{%c}{%d}%%\n", current_note->pitch, number);
      break;
    case _SEMI_CIRCULUS:
      fprintf (f, "\\gresemicirculus{%c}{%d}%%\n", current_note->pitch, number);
      break;
    case _SEMI_CIRCULUS_REVERSUS:
      fprintf (f, "\\grereversedsemicirculus{%c}{%d}%%\n", current_note->pitch, number);
      break;

    case _ICTUS_A:
      switch (current_note->signs)
	{
	case _V_EPISEMUS:
	case _V_EPISEMUS_PUNCTUM_MORA:
	case _V_EPISEMUS_AUCTUM_DUPLEX:
	  fprintf (f, "\\grevepisemusictusa{%c}{%d}%%\n", height, number);
	  break;
	default:
	  fprintf (f, "\\greictusa{%d}%%\n", number);
	  break;
	}
      break;
    case _ICTUS_T:
      switch (current_note->signs)
	{
	case _V_EPISEMUS:
	case _V_EPISEMUS_PUNCTUM_MORA:
	case _V_EPISEMUS_AUCTUM_DUPLEX:
	  fprintf (f, "\\grevepisemusictust{%c}{%d}%%\n", height, number);
	  break;
	default:
	  fprintf (f, "\\greictust{%d}%%\n", number);
	  break;
	}
      break;
    default:
      break;
    }
}
