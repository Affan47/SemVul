obj_directly_in_room (sc_gameref_t game, sc_int object, sc_int room)
{
  sc_bool result;


  result = obj_directly_in_room_internal (game, object, room);

  if (obj_trace)
    {
      sc_trace ("Object: checking for object %ld directly in room %ld, %s\n",
                object, room, result ? "true" : "false");
    }

  return result;
}
