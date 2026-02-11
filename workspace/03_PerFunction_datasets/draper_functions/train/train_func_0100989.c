unify(Interval &that)
{
   assert(this != &that);
   for (Range *next, *r = that.head; r; r = next) {
      next = r->next;
      this->extend(r->bgn, r->end);
      delete r;
   }
   that.head = NULL;
}
