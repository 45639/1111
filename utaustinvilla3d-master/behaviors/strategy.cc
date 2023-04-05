#include "naobehavior.h"
#include "../rvdraw/rvdraw.h"
#include "../GL/gl.h"
#include "../GL/glu.h"
#include "../GL/glut.h"

extern int agentBodyType;

/*
 * Real game beaming.
 * Filling params x y angle
 */
void NaoBehavior::beam( double& beamX, double& beamY, double& beamAngle ) {
    beamX = -HALF_FIELD_X + worldModel->getUNum();
    beamY = 0;
    beamAngle = 0;
}


SkillType NaoBehavior::selectSkill() {
    VecPosition Posball = worldModel->getBall();
    VecPosition Posgoal = VecPosition(-HALF_FIELD_X, 0, 0);
    //定义两个防守点的一些数据
    VecPosition midpoint = (Posball + Posgoal) / 2;  //中点
    double angle = atan2(Posgoal.getY() - Posball.getY(), Posgoal.getX() - Posball.getX());  //中垂线与y轴夹角
    double _x = 5 * sin(angle);
    double _y = 5 * cos(angle);
    //按点位优先级排序
    VecPosition target [6] = {
        Posball + VecPosition(-1, 0, 0),  //控球位
        VecPosition(Posgoal.getX(), Posball.getY(), 0),  //守门位
        Posball + VecPosition(9, 4, 0),  //接应点1
        Posball + VecPosition(9, -4, 0),  //接应点2
        midpoint + VecPosition(_x, _y, 0),  //防守点1
        midpoint - VecPosition(_x, _y, 0)  //防守点2
    };

    //绘制点位//由于链接不上OpenGL库，无法运行下面的绘制代码，所以用注释形式写出T—T
    /*
    for(int i = 0; i < 6; i++){
        glBegin(GL_POINTS);
        glVertex3f(target[i].getX(), target[i].getY(), target[i].getZ());
        glEnd();
    }
    */

    //若点位超出球场边界，就将点位移到球场内的合理对应位置中
    for(int i= 0; i < 6; i++){
        if(target[i].getX() > 15 || target[i].getX() < -15){
            if(target[i].getY() > 10)
                target[i] = (14.1, 10, 0);
            else
                target[i] = (14.1, target[i].getY(), 0);
            if(target[i].getY() < -10)
                target[i] = (14.1, -10, 0);
            else
                target[i] = (14.1, target[i].getY(), 0);
        }
        else if(target[i].getY() > 10 || target[i].getY() < -10)
            target[i] = (target[i].getX(), 10, 0);
    }
    

    vector<vector<double>>disTarget(6, vector<double>(6,0));
    vector<double>disBall(vector<double>(6,0));
    vector<double>disTeammate(vector<double>(6,0));
    int BotForTarget[6]={0};
    //计算球员花费
    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            int playerNum = WO_TEAMMATE1 + j;
            WorldObject *tem = worldModel->getWorldObject(playerNum);
            VecPosition temp;
            bool isfallen;
            if (worldModel->getUNum() == playerNum){
                temp = worldModel->getMyPosition();      //若是遍历到我,则获取我的位置
                isfallen = worldModel->isFallen();      //判断我是否摔倒
                disTeammate[j] = 10000;
            }
            else{
                tem = worldModel->getWorldObject( WO_TEAMMATE1 + j );
                temp = tem->pos;               //若是队友则获取队友的位置
                isfallen = worldModel->getFallenTeammate( WO_TEAMMATE1 + j );     //判断队友是否摔倒
                disTeammate[j]=me.getDistanceTo(temp);
            }

            //dis[i][j]保存第i个target到第j名球员的花费
            //判断球员位置是否有效
            if(temp.getX() < -15 || temp.getX() > 15 || temp.getY() < -10 || temp.getY() > 10){
                disTarget[i][j] = 10000;      //若球员位置无效则花费为最大
            }
            else{
                if(isfallen)     //若摔倒花费+1
                    disTarget[i][j] = disTarget[i][j]=target[i].getDistanceTo(temp) + 1;
                else
                    disTarget[i][j] = disTarget[i][j]=target[i].getDistanceTo(temp);
            }
            disBall[j]=Posball.getDistanceTo(temp);
        }
    }

    //控球位优先
    for(int i = 0; i < 6; i++){
        int minDisBot = min_element(disBall.begin(), disBall.end()) - disBall.begin();      //找到离球最近的球员
        BotForTarget[0] = minDisBot;     //离球最近的球员去控球
        disTarget[i][minDisBot]=10000;     //不再考虑该球员，就将他的距离全设成最⼤
    }
    
    for(int i = 1; i < 6; i++){
        int robot = min_element(disTarget[i].begin(), disTarget[i].end()) - disTarget[i].begin();    //找到距离最⼩的球员
        BotForTarget[i] = robot;     //保存其他球员编号
        for(int j = 1;j < 6; j++){ 
            disTarget[j][robot]=10000;      //不再考虑该球员，就将他的距离全设成最⼤
        }
    }
        
    
    for(int i=0;i<6;i++){
        if (worldModel->getUNum() == WO_TEAMMATE1 + BotForTarget[i]){
            if (i == 0){          //若我应跑去控球点
                if (me.getDistanceTo(target[0]) > 1)   //若离得较远就跑去控球点
                    return goToTarget(collisionAvoidance(true, false, false, 1,.5, target[0], true));
                else{             //若已到位就执⾏踢球
                    if (Posball.getDistanceTo(target[2]) > 1 && Posball.getDistanceTo(target[3]) > 1){      //若球不在接应点附近
                        if(me.getX() < -PENALTY_X && me.getY() < PENALTY_Y && me.getY() > -PENALTY_Y){      //若我在己方禁区内
                            int minTeammate = min_element(disTeammate.begin(), disTeammate.end()) - disTeammate.begin();
                            VecPosition temp = worldModel->getWorldObject(WO_TEAMMATE1 + minTeammate) -> pos;
                            kickBall(KICK_FORWARD, temp);    //踢向离我最近的队友
                        }
                        else{        //若我不在己方禁区内
                            if (me.getDistanceTo(target[2]) < me.getDistanceTo(target[3]))     //踢向离我较近的接应点
                                return kickBall(KICK_FORWARD, target[2]);
                            else
                                return kickBall(KICK_FORWARD, target[3]);
                        }
                    }
                    else{             //若球在接应点附近
                        VecPosition R_GOAL_1 (15, 1.05, 0);
                        VecPosition R_GOAL_2 (15, -1.05, 0);
                        if(me.getDistanceTo(R_GOAL_1) > me.getDistanceTo(R_GOAL_2)){     //踢向离我较远的对方门柱
                            return kickBall(KICK_FORWARD, R_GOAL_1);
                        }
                        else
                            return kickBall(KICK_FORWARD, R_GOAL_2);
                    }
                        
                }
            }
            else{      
                if(i == 1){             //若我应跑去防守点
                    VecPosition L_GOAL_1 (-15, 1.05, 0);
                    VecPosition L_GOAL_2 (-15, -1.05, 0);
                    if(me.getY() >= L_GOAL_1.getY() || me.getY() <= L_GOAL_2.getY()){      //若超出己方球门范围
                        return SKILL_STAND;
                    }
                    else
                        return goToTarget(collisionAvoidance(true, false, false, 1, .5,target[i], true));
                }
                else
                    return goToTarget(collisionAvoidance(true, false, false, 1, .5,target[i], true));    //其余⼈跑向⾃⼰点位
            }
        }
    }
    return SKILL_STAND;
}
