#include "vision.h"
#include "Timer.h"

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
    vision* engine = (vision*)obj;
    while(true) {
        vision::processContinuous(engine->getHotGoal());
    }
    return 0;
}

void vision::processContinuous(int goalIndic) {
    static Timer output;
    static bool outputStarted=false;
    if(!outputStarted) {
        output.Start();
        outputStarted=true;
    }
    if(output.Get()<0.5) {
        return;
    }
    output.Reset();
    if(goalIndic == 0) {
        printf("the hot goal is far\n");
        return;
    }
    printf("the hot goal is near");
}

int vision::getHotGoal() {
    if (table == NULL) {
        table=NetworkTable::GetTable(TABLE_NAME);
        if(table==NULL) {
            return 0;
        }
    }
    bool available=table->GetBoolean("1/Available",false);
    if(!available) {
        return 0;
    }
    int goalAvail = (int)table->GetNumber("1/HotGoalIndicator",0);
    return goalAvail;
}

