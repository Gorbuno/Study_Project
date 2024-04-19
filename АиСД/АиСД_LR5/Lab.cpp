#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>

using namespace std;
struct Edge{
    int vertex_begin;
    int vertex_end;
    int weight;};
struct Way{
    int vertex;
    int weigth_edge;};
void Print_Edges (int ** graph, int flag){
    cout << "Edges \t Weight \t Number"<<  endl;
    int count = 1;
    for (int v1=0; v1 < flag; v1++)
        for (int v2= v1 + 1; v2 < flag; v2++)
            if (graph[v1][v2] > 0)
                cout << v1 << " -- " << v2 << ": \t" << graph[v1][v2] << " \t" << count++<< endl;
    return;}
int Generator_graph(int **graph, int flag){
    int Curr_time = time(NULL);
    if (Curr_time == -1 ){
        cout << "Error time!"<< endl;
        return 1;
    }
    srand (Curr_time);
    int count_edges=0;
    for (int v1=0; v1 < flag-1; v1++)
        for (int v2= v1 + 1; v2 < flag; v2++){
            if ((v1 != v2 && graph[v1][v2] == 0 ) && rand() % 100 < 34 ) {
                graph[v1][v2] = graph[v2][v1]= rand() % 50 + 1 ;
            }
            else graph[v1][v2] = graph[v2][v1] = -1;}
    int critical_weight=200;
    for (int v1=0; v1<flag-1; v1++){
        int v2=v1+1;
        if (graph[v1][v2] == -1){
            graph[v1][v2] = graph[v2][v1]= critical_weight;
            count_edges++;}}
    return count_edges;
}
void Add_Struct_Edges (int ** graph, Edge* edges, int count, int flag ) {
    int k = 0;
    for (int v1 = 0; v1 < flag; v1++)
        for (int v2 = v1 + 1; v2 < flag; v2++)
            if (graph[v1][v2] > 0) {
                edges[k].weight = graph[v1][v2];
                edges[k].vertex_begin = v1;
                edges[k++].vertex_end = v2;
            }}
void Way_graph(Way** way, int ver_i,int flag){
    int edge;
    printf("Way: \t%d", ver_i);
    for (int i=flag -1; i> 0 ; i--)
        if (way[ver_i][i].vertex!=-1)
            cout << "("<<way[ver_i][i].weigth_edge<<") "<< way[ver_i][i].vertex;
    cout << endl;
    return;}
void Alg_Ford_Bellman(int * start_vertex, int ed, Edge * graph, Way ** MyWay, int flag){
    int min_way [flag][flag];
    for (int v1=0;v1<flag;v1++)
        for (int v2=0; v2<flag;v2++){
            if (*start_vertex == v1) min_way[v1][v2] = 0;
            else min_way[v1][v2] =  5000;
            if (v2!=0) MyWay[v1][v2].vertex = -1;
            else MyWay[v1][0].vertex =v1;
            MyWay[v1][v2].weigth_edge = 0; }
    for (int v1=0;v1<flag;v1++) {
        for (int v2 = 0; v2 < flag; v2++)
            min_way[v2][v1] = min_way[v2][v1 - 1];
        for (int v2 = 0; v2 < flag; v2++)
            for (int k = 0; k < ed; k++)
                if (graph[k].vertex_begin == v2 || graph[k].vertex_end == v2) {
                    if (min_way[graph[k].vertex_end][v1] > min_way[graph[k].vertex_begin][v1 - 1] + graph[k].weight) {
                        min_way[graph[k].vertex_end][v1] = min_way[graph[k].vertex_begin][v1 - 1] + graph[k].weight;
                        MyWay[graph[k].vertex_end][v1].weigth_edge = graph[k].weight;
                        MyWay[graph[k].vertex_end][v1].vertex = graph[k].vertex_begin;}
                    else if (min_way[graph[k].vertex_begin][v1] > min_way[graph[k].vertex_end][v1 - 1] + graph[k].weight){
                        min_way[graph[k].vertex_begin][v1] = min_way[graph[k].vertex_end][v1 - 1] + graph[k].weight;
                        MyWay[graph[k].vertex_begin][v1].weigth_edge = graph[k].weight;
                        MyWay[graph[k].vertex_begin][v1].vertex = graph[k].vertex_end;}}}
    for (int i=0; i<flag;i++){
        for (int j=0; j<flag; j++)
            if (min_way[i][j] >0 )
                cout << min_way[i][j]<<", ";
        cout << endl;}
    cout << endl;
    return;}
int main(){
    int n;
    cout << "Enter the number of verties:";
    cin >> n;
    int** graph = new int*[n];
    for(int v1 = 0; v1<n; v1++){
        graph[v1] = new int[n]; }
    for (int v1=0; v1<n; v1++)
        for (int v2=0; v2<n; v2++)
            graph[v1][v2]=0;
    int count_edges;
    count_edges=Generator_graph(graph, n);
    Edge* currEdge = new Edge [count_edges];
    Print_Edges(graph,n);
    Add_Struct_Edges(graph, currEdge, count_edges, n);
    int start_vertex;
    cout <<"Enter the start vertex:";
    cin >> start_vertex;
    Way ** MyWay = new Way * [n];
    for(int i = 0; i<n; i++)
        MyWay[i] = new Way [n];
    Alg_Ford_Bellman(&start_vertex, count_edges, currEdge, MyWay, n);
    for (int i=0; i<n;i++)
        if (i!=start_vertex)
            Way_graph(MyWay, i, n);
    delete(graph);
    delete (currEdge);
    delete (MyWay);
    return 0;}
