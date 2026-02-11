Cut(double t0, double t1, Track **dest){


   *dest = NULL;
   if (t1 <= t0)
      return false;
   double len = t1-t0;

   NoteTrack *newTrack = new NoteTrack(mDirManager);

   newTrack->Init(*this);

   mSeq->convert_to_seconds();
   newTrack->mSeq = mSeq->cut(t0 - GetOffset(), len, false);
   newTrack->SetOffset(GetOffset());


   *dest = newTrack;

   return true;
}
