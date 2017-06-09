//
// Created by thedoga on 17-6-2.
//
#include <iostream>
#include <fstream>
#include "tools.h"
using namespace std;



char ChessLogName[20] = "ChessLog.txt";



void read_table(char * table_path, int &x, int &y){
    int v;
    ifstream fin(table_path);
    for(int i=0; i<15; i++) {
        for (int j = 0; j < 15; j++) {
            fin >> v;
            if (v != mytable[i][j]){
                mytable[i][j] = v;
                x = i;
                y = j;
                return;
            }
        }
    }
    x = -1;
    y = -1;
}

