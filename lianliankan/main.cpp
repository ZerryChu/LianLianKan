//
//  main.cpp
//  lianliankan
//
//  Created by Gun Li on 8/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#define ROW 6
#define LINE 9

typedef struct Point {
    int x;
    int y;
} MyPoint;

//判断是否能直线连接两点
bool Link2PointSteepInArray(int (*arr)[LINE], int row, int line, Point p1, Point p2)
{
    //首先对两点不在同一直线情况做处理
    if (p1.x != p2.x && p1.y != p2.y) {
        return false;
    }
    //首先判断能否直连
    bool CanLink = true;
    
    //a、首先检查Y坐标上的直连
    if (p1.x == p2.x) {
        int MaxY = (p1.y > p2.y) ? p1.y : p2.y;
        int MinY = (p1.y < p2.y) ? p1.y : p2.y;
        for (int i = MinY+1; i < MaxY; i ++) { //不检查p1,p2本身
            if (arr[p1.x][i] == 0) {
                continue ;
            } else {
                CanLink = false;
                printf("cannot link, while at Point(%d,%d)\n",p1.x,i);
                break;
            }
        }
        
        //如果能直连，就返回了
        if (CanLink) {
            return CanLink;
        }
    }
    
    //b、其次检查X坐标上的直连
    if (p1.y == p2.y) {
        int MaxX = (p1.x > p2.x) ? p1.x : p2.x;
        int MinX = (p1.x < p2.x) ? p1.x : p2.x;
        for (int i = MinX+1; i < MaxX; i ++) { //不检查p1,p2本身
            if (arr[i][p1.y] == 0) {
                continue ;
            } else {
                CanLink = false;
                printf("cannot link, while at Point(%d,%d)\n",i,p1.y);
                break;
            }
        }
    }
    
    return CanLink;
}

//一个转角相连，pList用来存储转角节点，包括p1，keyP，p2，方便做后续处理，返回为false，则p1，p2不能通过一个转角相连
bool Link2Point1CornerInArray(int (*arr)[LINE], int row, int line, Point p1, Point p2, Point *pList)
{
    //计算转焦点,p1、kp1、p2、kp2组成矩形的四个顶点
    Point kp1 = {p1.x, p2.y};
    Point kp2 = {p2.x, p1.y};
    
    if (Link2PointSteepInArray(arr, row, line, p1, kp1) && Link2PointSteepInArray(arr, row, line, p2, kp1) && arr[kp1.x][kp1.y] == 0) {
        //p1直连kp1，p2也能直连kp1，故，kp1是转角点， 返回{p1，kp1，p2}
        pList[0] = p1;
        pList[1] = kp1;
        pList[2] = p2;
        return true;
    }
    
    if (Link2PointSteepInArray(arr, row, line, p1, kp2) && Link2PointSteepInArray(arr, row, line, p2, kp2) && arr[kp2.x][kp2.y] == 0) {
        //p1直连kp1，p2也能直连kp1，故，kp2是转角点， 返回{p1，kp2，p2}
        pList[0] = p1;
        pList[1] = kp2;
        pList[2] = p2;
        return true;
    }
    return false;
}

