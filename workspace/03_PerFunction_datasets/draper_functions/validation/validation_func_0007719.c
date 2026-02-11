_momentum_test_reset(Gesture_Info *gesture)
{
   EINA_SAFETY_ON_NULL_RETURN(gesture);
   if (!gesture->data) return;

   memset(gesture->data, 0, sizeof(Momentum_Type));
}
