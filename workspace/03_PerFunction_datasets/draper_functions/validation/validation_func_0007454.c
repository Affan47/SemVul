calcZeigVonBis(int y0, int & von, int & bis) {
  for (von = mEintraege.size();
       von>0 && y0+mEintraegeY[von-1]>=0;
       von--) {}
  for (bis = 0;
       bis<(int)mEintraege.size() && y0+mEintraegeY[bis+1]<=L_menu_hoehe;
       bis++) {}
}
