DestroyFolderNodes()


{
    PCFFOLDER_NODE PrevNode;
    PCFFOLDER_NODE NextNode;

    NextNode = FolderListHead;
    while (NextNode != NULL)
    {
        PrevNode = NextNode->Next;
        DestroyDataNodes(NextNode);
        FreeMemory(NextNode);
        NextNode = PrevNode;
    }
    FolderListHead = NULL;
    FolderListTail = NULL;
}
