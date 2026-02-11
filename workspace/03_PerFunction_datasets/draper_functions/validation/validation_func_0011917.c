hardestEmission(bool hard) {
  if( ( _hardme &&  _hardme->hasPOWHEGCorrection()) ||
      (_decayme && _decayme->hasPOWHEGCorrection())) {
    if(_hardme)
      _hardtree =  _hardme->generateHardest( currentTree() );
    else
      _hardtree = _decayme->generateHardest( currentTree() );
    if(!_hardtree) return;

    connectTrees(currentTree(),_hardtree,hard);
  }
  else {
    _hardtree = ShowerHandler::currentHandler()->generateCKKW(currentTree());
  }
}
