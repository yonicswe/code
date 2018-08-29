typedef unsigned char BYTE;
                  
#define M_GetTBit(FLAGS)      (BYTE)((FLAGS>>7) & 0X1)
#define M_GetCBit(FLAGS)      (BYTE)((FLAGS>>6) & 0X1)
#define M_GetCSGBit(FLAGS)    (BYTE)((FLAGS>>2) & 0X3)
#define M_GetNSGBit(FLAGS)    (BYTE)((FLAGS>>0) & 0X3)

int 
main (int argc, char *argv[])
{
    BYTE flags=0x87;

    printf("T=0x%x, C=0x%x, CSG=0x%x, NSG=0x%x\n",
           M_GetTBit(flags),
           M_GetCBit(flags),
           M_GetCSGBit(flags),
           M_GetNSGBit(flags));

    return 0;

}
