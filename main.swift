//
//  main.swift
//  swift_parse_tracklet
//
//  Created by pro on 2017/8/3.
//  Copyright © 2017年 pro. All rights reserved.
//

import Foundation
struct pose {
    //double tx,ty,tz,rx,ry,rz
    //int start
    //int occlusion,occlusion_kf,truncation
    //int amt_occlusion,amt_occlusion_kf
    //int amt_border_l,amt_border_r,amt_border_kf
    var tx: Double
    var ty: Double
    var tz: Double
    var rx: Double
    var ry: Double
    var rz: Double
    
    var state: Int
    var occlusion: Int
    var occlusion_kf: Int
    var truncation: Int
    
    var amt_occlusion: Int
    var amt_occlusion_kf: Int
    var amt_border_l: Int
    var amt_border_r: Int
    var amt_border_kf: Int
    init(_ a: Double, _ b: Double, _ c: Double, _ d: Double, _ e: Double, _ f: Double,
         _ g: Int, _ h: Int, _ I: Int, _ j: Int,
         _ k: Int, _ l: Int, _ m: Int, _ n: Int, _ o: Int) {
        tx = a; ty = b; tz = c; rx = d; ry = e; rz = f;
        state = g; occlusion = h; occlusion_kf = I; truncation = j;
        amt_occlusion = k; amt_occlusion_kf = l; amt_border_l = m; amt_border_r = n; amt_border_kf = o;
    }
    init() {
        tx = 0; ty = 0; tz = 0; rx = 0; ry = 0; rz = 0;
        state = 0; occlusion = 0; occlusion_kf = 0; truncation = 0;
        amt_occlusion = 0; amt_occlusion_kf = 0; amt_border_l = 0; amt_border_r = 0; amt_border_kf = 0;
    }
}
enum Type {
    case Car
    case Van
    case Truck
    case Pedestrian
    case Cyclist
    case Tram
    case Misc
    case undefined
}
class item {
    var type: Type
    var begin_frame: Int
    var count: Int
    var height: Double
    var width: Double
    var length: Double
    var pose_list = [pose]()
    init() {
        type = .undefined
        begin_frame = 0
        count = 0
        height = 0
        width = 0
        length = 0
    }
    init(_ t: Type, _ b: Int, _ c: Int, _ h: Double, _ w: Double, _ l: Double) {
        type = t; begin_frame = b; count = c;
        height = h; width = w; length = l;
    }
    func add_poses() {
        readLine()
        var pose_ele = pose()
        print("232432")
        for i in 0 ..< 15 {
            var ele = getoneline_process()
            //print(ele)
            switch (i) {
            case 0:
                pose_ele.tx = Double(ele)!
                break
            case 1:
                pose_ele.ty = Double(ele)!
                break
            case 2:
                pose_ele.tz = Double(ele)!
                break
            case 3:
                pose_ele.rx = Double(ele)!
                break
            case 4:
                pose_ele.ry = Double(ele)!
                break
            case 5:
                pose_ele.rz = Double(ele)!
                break
            case 6:
                pose_ele.state = Int(ele)!
                break
            case 7:
                pose_ele.occlusion = Int(ele)!
                break
            case 8:
                pose_ele.occlusion_kf = Int(ele)!
                break
            case 9:
                pose_ele.truncation = Int(ele)!
                break
            case 10:
                pose_ele.amt_occlusion = Int(ele)!
                break
            case 11:
                pose_ele.amt_occlusion_kf = Int(ele)!
                break
            case 12:
                pose_ele.amt_border_l = Int(ele)!
                break
            case 13:
                pose_ele.amt_border_r = Int(ele)!
                break
            case 14:
                pose_ele.amt_border_kf = Int(ele)!
                break
            default:
                break
            }
            //print(ele)
        }
        pose_list.append(pose_ele)
        readLine()
    }
}
func getoneline_process() -> String {
    var res : String?
    res = readLine()
    var ele = ""
    var flag = false
    for element in res! {
        if element == ">" {
            flag = true
            continue
        }
        if flag == true && element == "<" {
            flag = false
            continue
        }
        if flag == true {
            ele = ele + String(element)
        }
    }
    return ele
}


//let res = readLine()
//print(res!)
/*readLine()
var one_ele = item()
for i in 0 ..< 5 {
    var ele = getoneline_process()
    //print(ele)
    if i == 0 {
        switch (ele) {
        case "Car":
            one_ele.type = .Car
            break
        default:
            break
        }
        continue
    }
    switch (i) {
    case 1:
        one_ele.height = Double(ele)!
        break
    case 2:
        one_ele.width = Double(ele)!
        break
    case 3:
        one_ele.length = Double(ele)!
        break
    case 4:
        one_ele.begin_frame = Int(ele)!
    default:
        break
    }
}
readLine()
var ele = getoneline_process()
readLine()
/*print(one_ele.type)
print(one_ele.height)
print(one_ele.width)
print(one_ele.length)
print(one_ele.begin_frame)*/
for _ in 0 ..< 14 {
    one_ele.add_poses()
}
/*for _ in 0 ..< 3 {
    readLine()
}*/

print(one_ele.type)
print(one_ele.height)
print(one_ele.width)
print(one_ele.length)
print(one_ele.begin_frame)
for i in 0 ..< one_ele.pose_list.count {
    print(one_ele.pose_list[i].tx, one_ele.pose_list[i].ty, one_ele.pose_list[i].tz)
}*/
var one_ele = item()
for _ in 0 ..< 14 {
    one_ele.add_poses()
}









