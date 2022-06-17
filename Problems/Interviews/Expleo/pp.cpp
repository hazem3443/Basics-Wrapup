typedef struct xyzm{
     uint8_t 	     En_Disable;
     uint8_t         CalculatedEarth;
     TripRstTimeMode tripTimeMode;
     TripRstTimeMode resetMode;
     uint16_t        PickmA;
     uint16_t        OpLvL;   // 1100
     uint16_t        Rst_LvL;  //950
     uint16_t        DTL_Time;
     uint16_t        RstDTL_Time;
     uint16_t        MinOpTime;
     uint16_t        Follower;
     uint16_t        _TMS;   //Time Dial (TMS): 0.01 to 1.5 (step 0.01)
     uint16_t        SecHRatio;
     uint8_t	     SecondHarBlk;
     uint8_t	     BreakerProtect; 
 }tripcfglow_st;

