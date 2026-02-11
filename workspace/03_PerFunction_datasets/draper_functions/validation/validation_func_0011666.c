FT_Stroker_Done( FT_Stroker  stroker )
  {
    if ( stroker )
    {
      FT_Memory  memory = stroker->library->memory;


      ft_stroke_border_done( &stroker->borders[0] );
      ft_stroke_border_done( &stroker->borders[1] );

      stroker->library = NULL;
      FT_FREE( stroker );
    }
  }