bool Link2Point2CornerInArray(int (*arr)[LINE], int row, int line, Point p1, Point p2, Point *pList)
{
    //先Y坐标内部检查
    int MaxY = (p1.y > p2.y) ? p1.y : p2.y;
    int MinY = (p1.y < p2.y) ? p1.y : p2.y;
    for (int i = MinY+1; i < MaxY; i++) {
        //计算两个两个拐点kp1,kp2
        Point kp1 = {p1.x, i};
        Point kp2 = {p2.x, i};
        if (arr[kp1.x][kp1.y] != 0 || arr[kp2.x][kp2.y] != 0) {
            continue;
        }
        if (Link2PointSteepInArray(arr, row, line, p1, kp1) && 
            Link2PointSteepInArray(arr, row, line, kp1, kp2) && 
            Link2PointSteepInArray(arr, row, line, kp2, p2)) {
            //p1,p2可以经过kp1,kp2两个拐点相连
            printf("kp1(%d,%d), kp2(%d,%d)\n",kp1.x,kp1.y,kp2.x,kp2.y);
        }
    }
    
    //再X坐标内部检查
    int MaxX = (p1.x > p2.x) ? p1.x : p2.x;
    int MinX = (p1.x < p2.x) ? p1.x : p2.x;
    for (int i = MinX+1; i < MaxX; i++) {
        //计算两个两个拐点kp1,kp2
        Point kp1 = {i, p1.y};
        Point kp2 = {i, p2.y};
        if (arr[kp1.x][kp1.y] != 0 || arr[kp2.x][kp2.y] != 0) {
            continue;
        }
        if (Link2PointSteepInArray(arr, row, line, p1, kp1) && 
            Link2PointSteepInArray(arr, row, line, kp1, kp2) && 
            Link2PointSteepInArray(arr, row, line, kp2, p2)) {
            //p1,p2可以经过kp1,kp2两个拐点相连
            printf("kp1(%d,%d), kp2(%d,%d)\n",kp1.x,kp1.y,kp2.x,kp2.y);
        }
    }
    
    //再Y坐标外部检查
    for (int i = MaxY+1; i < LINE; i++) {
        Point kp1 = {p1.x,i};
        Point kp2 = {p2.x,i};
        if (arr[kp1.x][kp1.y] != 0 || arr[kp2.x][kp2.y] != 0) {
            continue;
        }
        
        if (Link2PointSteepInArray(arr, row, line, p1, kp1) && 
            Link2PointSteepInArray(arr, row, line, kp1, kp2) && 
            Link2PointSteepInArray(arr, row, line, kp2, p2)) {
            //p1,p2可以经过kp1,kp2两个拐点相连
            printf("kp1(%d,%d), kp2(%d,%d)\n",kp1.x,kp1.y,kp2.x,kp2.y);
        }
    }
    for (int i = MinY-1; i > 0; i--) {
        Point kp1 = {p1.x,i};
        Point kp2 = {p2.x,i};
        if (arr[kp1.x][kp1.y] != 0 || arr[kp2.x][kp2.y] != 0) {
            continue;
        }
        
        if (Link2PointSteepInArray(arr, row, line, p1, kp1) && 
            Link2PointSteepInArray(arr, row, line, kp1, kp2) && 
            Link2PointSteepInArray(arr, row, line, kp2, p2)) {
            //p1,p2可以经过kp1,kp2两个拐点相连
            printf("kp1(%d,%d), kp2(%d,%d)\n",kp1.x,kp1.y,kp2.x,kp2.y);
        }
    }
    
    //最后X坐标外部检查
    for (int i = MaxX+1; i < row; i++) {
        Point kp1 = {i, p1.y};
        Point kp2 = {i, p2.y};
        if (arr[kp1.x][kp1.y] != 0 || arr[kp2.x][kp2.y] != 0) {
            continue;
        }
        if (Link2PointSteepInArray(arr, row, line, p1, kp1) && 
            Link2PointSteepInArray(arr, row, line, kp1, kp2) && 
            Link2PointSteepInArray(arr, row, line, kp2, p2)) {
            //p1,p2可以经过kp1,kp2两个拐点相连
            printf("kp1(%d,%d), kp2(%d,%d)\n",kp1.x,kp1.y,kp2.x,kp2.y);
        }
    }
    for (int i = MinX-1; i > 0; i++) {
        Point kp1 = {i, p1.y};
        Point kp2 = {i, p2.y};
        if (arr[kp1.x][kp1.y] != 0 || arr[kp2.x][kp2.y] != 0) {
            continue;
        }
        if (Link2PointSteepInArray(arr, row, line, p1, kp1) && 
            Link2PointSteepInArray(arr, row, line, kp1, kp2) && 
            Link2PointSteepInArray(arr, row, line, kp2, p2)) {
            //p1,p2可以经过kp1,kp2两个拐点相连
            printf("kp1(%d,%d), kp2(%d,%d)\n",kp1.x,kp1.y,kp2.x,kp2.y);
        }
    }
    return false;
}

int main(int argc, const char * argv[])
{
    // insert code here...
    std::cout << "Hello, World!\n";
    
    int testArr[ROW][LINE] = {
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,1,1,0,0},
        {0,0,0,0,1,0,0,0,0},
        {0,0,0,0,1,0,1,0,0},
        {0,0,0,0,0,0,0,0,0}};
    
    
    MyPoint p1 = {1, 3};
    MyPoint p2 = {4, 6};
    
    //首先处理能否直连
    bool CanLink = Link2PointSteepInArray(testArr, ROW, LINE, p1, p2);
    
    //再次处理一个转角的情况下相连
    if (!CanLink) {
        printf("cannot link steep");
        Point *pList = (Point *)calloc(3, sizeof(Point));
        
        CanLink = Link2Point1CornerInArray(testArr, ROW, LINE, p1, p2, pList);
        if (CanLink) {
            for (int i = 0; i < 3; i ++) {
                Point tempP = pList[i];
                printf("%d,%d\n",tempP.x,tempP.y);
            }
            free(pList);
        } else {
            //最后处理两个转角相连的情况
            Point *pList2 = (Point *)calloc(4, sizeof(Point));
            Link2Point2CornerInArray(testArr, ROW, LINE, p1, p2, pList2);
        }
    }
    
    return 0;
}
