GetTimeAsym()
{ float Sweep=Sum[1]-Sum[0]; return Sweep>0 ? 2*TimeAsym/Sweep : 0.0; }
