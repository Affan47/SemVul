precalc_tech_data()
{
  bool counted[A_LAST];

  advance_index_iterate(A_NONE, tech) {
    memset(counted, 0, sizeof(counted));
    advances[tech].num_reqs = precalc_tech_data_helper(tech, counted);
  } advance_index_iterate_end;

  advance_index_iterate(A_NONE, tech) {

    double reqs = advances[tech].num_reqs + 1;
    double cost = 0;
    const double base = game.info.base_tech_cost;

    switch (game.info.tech_cost_style) {
    case 0:
      break;
    case 1:
    case 2:
      cost = base * reqs * sqrt(reqs) / 2;
      break;
    case 3:
    case 4:
      cost = base * (reqs - 1) * (reqs - 1) / (1 + sqrt(sqrt(reqs))) - base/2;
      break;
    default:
      log_error("Invalid tech_cost_style %d", game.info.tech_cost_style);
      break;
    }

    techcoststyle1[tech] = MAX(cost, game.info.base_tech_cost);
  } advance_index_iterate_end;
}
