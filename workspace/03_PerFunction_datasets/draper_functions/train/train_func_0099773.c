shrink() {
   world.clear() ;
   vector<ndd> oseq = seq ;
   seq.clear() ;
   cache.clear() ;
   nodeseq = 0 ;
   curndd = recreate(oseq, curndd, neighborhood_size) ;
   cerr << "Shrunk from " << oseq.size() << " to " << seq.size() << endl ;
   shrinksize = (int)(seq.size() * 2) ;
}
