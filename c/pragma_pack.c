
//
// the purpose of this file is to see how the pragma pack works. 
// the packing alignment effects the members of the struct as also 
// on the total size of the struct.
//
// compile this file with 
//    'gcc -g pragma_pack.c -o pragma_pack -O0'
// then run 
//    'cgdb pragma_pack'
//
// in cgdb command line do : 
//    p sizeof(ss)
//    p sizeof(tt)
//
// the output with pack(1) is 
//       (gdb) p sizeof(ss)
//       $1 = 32
//       (gdb) p sizeof(tt)
//       $2 = 23
//       (gdb) 
// although both structs are the same see that 
// since tt has pack(1) its size is exactly what you would expect - 23 bytes 
//    sizeof(int)       +  4  
//    sizeof(char)      +  1 
//    sizeof(int)       +  4 
//    sizeof(short)     +  2
//    sizeof(long long) +  8
//    sizeof(int)       +  4
//    ----------------------------
//                         23
//
// looking even closer you will notice that 'tt' memory look 
//       (gdb) x/23xb &tt
//       0x7fffffffdcf0: 0xa5    0xa5    0xa5    0xa5    0x0b    0x04    0x00    0x00
//       0x7fffffffdcf8: 0x00    0x05    0x00    0x06    0x00    0x00    0x00    0x00
//       0x7fffffffdd00: 0x00    0x00    0x00    0xa5    0xa5    0xa5    0xa5
//
//       notice that 0xb in offset 0x7fffffffdcf4 is really one byte.
//       we know this since its followed by the value of tt.i = 4
// 
// while 'ss' memory look 
//       0x7fffffffdd10: 0xa5    0xa5    0xa5    0xa5    0x0a    0x00    0x00    0x00
//       0x7fffffffdd18: 0x01    0x00    0x00    0x00    0x02    0x00    0x00    0x00
//       0x7fffffffdd20: 0x03    0x00    0x00    0x00    0x00    0x00    0x00    0x00
//       0x7fffffffdd28: 0xa5    0xa5    0xa5    0xa5    0x00    0x00    0x00    0x00
//
//       here we notice that 0xa in offset 0x7fffffffdd14 is really 4 bytes.
//       we know this since its followed by 3 bytes of zero and then the value of ss.i = 1
//    
//
//


struct S {
   int d1;
   char c;
   int i;   // size 4
   short j;   // size 2
   long long k;   // size 8
   int d2;
};

#pragma pack(1)
struct T {
   int d1;
   char c;
   int i;
   short j;
   long long k;
   int d2;
};

int main() {
//    printf("%d ", offsetof(S, i));
//    printf("%d ", offsetof(S, j));
//    printf("%d\n", offsetof(S, k));
   struct S        ss;
   struct T        tt;
//    printf("%d ", offsetof(T, i));
//    printf("%d ", offsetof(T, j));
//    printf("%d\n", offsetof(T, k));
//

   ss.d1=0xa5a5a5a5;
   ss.c = 0xa;
   ss.i= 1;
   ss.j= 2;
   ss.k= 3;
   ss.d2=0xa5a5a5a5;

   tt.d1=0xa5a5a5a5;
   tt.c = 0xb;
   tt.i= 4;
   tt.j= 5;
   tt.k= 6;
   tt.d2=0xa5a5a5a5;

}

