operator>>(std::istream& s, ScoreList& slist)
{
   char c;
   s >> c;
   s >> c;
   if (c == '(') {
      do {
	 Score score;
	 s.putback(c);
	 s >> score >> c;
	 slist._list.push_back(score);
      } while (c != ')');
   }
   return s;
}
