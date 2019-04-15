#define XSIGIPC  3
#define XSIGALRM 4
#define XSIGGPF  5

extern  struct  alrmqueue{
        uint32 alrmtime;
        pid32   alrmpid;
        struct  alrmqueue * alrmnext;
}

extern struct alrmqueue * alrmqueue;
