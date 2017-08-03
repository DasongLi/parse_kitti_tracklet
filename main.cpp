//
//  main.cpp
//  parse_tracklet
//
//  Created by pro on 2017/7/29.
//  Copyright © 2017年 pro. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cassert>
using namespace std;
ifstream infile;
ofstream outfile;
struct pose {
    double tx,ty,tz,rx,ry,rz;
    int state;
    int occlusion,occlusion_kf,truncation;
    int amt_occlusion,amt_occlusion_kf;
    int amt_border_l,amt_border_r,amt_border_kf;
    int number;
};
string read_oneline_process() {
    string res;
    getline(infile,res);
    int i,j,k,l;
    bool flag = false;
    string tmp = "";
    for (i=0;i<res.length();i++) {
        if (res[i] == '>') {
            flag = true; continue;
        }
        if (flag == true and res[i] == '<') {
            flag = false; continue;
        }
        if (flag == true) tmp = tmp + res[i];
    }
    return tmp;
}
struct one_item_pose {
    double tx,ty,tz,rx,ry,rz;
    int state;
    int occlusion,occlusion_kf,truncation;
    int amt_occlusion,amt_occlusion_kf;
    int amt_border_l,amt_border_r,amt_border_kf;
    string type;
    double height,width,length;
    one_item_pose(string t,double h,double w,double l,pose ele) {
        type = t; height = h; width = w; length = l;
        tx = ele.tx; ty = ele.ty; tz = ele.tz;
        rx = ele.rx; ry = ele.ry; rz = ele.rz;
        state = ele.state; occlusion = ele.occlusion; occlusion_kf = ele.occlusion_kf; truncation = ele.truncation;
        amt_occlusion = ele.amt_occlusion; amt_occlusion_kf = ele.amt_occlusion_kf;
        amt_border_l = ele.amt_border_l; amt_border_r = ele.amt_border_r; amt_border_kf = ele.amt_border_kf;
    }
};

class one_frame {
public:
    vector<one_item_pose> vect;
    one_frame() {
        vect.clear();
    }
};

class item {
public:
    string type;
    int begin_frame,count;
    double height,width,length;
    pose * pose_list;
    item() {
        type = "undefined";
        count = 0;
        begin_frame = 0; height = width = length = 0;
    }
    item(string tt,int b,int c,double h,double w,double l) {
        type = tt; begin_frame = b; count = c;
        height = h; width = w; length = l;
        pose_list = new pose [count];
    }
    void add_pose(int index,int begin) {
        string ss;
        getline(infile,ss);
        pose pose_ele;
        //cout<<index<<endl;
        for (int i=0;i<15;i++) {
            string res = read_oneline_process();
            //cout<<res<<endl;
            switch (i) {
                case 0:
                    pose_ele.tx = stod(res);
                    break;
                case 1:
                    pose_ele.ty = stod(res);
                    break;
                case 2:
                    pose_ele.tz = stod(res);
                    break;
                case 3:
                    pose_ele.rx = stod(res);
                    break;
                case 4:
                    pose_ele.ry = stod(res);
                    break;
                case 5:
                    pose_ele.rz = stod(res);
                    break;
                case 6:
                    pose_ele.state = stoi(res);
                    break;
                case 7:
                    pose_ele.occlusion = stoi(res);
                    break;
                case 8:
                    pose_ele.occlusion_kf = stoi(res);
                    break;
                case 9:
                    pose_ele.truncation = stoi(res);
                    break;
                case 10:
                    pose_ele.amt_occlusion = stoi(res);
                    break;
                case 11:
                    pose_ele.amt_occlusion_kf = stoi(res);
                    break;
                case 12:
                    pose_ele.amt_border_l = stoi(res);
                    break;
                case 13:
                    pose_ele.amt_border_r = stoi(res);
                    break;
                case 14:
                    pose_ele.amt_border_kf = stoi(res);
                    break;
                default:
                    break;
            }
        }
        pose_ele.number = begin + index;
        pose_list[index] = pose_ele;
        //cout<<index<<endl;
        getline(infile,ss);
    }
};



int main(int argc, const char * argv[]) {
    string file = "tracklet_labels1.xml";
    infile.open(file.data());   //将文件流对象与文件连接起来
    assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行
    
    int i,j,k,l;
    string ss,res;
    getline(infile,ss);getline(infile,ss);getline(infile,ss);getline(infile,ss);
    k = stoi(read_oneline_process());
    item* item_list;
    item_list = new item [k];
    getline(infile,ss);
    for (l=0; l<k; l++) {
        item item_ele;
        getline(infile,ss);
        for (i=0;i<5;i++) {
            string res = read_oneline_process();
            switch (i) {
                case 0:
                    item_ele.type = res;
                    break;
                case 1:
                    item_ele.height = stod(res);
                    break;
                case 2:
                    item_ele.width = stod(res);
                    break;
                case 3:
                    item_ele.length = stod(res);
                    break;
                case 4:
                    item_ele.begin_frame = stoi(res);
                    break;
                default:
                    break;
            }
        }
        getline(infile,ss);
        res = read_oneline_process();
        int count = stoi(res);
        getline(infile,ss);
        
        
        item_ele.pose_list = new pose [count];
        item_ele.count = count;
        for (i=0; i<count; i++) item_ele.add_pose(i,item_ele.begin_frame);
        getline(infile,ss);getline(infile,ss);getline(infile,ss);
        /*cout<<item_ele.type<<"  "<<item_ele.height<<"   "<<item_ele.width<<"    "<<item_ele.length<<"   "<<item_ele.begin_frame<<endl;
         cout<<count<<endl;
         for (i=0;i<count;i++) {
         cout<<"---------------------------------------------------------------"<<endl;
         cout<<item_ele.pose_list[i].tx<<" "<<item_ele.pose_list[i].ty<<" "<<item_ele.pose_list[i].tz<<endl;
         cout<<item_ele.pose_list[i].rx<<" "<<item_ele.pose_list[i].ry<<" "<<item_ele.pose_list[i].rz<<endl;
         cout<<"---------------------------------------------------------------"<<endl;
         }*/
        item_list[l] = item_ele;
    }
    getline(infile,ss);getline(infile,ss);
    //infile.close();
    one_frame * frame_list = new one_frame [500];
    for (i=0;i<k;i++) {
        for (j=0;j<item_list[i].count;j++) {
            one_item_pose one_item_pose(item_list[i].type,item_list[i].height,item_list[i].width,item_list[i].length,item_list[i].pose_list[j]);
            frame_list[item_list[i].pose_list[j].number].vect.push_back(one_item_pose);
        }
    }
    outfile.open("data2.txt");
    outfile<<"[";
    for (i=0; i<500; i++) {
        if (!frame_list[i].vect.empty()) {
            //cout<<"------------------------------- frame "<<i<<" --------------------------------"<<endl;
            outfile<<"[ "<<i<<" ";
            for (j=0;j<frame_list[i].vect.size();j++) {
                outfile<<"[";
                outfile<<frame_list[i].vect[j].type<<","<<frame_list[i].vect[j].height<<","<<frame_list[i].vect[j].width<<","<<frame_list[i].vect[j].length<<",";
                outfile<<frame_list[i].vect[j].tx<<","<<frame_list[i].vect[j].ty<<","<<frame_list[i].vect[j].tz;
                outfile<<"]"<<endl;
            }
            outfile<<"]"<<endl;
            //cout<<"---------------------------------------------------------------"<<endl;
        }
    }
    //cout<<"this is the end"<<endl;
    outfile<<"]";
    return 0;
}











