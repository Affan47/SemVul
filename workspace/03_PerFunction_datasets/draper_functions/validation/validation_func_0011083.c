stabilizerSize(IntegerVector const &v, int i)const
		{
		  int ret=0;
		  if(i==v.size())return 1;
                  for(Map::const_iterator j=m.begin();j!=m.end();j++)
                    {
                      if(v[i]==v[j->first])
                        ret+=j->second.stabilizerSize(v,i+1);
                    }
                  return ret;
		}
