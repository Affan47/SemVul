dist_from_city(point p)
{
 int distance = 999;
 for (int i = 0; i < cities.size(); i++) {
  int dist = rl_dist(p.x, p.y, cities[i].x, cities[i].y);
  dist -= cities[i].s;
  if (dist < distance)
   distance = dist;
 }
 return distance;
}
