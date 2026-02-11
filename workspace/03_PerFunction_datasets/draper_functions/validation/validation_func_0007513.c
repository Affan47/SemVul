printTree(struct node* root, int height) {
    int i;

    if(root) {
        printTree(root->left, height + 1);
        for(i = 0; i < height; i++)
            printf("  ");
        printf("%d\n", root->value);
        printTree(root->right, height + 1);
    }
}
