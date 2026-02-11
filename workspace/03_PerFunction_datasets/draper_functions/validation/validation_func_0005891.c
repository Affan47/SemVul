buildRIG(ArrayList& insns)
{
   std::list<RIG_Node *> values, active;

   for (std::deque<ValueDef>::iterator it = func->ins.begin();
        it != func->ins.end(); ++it)
      insertOrderedTail(values, getNode(it->get()->asLValue()));

   for (int i = 0; i < insns.getSize(); ++i) {
      Instruction *insn = reinterpret_cast<Instruction *>(insns.get(i));
      for (int d = 0; insn->defExists(d); ++d)
         if (insn->getDef(d)->rep() == insn->getDef(d))
            insertOrderedTail(values, getNode(insn->getDef(d)->asLValue()));
   }
   checkList(values);

   while (!values.empty()) {
      RIG_Node *cur = values.front();

      for (std::list<RIG_Node *>::iterator it = active.begin();
           it != active.end();) {
         RIG_Node *node = *it;

         if (node->livei.end() <= cur->livei.begin()) {
            it = active.erase(it);
         } else {
            if (node->f == cur->f && node->livei.overlaps(cur->livei))
               cur->addInterference(node);
            ++it;
         }
      }
      values.pop_front();
      active.push_back(cur);
   }
}
