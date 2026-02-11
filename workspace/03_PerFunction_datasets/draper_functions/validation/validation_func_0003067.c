calc_stream_moves(ushort stream, ushort pos, ushort len)
{
   int i;
   int moves = 0;
   int before=0, after=0;


   if (pos > len)
     {
      printf("duh, the position %d can't be greater than the length %d\n", pos, len);
      return 0;
     }


   for (i=0; i<pos; i++)
     {
      if (stream & 0x1)
	 before = 0;
      else
	 ++before;
      stream >>= 1;
     }

   ++i;
   stream >>= 1;

   for ( ; i<len; i++)
     {
      if (stream & 0x1)
	 break;
      else
	 ++after;
      stream >>= 1;
     }
   moves = before + after;


   return moves;
}
