about(s_player *pPlayer)
{
  int i;
  char txt[3];
  pPlayer->score=0;
  printf("Joueur, entre ton nom en 3 lettres :\n");
  for(i=0;i<3;i++)
    {
      scanf("%c",&txt[i]);
      if(txt[i]=='\n')
	scanf("%c",&txt[i]);
      pPlayer->name[i]=toupper(txt[i]);
    }
  return ;
}
