left_rotate(void *item)
{
   void *y;
   void *x;

   x = item;
   y = right(x);
   set_right(x, left(y));
   if (left(y)) {
      set_parent(left(y), x);
   }
   set_parent(y, parent(x));

   if (!parent(x)) {
      head = y;
   } else if (x == left(parent(x))) {
      set_left(parent(x), y);
   } else {
      set_right(parent(x), y);
   }
   set_left(y, x);
   set_parent(x, y);
}
