pcl3_end_page(FILE *out, pcl_FileData *data)
{

  fputc('\f', out);

  if (ferror(out)) {
    fputs(ERRPREF "Unidentified system error while writing the output file.\n",
      stderr);
    return -1;
  }

  return 0;
}
