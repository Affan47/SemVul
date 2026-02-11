checkInterference(const RIG_Node *node, Graph::EdgeIterator& ei)
{
   const RIG_Node *intf = RIG_Node::get(ei);

   if (intf->reg < 0)
      return;
   const LValue *vA = node->getValue();
   const LValue *vB = intf->getValue();

   const uint8_t intfMask = ((1 << intf->colors) - 1) << (intf->reg & 7);

   if (vA->compound | vB->compound) {

      for (Value::DefCIterator D = vA->defs.begin(); D != vA->defs.end(); ++D) {
      for (Value::DefCIterator d = vB->defs.begin(); d != vB->defs.end(); ++d) {
         const LValue *vD = (*D)->get()->asLValue();
         const LValue *vd = (*d)->get()->asLValue();

         if (!vD->livei.overlaps(vd->livei)) {
            INFO_DBG(prog->dbgFlags, REG_ALLOC, "(%%%i) X (%%%i): no overlap\n",
                     vD->id, vd->id);
            continue;
         }

         uint8_t mask = vD->compound ? vD->compMask : ~0;
         if (vd->compound) {
            assert(vB->compound);
            mask &= vd->compMask & vB->compMask;
         } else {
            mask &= intfMask;
         }

         INFO_DBG(prog->dbgFlags, REG_ALLOC,
                  "(%%%i)%02x X (%%%i)%02x & %02x: $r%i.%02x\n",
                  vD->id,
                  vD->compound ? vD->compMask : 0xff,
                  vd->id,
                  vd->compound ? vd->compMask : intfMask,
                  vB->compMask, intf->reg & ~7, mask);
         if (mask)
            regs.occupyMask(node->f, intf->reg & ~7, mask);
      }
      }
   } else {
      INFO_DBG(prog->dbgFlags, REG_ALLOC,
               "(%%%i) X (%%%i): $r%i + %u\n",
               vA->id, vB->id, intf->reg, intf->colors);
      regs.occupy(node->f, intf->reg, intf->colors);
   }
}
