closeChain(void)
{
	if (curChain[0] == 0)
		return;

	if (closeActionTag[0])
		printf("%s\n", closeActionTag);
	closeActionTag[0] = 0;
	if (closeRuleTag[0])
		printf("%s\n", closeRuleTag);
	closeRuleTag[0] = 0;
	if (curChain[0])
		printf("    </chain>\n");
	curChain[0] = 0;

}
