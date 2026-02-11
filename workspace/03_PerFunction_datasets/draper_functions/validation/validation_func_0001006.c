print_blurb()
{
   FILE *fstp;
   char line[MAXLINE];

   if ((fstp=fopen("blksrch.stp", "r")) == NULL)
   {
      printf("\n========================================");
      printf("=======================================");
      printf("\nSearch results from the BLOCKS e-mail searcher.");
      printf("\nPlease report problems to jorja@sparky.fhcrc.org");
      printf(", include your query\nand this output.");
      printf(" To obtain help, send the word HELP on a single");
      printf("\nline to blocks@howard.fhcrc.org");
      printf("\n========================================");
      printf("=======================================");
      printf("\nCopyright (c) 1992 by the Fred Hutchinson Cancer Research Center");
      printf("\nIf you use BLOCKS in your research, please cite:");
      printf("\nSteven Henikoff and Jorja G. Henikoff,");
      printf(" Automated assembly of protein");
      printf("\nblocks for database searching, NAR 19:23 (1991), 6565-6572.");


      printf("\n========================================");
      printf("=======================================");
      printf("\nEach numbered result consists of one");
      printf(" or more blocks from a PROSITE group");
      printf("\nfound in the query sequence. One set");
      printf(" of the highest-scoring blocks that");
      printf("\nare in the correct order and separated");
      printf(" by distances comparable to the BLOCKS");
      printf("\ndatabase is selected for analysis.");
      printf(" If this set includes multiple blocks");
      printf("\nthe probability that the lower scoring");
      printf(" blocks support the highest scoring");
      printf("\nblock is reported. Maps of the database");
      printf(" blocks and query sequence are shown:");
      printf("\n  < indicates the sequence has been");
      printf(" truncated to fit the page");
      printf("\n  : indicates the minimum distance");
      printf(" between blocks in the database");
      printf("\n  . indicates the maximum distance");
      printf(" between blocks in the database");
      printf("\nThe maps are aligned on the highest");
      printf(" scoring block. The alignment of the");
      printf("\nquery sequence with the sequence");
      printf(" closest to it in the BLOCKS database");
      printf("\nis shown. Upper case in the query");
      printf(" sequence indicates at least one");
      printf("\noccurrence of the residue in that");
      printf(" column of the block.");
      printf("\n========================================");
      printf("=======================================");
      printf("\n");
   }
   else
   {
      while (!feof(fstp) && fgets(line, MAXLINE, fstp) != NULL)
         printf("%s", line);
      fclose(fstp);
   }

}
