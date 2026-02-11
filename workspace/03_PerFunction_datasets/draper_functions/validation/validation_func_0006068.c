inCycle()
{
  if (!_caller || !_called) return 0;
  if (!_caller->cycle()) return 0;
  if (_caller == _caller->cycle()) return 0;
  if (_caller->cycle() != _called->cycle()) return 0;

  return _caller->cycle()->cycleNo();
}
