//
//  main.cpp
//  Box Stacking Problem DP
//
//  Created by Zijian Xie on 2016/11/9.
//  Copyright © 2016年 Jason Xie. All rights reserved.

//  You are given a set of n types of rectangular 3-D boxes, where the i^th box has height h(i), width w(i) and depth d(i) (all real numbers). You want to create a stack of boxes which is as tall as possible, but you can only stack a box on top of another box if the dimensions of the 2-D base of the lower box are each strictly larger than those of the 2-D base of the higher box. Of course, you can rotate a box so that any side functions as its base. It is also allowable to use multiple instances of the same type of box.
//  http://www.geeksforgeeks.org/dynamic-programming-set-21-box-stacking-problem/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class dimension{
    friend class boxstacking;
private:
    int length;
    int width;
    int height;
public:
    dimension(int length, int width, int height){
        this->length = length;
        this->width = width;
        this->height = height;
    }
    dimension(){}
    
    bool operator>(const dimension* d2){
        if(this->length * this->width >= d2->length * d2->width){
            return true;
        }else{
            return false;
        }
    }
    bool operator<(const dimension* d2){
        if(this->length * this->width < d2->length * d2->width){
            return true;
        }else{
            return false;
        }
    }
};

class boxstacking{
private:
    vector<dimension*> box;
public:
    boxstacking(vector<dimension*> box){this->box = box;}
    
    dimension* creatDimension(int side1, int side2, int height){
        dimension* d = new dimension();
        d->height = height;
        if(side1 >= side2){
            d->length = side1;
            d->width = side2;
        }else{
            d->length = side2;
            d->width = side1;
        }
        return d;
    }
    //Generate all 3 rotations of all boxes. The size of rotation array becomes 3 times the size of original array. For simplicity, we consider depth as always smaller than or equal to width.
    void ROTATION(vector<dimension*>& rot){
        for(int i = 0; i < box.size(); ++i){
            //分别以三种不同的高度去作为高度，来进行creat
            rot.push_back(creatDimension(box[i]->length, box[i]->width, box[i]->height));
            rot.push_back(creatDimension(box[i]->length, box[i]->height, box[i]->width));
            rot.push_back(creatDimension(box[i]->height, box[i]->width, box[i]->length));
        }
    };
    
    int maxHeight(){
        //rot.clear();
        vector<dimension*> rot;
        ROTATION(rot);
        sort(rot.begin(), rot.end(),[](dimension* a, dimension* b){
            return a > b;
        });//这里必须从大到小排列！！！因为你是想把i放在j上，所以相对而言，越大的就越放在底层。
        int n = (int)rot.size();
        
        vector<int> dp(n);
        vector<int> res(n);
        
        for(int i = 0; i < n; ++i){
            dp[i] = rot[i]->height;
            res[i] = i;
        }
        for(int i = 1; i < n; ++i){
            for(int j = 0; j < i; ++j){
                if((rot[i]->length < rot[j]->length) && (rot[i]->width < rot[j]->width)){
                    if(dp[i] < dp[j] + rot[i]->height){
                        dp[i] = dp[j] + rot[i]->height;
                        res[i] = j;
                    }
                }
            }
        }
        int max_res = -1, index = -1;
        for(int i = 0; i < n; ++i){
            if(max_res < dp[i]){
                index = i;
                max_res = dp[i];
            }
        }
        
        cout<< "The box stacking plan is: "<<endl;
        while(index != res[index]){
            cout<<"No."<<index<<" "<<"with length: "<<rot[index]->length <<", withd: "<<rot[index]->width<< ", height: "<<rot[index]->height<<endl;
            index = res[index];
        }
        
        cout<<"No."<<index<<" "<<"with length: "<<rot[index]->length <<", withd: "<<rot[index]->width<< ", height: "<<rot[index]->height<<". "<<endl;
        
        cout<<"The max height is: "<<max_res<<". "<<endl;
        return max_res;
    }
};

int main(int argc, const char * argv[]) {
    
    vector<dimension*> box = {new dimension(1,2,4), new dimension(3,2,5)};
    boxstacking* test = new boxstacking(box);
    test->maxHeight();
    return 0;
}
