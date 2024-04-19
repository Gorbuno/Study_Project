#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
using namespace std;
 struct Rectangle{
     int length;
     int width;
     int flag;};
 struct Box{
     int length=0;
     int width = 1000;
     int count_subject=0;
     int bloks[100];};
void PrintFile(int flag, Rectangle * rec){
    int count=0;
    while (count < flag ){
        cout << "Rectangle: "<< count << " \tLength: "<<  rec[count].length;
        cout << " \tWidth: "<< rec[count].width<< endl;
        count++;}
    return;}
void Sort_Rec (Rectangle * rec, int flag){
    for (int i=0; i<flag; i++)
        for (int j=0; j<flag; j++)
            if (rec[i].length >= rec[j].length)
                swap(rec[i], rec[j]);}
void FFDH(Rectangle * rec, Box* box, int flag){
    int level=0;
    for (int i=0; i< flag; i++){
        int cnt =1;
        while (cnt){
            if (box[level].width >= rec[i].width){
                box[level].width -= rec[i].width;
                box [level].bloks[box[level].count_subject] = rec[i].width;
                box[level].count_subject++;
                if (rec[i].length > box[level].length)
                    box[level].length = rec [i].length;
                level=0;
                cnt=0;}
            else level++;}}
    int length=0;
    int k=1;
    for (int i=0; i<9;i++){
        length += box[i].length;
        cout << "Level: "<< k << " \t";
        cout << " Length: "<< box[i].length << " Width: ";
        for (int  j=0 ; j<box[i].count_subject; j++)
            cout << box[i].bloks[j]<< " ";
        cout << "\nResidual_width: "<< box[i].width<< "\n\n";
        k++;}
    cout << "\n----------------------------------------------------------------\n\nSummary length:" <<length<<" \n";}
int main(){
    FILE *file;
    int scan_error;
    int length, width, flag=133;
    Rectangle rectangle[flag];
    Box box1,box2 [10];
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
    }while (scan_error!=EOF || count < flag); //заполнение массива структур прямоугольника
    Sort_Rec(rectangle,flag);
    PrintFile(flag, rectangle);
    cout << "\n----------------------------------------------------------------\n\n\n";
    cout << "\t\t\tFirst-Fit Decreasing Height: \n\n\n";
    FFDH(rectangle,box2, flag);


    return 0;
}
