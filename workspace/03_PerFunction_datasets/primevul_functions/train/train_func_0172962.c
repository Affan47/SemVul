void insert_breaks(char *str, int n, int size) {
   int i, j, i_last;

   i_last = 0;
   for (i = 0; i < (int) strlen(str); i++) {
      if (str[i] == '\r')
         i_last = i;


      if (i - i_last >= n && (int) strlen(str) + 3 < size) {


         while (i > i_last && str[i] != ' ')
            i--;
         if (str[i] == ' ')
            i++;


         for (j = strlen(str) + 2; j > i; j--)
            str[j] = str[j - 2];


         str[i++] = '\r';
         str[i++] = '\n';

         i_last = i;
      }
   }
}
