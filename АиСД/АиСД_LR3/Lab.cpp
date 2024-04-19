#include <cstdio>
#include <iostream>
#include <list>
using namespace std;
int Index;
struct tree{
    float price;
    int article, fabricator;
    tree *left;
    tree *right;
    int articles [1000] = {0};
    int fabricators [1000] = {0};
    size_t way;
    size_t index_node=0;};
tree *create (float price, int article, int fabricator){
    tree *new_node = new tree;
    new_node -> price = price;
    new_node -> article = article;
    new_node -> fabricator = fabricator;
    new_node -> left = nullptr;
    new_node -> right = nullptr;
    new_node -> way = 0;
    return new_node;}
void add (tree * containingNode, tree * myNode){
    int i=0;
    if (containingNode->price == myNode -> price ){
        while (containingNode->articles [i] !=0)
            i++;
        containingNode -> articles [i] = myNode ->article;
        containingNode -> fabricators[i] = myNode -> fabricator;}
    if (myNode-> price > containingNode->price){
        if(containingNode->right!= nullptr){
            add(containingNode->right, myNode);
        }else{
            containingNode->right = myNode;
            containingNode -> right -> fabricators[i]= myNode -> fabricator;
            containingNode->right->articles[i] = myNode ->article;}
    }else if (containingNode -> price > myNode -> price){
        if(containingNode->left != nullptr){
            add(containingNode->left, myNode);}
        else{
            containingNode->left = myNode;
            containingNode -> left -> fabricators[i]= myNode -> fabricator;
            containingNode->left->articles[i] = myNode ->article;}}}
void *search (tree * myNode, float price){
    if ((myNode-> price == price))
    {   printf ("Article: %d     Fabricator: %d    Price: %f\n", (myNode->article),  (myNode->fabricator), (myNode->price));
        for (int i=1; myNode->articles [i] !=0 ; i++)
            printf ("Article: %d     Fabricator: %d    \n", (myNode->articles[i]), (myNode->fabricator)); }
    if (myNode-> left != nullptr)
    {return search (myNode -> left, price); }
    if (myNode -> right != nullptr)
    {return search (myNode-> right, price);}}
int preOrderTravers(tree * root, int * statistic) {
    if (root) {
        statistic[root->way]+=1;
        preOrderTravers(root->left, statistic);
        preOrderTravers(root->right,statistic); }}
int Way (tree * root){
    int level_tree = 0;
    if (root){
        int Way_left = Way(root->left);
        int Way_right = Way(root -> right);
        level_tree = max(Way_left+1,Way_right+1);}
    return level_tree;}
int count_way (tree * root, int Way){
    if (root == nullptr) return 0;
    else if (Way == 0) return 1;
    else return (count_way(root->left, Way-1) + count_way(root->right,Way-1));}
int Travel_Tree (tree * root){
    int i;
    if (root -> left !=0)
        Travel_Tree(root->left);
    root -> index_node = Index;
    Index++;
    if ((root->index_node >=0 && root-> index_node<=9) ||
            (root->index_node>=50000 && root->index_node<=50009)){
        cout << "\t\tPrice: "<< root->price<<endl;
        while (root->articles[i]!=0){
            cout << "Article: "<< root->articles[i] <<"\t Fabricator: "<< root->fabricators[i]<<endl;
            i++;}
        cout << endl;}
    if (root->right != 0){
        Travel_Tree(root->right);}
    return 0;}
int main() {
    FILE *file;
    int scan_error,i=0, count;
    tree * BinTree;
    tree * myNode;
    float price, user_price;
    int article,fabricator;
    int* statistic;
    file = fopen ("D:\\Users\\Leera\\CLionProjects\\LR2_AiCD\\ads_lab2.txt", "r");
    if ( file == nullptr){
        printf ("Error fopen!");
        return 1;}
    if (fscanf(file,"%d%f%d",&article, &price, &fabricator)==EOF){
        printf("error!");
        return 4;}
    BinTree = create(price,article,fabricator);
    myNode=BinTree;
    do{
        scan_error=fscanf(file, "%d%f%d",&article, &price, &fabricator);
        myNode = create(price, article, fabricator);
        add (BinTree, myNode);
        ++i;
    }while (scan_error!=EOF);
    Travel_Tree(BinTree);
    for (int i=0; i < Way (BinTree); ++i ) {
        cout << "Statistic: " << i << "\tWay: " << count_way(BinTree, i) << "\t\t\t";
        cout << "Statistic: " << ++i << "\tWay: " << count_way(BinTree, i) << "\n";}
    printf("\n\nPlease, input price:");
    scanf("%f", &user_price);
    search (BinTree, user_price);
    cout << endl;
    if (fclose(file)!=0){
        printf("Error fclose!");
        return 2;}
    delete (myNode);
    delete (statistic);
    delete (BinTree);
    return 0;}
