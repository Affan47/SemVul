WritePDBOld(FILE *fp) const
{

  if (!fp) fp = stdout;


  int n = 0;
  for (int k = 0; k < ZResolution(); k++) {
    for (int j = 0; j < YResolution(); j++) {
      for (int i = 0; i < XResolution(); i++) {
	if (GridValue(i,j, k) > 0){
	  R3Point world_position = WorldPosition(i, j, k);
	  fprintf(fp, "%-6s%5d %-4s%c%3s %1s%4d%c   %8.3f%8.3f%8.3f%6.2f%6.2f          %2s\n", "HETATM", n, "H", ' ', "POC", "1", n, ' ', world_position.X(), world_position.Y(), world_position.Z(), GridValue(i, j, k), GridValue(i, j, k), "");
	  n++;


	}
      }
    }
  }


  return grid_size;
}
