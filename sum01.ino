    /*
     * @程序功能：自动避险的火车
     * @实验现象：MAX在巡线的时候，可以及时判断前方是否有障碍物。如果在50cm内有障碍物，就发出音效，并原地打转或者掉头继续巡线，或者改变线路。
     * @author [liulihua](lihua.liu@dfrobot.com)
     * @version  V1.0
     * @date  2017-11-22
     */

    #include <DFRobot_MAX.h>    //载入MAX库
    DFRobot_MAX myMax;
    int l,r,c,u;                 //定义变量，l表示左巡线传感器，r右巡线传感器，c中间传感器 u超声波距离
    int i=1;                     //用于是否播放音效的标志

    void setup() {
      myMax.begin();             //初始化MAX系统
     // Serial.begin(9600);
      myMax.forward(70,70);      //程序开始就让MAX前进
    }

    void loop() {
      l=myMax.lineValue(2);    //读取左侧巡线传感器的值
      c=myMax.lineValue(1);    //读取中间巡线传感器的值
      r=myMax.lineValue(0);    //读取右侧巡线传感器的值
      u=myMax.distanceValue(); //读取超声波距离
      //Serial.println(u);
      if(u > 50){                   //判断障碍物距离是否小于50cm，小于的话，就执行巡线功能
        i = 1;                      //这个标志置1，用于重启避障模式的音效播放
        if(l==1 && c==1 && r==1){   //如果三个巡线传感器都在黑色上的话，就慢速前进。
          myMax.forward(70,70);
        }else{
            if( l==0 && c==1 && r==0){   //否则，就判断中间传感器是否在黑线上，左右在白线上
              myMax.forward(70,70);      //是的话，就直线前进
            }else{
              if((l==0 && c==1 && r==1)||(l==0 && c==0 && r==1)){  //否则的话，就判断右侧两个传感器是否在黑线上或者右侧一个在黑线上，从而判断小车左偏了。
                myMax.forward(150,70);      //是的话，就让小车右转
                if(l==0 && c==0 && r==0){  //如果小车速度过快，冲出去了，前面没有检测到的话
                  myMax.forward(130,70);   //依然继续让小车右转 从而避免误判断。
                  }
              }else{
                if((l==1 && c==0 && r==0)||(l==1 && c==1 && r==0)){  //否则的话，再通过巡线传感器判断小车是否往右偏了
                   myMax.forward(70,150);                            //是右偏的话，小车左转
                   if(l==0 && c==0 && r==0){                         //如果小车速度过快，冲出去了，前面没有检测到的话
                     myMax.forward(70,150);                          //依然继续让小车左转 从而避免误判断。
                     }
                   }
                 }
              }
           }
        }
      else{                                //如果距离小于50cm的话，执行避障模式
        if(i==1){                          //先判断标志是否为1
            i=0;                           //再把标志置零，从而避免多次调用音效
            myMax.playSound(12);           //发出音效
            }
         myMax.forward(0,130);            //如果有障碍物就让小车左转
        }
    }
