#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge{
    int vertex_begin;
    int vertex_end;
    int weight;
};
void Print_Edges (int ** graph, int flag){
    cout << "Edges \t Weight \t Number"<<  endl;
    int count = 1;
    for (int v1=0; v1 < flag; v1++)
        for (int v2= v1 + 1; v2 < flag; v2++)
            if (graph[v1][v2] > 0)
                cout << v1 << " -- " << v2 << ": \t" << graph[v1][v2] << " \t" << count++<< endl;
    return;
}
int Generator_graph(int **graph, int flag){
    int Curr_time = time(NULL);
    if (Curr_time == -1 ){
        cout << "Error time!"<< endl;
        return 1;
    }
    srand (Curr_time);
    int count_edges=0;
    for (int v1=0; v1 < flag-1; v1++){
        for (int v2= v1 + 1; v2 < flag; v2++){
            if ((v1 != v2 && graph[v1][v2] == 0 ) && rand() % 100 < 34 ) {
                graph[v1][v2] = graph[v2][v1]= rand() % 50 + 1 ;//генерация веса ребра
                count_edges++;
            }
            else graph[v1][v2] = graph[v2][v1] = -1;
        }
    }
    int critical_weight=200;
    for (int v1=0; v1<flag-1; v1++){
        int v2=v1+1;
        if (graph[v1][v2] == -1){
            graph[v1][v2] = graph[v2][v1]= critical_weight; //создание доп ребер для гарантии графа
            count_edges++;
        }}
    //cout << "Number of undirected edges:  " << count_edges<< endl<< endl;
    return count_edges;
}
void Sort_Edges (int ** graph, Edge* edges, int count, int flag ) {
    int k = 0;
    for (int v1 = 0; v1 < flag; v1++)
        for (int v2 = v1 + 1; v2 < flag; v2++)
            if (graph[v1][v2] > 0) {
                edges[k].weight = graph[v1][v2];
                edges[k].vertex_begin = v1;
                edges[k++].vertex_end = v2;
            }
    for (int i = 0; i < flag; i++)
        for (int j = 0; j < flag; j++)
            if (edges[i].weight < edges[j].weight)
                swap(edges[i], edges[j]);
}
int Alg_Kruskal( Edge* edges, int flag){
    int* connectivity_component = new int[flag];// компонента связности
    for (int i=0; i<flag; i++) connectivity_component[i]=i;
    int currSumEdges=0;
    cout << "My Tree\nEdges \tWeight \tIndex\n";
    for (int i=0; i< flag; i++){
        Edge currEdge = edges [i];
        if (connectivity_component[currEdge.vertex_begin]!=connectivity_component[currEdge.vertex_end]){
            int past_connectivity_component = connectivity_component[currEdge.vertex_begin];
            int new_connectivity_component = connectivity_component[currEdge.vertex_end];
            cout << currEdge.vertex_begin<<"--"<< currEdge.vertex_end<<" \t"<< currEdge.weight<< " \t"<< i<<endl;
        for (int j=0;j<flag; j++){
            if (connectivity_component[j] == past_connectivity_component)
                connectivity_component[j]=new_connectivity_component;
        }  }
        currSumEdges+=currEdge.weight;
    }
    return currSumEdges;}

int main(){
    int n;
    cout << "Enter the number of verties:";
    cin >> n;
    int** graph = new int*[n];
    for(int v1 = 0; v1<n; v1++){
        graph[v1] = new int[n];
    }
    for (int v1=0; v1<n; v1++)
        for (int v2=0; v2<n; v2++)
            graph[v1][v2]=0;
    int count_edges;
    count_edges=Generator_graph(graph, n);
    Edge* currEdge = new Edge [count_edges];
    cout << endl<< endl;
    Print_Edges(graph,n);
    cout <<endl<< endl;
    Sort_Edges(graph, currEdge, count_edges, n);
    cout << endl << endl;

   int sum_weig = Alg_Kruskal(currEdge,n);
   cout << "Summary Weigth:"<<sum_weig<<endl<< endl<< endl;

    delete(graph);
    delete (currEdge);
    return 0;
}
