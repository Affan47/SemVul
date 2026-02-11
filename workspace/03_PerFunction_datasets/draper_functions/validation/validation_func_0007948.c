send_best_move() {

   double time, speed, cpu;
   sint64 node_nb;
   char move_string[256];
   char ponder_string[256];
   int move;
   mv_t * pv;


   time = SearchCurrent->time;
   speed = SearchCurrent->speed;
   cpu = SearchCurrent->cpu;
   node_nb = SearchCurrent->node_nb;

   send("info time %.0f nodes " S64_FORMAT " nps %.0f cpuload %.0f",time*1000.0,node_nb,speed,cpu*1000.0);

   trans_stats(Trans);


   move = SearchBest->move;
   pv = SearchBest->pv;

   move_to_string(move,move_string,256);

   if (pv[0] == move && move_is_ok(pv[1])) {
      move_to_string(pv[1],ponder_string,256);
      send("bestmove %s ponder %s",move_string,ponder_string);
   } else {
      send("bestmove %s",move_string);
   }
}
