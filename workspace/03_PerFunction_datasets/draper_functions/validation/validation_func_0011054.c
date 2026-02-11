setEncoderGoalRel(double dist,
						      double deltaHeading,
						      bool backToGoal,
						      bool justDistance)
{
  ArPose goal;
  goal.setX(dist * ArMath::cos(deltaHeading));
  goal.setY(dist * ArMath::sin(deltaHeading));
  goal = myRobot->getToGlobalTransform().doTransform(goal);
  goal = myRobot->getEncoderTransform().doInvTransform(goal);
  setEncoderGoal(goal, backToGoal, justDistance);
}
