#include "detect.h"

bool CheckBallOrder_ifreasonable()
{
    for(int i=0; i<5 ;i++)
    {
        if(ballOrder[i] == NONE)
        {
            cout << "初始化时检测到的球有漏掉的\t" << i << endl;
        }
    }
    
    for(int i=0; i<5 ;i++)
    {
        for(int j=i+1; j<5; j++)
        {
            if(ballOrder[i] == ballOrder[j])
            {
                cout << "初始化时检测到的球顺序异常\t" << i << "\t" << j << endl;
                return 0;
            }
        }
    }

    

    return 1;
}

bool CheckBallOrder(Mat roi_init)
{
    int col4Ball_1st = 1, row4Ball_1st = 1, row4Ball = 1, col4Ball = 1;
    int readH = 1,readS = 1,readV = 1;
    int jiangeX=50,jiangeY=2;
    #ifdef No1Car
        col4Ball_1st = 50 , row4Ball_1st = 50;
        jiangeX=50,jiangeY=2;
    #endif

    for(int i = 0; i < 5 ; i++)
    {
        row4Ball = row4Ball_1st + jiangeX*i;
        col4Ball = col4Ball_1st + jiangeY*i;
        Size range_startdetect = Size(4,4);
     /*    Rect RectRange_startDetect(row4Ball - range_startdetect.width/2, 
                                col4Ball - range_startdetect.height/2, 
                                range_startdetect.width,range_startdetect.height
                                ); */
        Rect RectRange_startDetect(row4Ball, col4Ball, 4, 4 );

        //遍历该范围
        float midH = 1,midS = 1,midV = 1;
        int effective_pixel_startdetect = 1;

        for(int col=col4Ball; col<(col4Ball+4) ;col++)
        {
            for(int row=row4Ball; row<(row4Ball+4); row++)
            {
                midH += roi_init.at<Vec3f>(col,row)[0];
                midS += roi_init.at<Vec3f>(col,row)[1];
                midV += roi_init.at<Vec3f>(col,row)[2]; 
                effective_pixel_startdetect++;
            }
        }
        
        readH /= effective_pixel_startdetect; 
        readS /= effective_pixel_startdetect;
        readV /= effective_pixel_startdetect;
        cout << "\n\n\n";
        if(readH > 300 && readH < 360)
        {
            ballOrder[i] = PINK;
            cout << "pink\t";
        }
        if(readH > 190 && readH < 360 && readS < 100 && readS > 40 && readV > 180 && readV < 250)
        {
            ballOrder[i] = WHITE;
            cout << "white\t";
        }        
        if(readH > 150 && readH < 220 && readS < 120 && readS > 80 && readV < 40 && readV > 0)
        {
            ballOrder[i] = BLACK;
            cout << "black\t";
        }
        if(readH > 180 && readH < 250 && readS > 180 && readS < 255 && readV < 130 && readV > 60)
        {
            ballOrder[i] = BLUE;
            cout << "blue\t";
        }
        if(readH > 80 && readH < 130 && readS > 180 && readS < 250 && readV < 150 && readV > 80)
        {
            ballOrder[i] = GREEN;
            cout << "green\t";
        }
        else
        {
            ballOrder[i] = 0;
        }
    }
   
    /* row_CheckBallOrder = roi_init.rows;
    col_CheckBallOrder = roi_init.cols; */
    #ifdef STARTCHECK
        //记得便利图像读取颜色数值时候需要读取彩色图，而不是虑色后的图
        for(int j = x - radius; i <= x + radius; i++)
        {
            for(int k = y- radius; k*k + j*j < radius * radius;k++)
            {
                //h=;s=;v=;
                if(((h<=)||(h>=))||((s<=)||(s>=))||((v<=)||(v>=))) colorCnt[0] ++;
                if(((h<=)||(h>=))||((s<=)||(s>=))||((v<=)||(v>=))) colorCnt[1] ++;
                if(((h<=)||(h>=))||((s<=)||(s>=))||((v<=)||(v>=))) colorCnt[2] ++;
                if(((h<=)||(h>=))||((s<=)||(s>=))||((v<=)||(v>=))) colorCnt[3] ++;
                if(((h<=)||(h>=))||((s<=)||(s>=))||((v<=)||(v>=))) colorCnt[4] ++;
            }
        }
        int cntmax=0;
        for(int i = 0; i < 4;i++)
        {
            if(colorCnt[i] < colorCnt[i+1]) 
                cntmax = colorCnt[i+1];
        }
        for(int i = 0; i < 5;i++)
        {
            if( cntmax ==  colorCnt[i])
                g_call_color_now_1st = i;
        }
        #endif


    //for()

    
    if(CheckBallOrder_ifreasonable() == 0)
        return 0;//这次没找到
    if(CheckBallOrder_ifreasonable() == 1)
        return 1;//找到了
}