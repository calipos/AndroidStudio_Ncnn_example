

#include <iostream>
#include <fstream>
#include <string>

#include "benchmark.h"
#include "net.h"
#include "ncnnshell.h"

static std::vector<unsigned char> model_param;
static std::vector<unsigned char> model_bin;
static ncnn::Net net;

static const char* class_names[] = {"background", "aeroplane","bicycle","bird", "boat", "bottle",
                                    "bus", "car", "cat", "chair", "cow",
                                    "diningtable", "dog", "horse", "motorbike", "person",
                                    "pottedplant", "sheep", "sofa", "train", "tvmonitor"};



char* ncnnShell_DebugInterface(unsigned char* param, unsigned char* bin,char*report)
{
    ncnn::Net debugNet;
    std::string retString = "debugInitResult = ";
    // param
    {
        int ret1 = debugNet.load_param(param);
        retString += std::to_string(ret1);
    }
    // bin
    {
        int ret2 = debugNet.load_model(bin);
        retString += std::to_string(ret2);
    }
    retString += " blobNum=";
    retString += std::to_string(debugNet.howManyBlobs());
    debugNet.clear();
    strcpy(report,retString.c_str());
    return report;
}


char* ncnnShell_Init(unsigned char* param, unsigned char* bin,char*report) {
    std::string retString = "initResult = ";
    // param
    {
        int ret1 = net.load_param(param);
        retString += std::to_string(ret1);
    }
    // bin
    {
        int ret2 = net.load_model(bin);
        retString += std::to_string(ret2);
    }
    retString += " blobNum=";
    retString += std::to_string(net.howManyBlobs());
    strcpy(report,retString.c_str());
    return report;
}

char*ncnnShell_DetectSSD(int h, int w, void* bitmapData,char*report) {
    std::string ret = "";


    double time_min = DBL_MAX;
    double time_max = -DBL_MAX;
    double start = ncnn::get_current_time();

    ncnn::Mat in;

    in = ncnn::Mat::from_pixels((const unsigned char *) bitmapData, ncnn::Mat::PIXEL_RGBA2BGR,
                                w, h);

    const float mean_vals[3] = {127.5f, 127.5f, 127.5f};
    const float norm_vals[3] = {1.0/127.5,1.0/127.5,1.0/127.5};
    in.substract_mean_normalize(mean_vals, norm_vals);



    ncnn::Extractor ex = net.create_extractor();
    ex.set_light_mode(true);
    ex.set_num_threads(4);

    int extractInRet = ex.input(0, in);
    ncnn::Mat out;
    int extractOutRet = ex.extract(149, out);//if extractOutRet=-101, the detected targets num =0.

    double end = ncnn::get_current_time();
    double time = end - start;
    if(extractInRet!=0 || extractOutRet!=0)
    {
        ret += "(";
        ret += std::to_string(in.c);
        ret += ",";
        ret += std::to_string(in.h);
        ret += ",";
        ret += std::to_string(in.w);
        ret += "),";
        ret += std::to_string(extractInRet);
        ret += ",";
        ret += std::to_string(extractOutRet);
        ret += ",(";
        ret += std::to_string(out.c);
        ret += ",";
        ret += std::to_string(out.h);
        ret += ",";
        ret += std::to_string(out.w);
        ret += ") nothing detected.";
        strcpy(report,ret.c_str());
        return report;
    } else
    {
        for(int i=0;i<out.h;i++)
        {
            const float* values = out.row(i);
            int this_label = values[0];
            float this_prob = values[1];
            int this_x1 = values[2] * 300;
            int this_y1 = values[3] * 300;
            int this_x2 = values[4] * 300;
            int this_y2 = values[5] * 300;

            ret += "(label=";
            ret +=std::string(class_names[this_label]);
            ret += ",prob=";
            ret +=std::to_string(this_prob);
            ret += ",x1=";
            ret +=std::to_string(this_x1);
            ret += ",y1=";
            ret +=std::to_string(this_x1);
            ret += ",x2=";
            ret +=std::to_string(this_x2);
            ret += ",y2=";
            ret +=std::to_string(this_y2);
            ret += ")| ";
        }
        ret += "|   time cost=";
        ret +=std::to_string(time);

        strcpy(report,ret.c_str());
        return report;
    }
}

