#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
using namespace std;
 struct Rectangle{
     int length;
     int width;
     int flag; };
 struct Box{
     int length=0;
     int width = 1000;
     int count_subject=0;
     int bloks[100]; };
void PrintFile(int flag, Rectangle * rec){
    int count=0;
    while (count < flag ){
        cout << "Rectangle: "<< count << " \tLength: "<<  rec[count].length;
        cout << " \tWidth: "<< rec[count].width<< endl;
        count++;
    }
    return;
}

void Sort_Rec (Rectangle * rec, int flag){
    for (int i=0; i<flag; i++)
        for (int j=0; j<flag; j++)
            if (rec[i].length >= rec[j].length)
                swap(rec[i], rec[j]);
}
void NFDH(Rectangle * rec, Box box, int flag){
    int level=0;
    for (int i=0; i<flag-1; i++){
        if (rec[i].length !=0){
            box.length += rec[i].length;
            level ++;
            int curr_width=0;
            cout << "Level: "<< level<< " Length: "<< rec[i].length<< " Width: ";
            for (int j=i; j<flag;j++){
                if ((box.width-(rec[j].width+curr_width)>=0)){
                    curr_width +=rec[j].width;
                    cout << rec[j].width<<",";
                    rec[j].length =0;
                    rec[j].width =0; }
                else break; }
        cout <<"\nResidual_width: " << box.width - curr_width <<endl<< endl;}}}
int main(){
    FILE *file;
    int scan_error;
    int length, width, flag=133;
    Rectangle rectangle[flag];
    Box box1;
    file = fopen ("C:\\Users\\Leera\\CLionProjects\\A_CD_LR6\\ads_lab6_rnd.txt", "r");
    if (file == nullptr){
        cout << "Error open file\n";
        return 1;
    }
    int count=0;
    do {
        scan_error = fscanf(file, "%d%d", &length,&width);
        rectangle[count].length = length;
        rectangle[count].width = width;
        count ++;
    }while (scan_error!=EOF || count < flag);
    Sort_Rec(rectangle,flag);
    PrintFile(flag, rectangle);
    cout << "\n----------------------------------------------------------------\n\n\n";
   cout << "\t\t\tNext-Fit Decreasing Height: \n\n\n";
    NFDH(rectangle,box1, flag);
    cout << "----------------------------------------------------------------\n\n Summary length: "<< box1.length<< endl;
    return 0;}

