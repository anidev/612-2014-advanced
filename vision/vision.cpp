#include "vision.h"

std::string TABLE_NAME="PCVision";

vision::vision()
    :table(NetworkTable::GetTable(TABLE_NAME)),
    vision_task("DriverVision Task", (FUNCPTR)&vision::vision_entry)
{
    
}

vision::~vision(){
    if(continuousRunning) {
        stopContinuous();
    }
}

bool vision::isContinuousRunning() {
    return continuousRunning;
}

void vision::startContinuous() {
    printf("starting continuous");
    continuousRunning=true;
    vision_task.Start((UINT32)this);
}

void vision::stopContinuous() {
    printf("stopping continuous");
    continuousRunning=false;
    vision_task.Stop();
}

int vision::vision_entry(void* obj){
    //vision* engine = (vision*)obj;
    while(true) {
        vision::processContinuous(/*engine->getHotGoal()*/);
    }
    return 0;
}

void vision::processContinuous() {
    
}

void getHotGoal(BinaryImage* image) {
    //Image* imaq = image -> GetImaqImage(); 
}

