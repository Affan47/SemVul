force_home(char *call, char *route)
{
  vector <route_addr>::iterator it;

  if (routes.empty())
  {
    route_addr newaddr;
    newaddr.count = 1;
    newaddr.ttime = -1;
    strcpy(newaddr.call, call);
    strcpy(newaddr.route, route);
    routes.push_back(newaddr);
  }
  else
  {

    for (it = routes.begin(); it < routes.end(); it++)
      if (strcmp(it->call, call) == 0 && it->ttime == -1)
      {
        it->ttime = 0;
        it->count = 0;
        it->pcount = 0;
      }

    it = routes.begin();
    while (it < routes.end() &&
           (strcmp(it->call, call) < 0 ||
            (strcmp(it->call, call) == 0 && strcmp(it->route, route) < 0)))
              it++;

    if (it < routes.end() && strcmp(call, it->call) == 0 && strcmp(route, it->route) == 0)
    {
      it->ttime = -1;
    }
    else
    {
      route_addr newaddr;
      strcpy(newaddr.call, call);
      strcpy(newaddr.route, route);
      newaddr.count = 1;
      newaddr.ttime = -1;
      if (it < routes.end()) routes.insert(it, newaddr);
      else routes.push_back(newaddr);
    }
  }
}
