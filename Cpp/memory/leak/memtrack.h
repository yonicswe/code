#ifndef MEMTRACK_H_
#define MEMTRACK_H_

#include <stdlib.h>
#include <typeinfo>
#include <stdio.h>

namespace MemTrack
{

    class MemStamp
    {
        public: 
            char const * const fileName;
            char const * const funcName;
            int const lineNum;

        public:
            MemStamp(char const *fileName, 
                     char const *funcName,
                     int lineNum) : 
                fileName(fileName), 
                funcName(funcName), 
                lineNum(lineNum) 
                { };

            ~MemStamp() { }
    };

    template <class T> 
    inline T *operator*(const MemStamp &stamp, T *p)
    {
        printf("new %s:/%s(%p)+%d\n",
                stamp.fileName, 
                stamp.funcName,
                p,
                stamp.lineNum);
        return p;
    }

    template <class T> 
    inline void operator << (const MemStamp &stamp, T *p)
    {
        printf("delete %s:/%s(%p)+%d\n",
                stamp.fileName, 
                stamp.funcName,
                p,
                stamp.lineNum);
        delete p;
    }

    template <class T> 
    inline void operator >> (const MemStamp &stamp, T *p)
    {
        printf("delete[] %s:/%s(%p)+%d\n",
                stamp.fileName, 
                stamp.funcName,
                p,
                stamp.lineNum);
        delete [] p;
    } 
}


#define MEMTRACK_NEW MemTrack::MemStamp(__FILE__, __func__, __LINE__) * new
#define new MEMTRACK_NEW

#define MEMTRACK_DELETE MemTrack::MemStamp(__FILE__, __func__, __LINE__) <<
#define delete MEMTRACK_DELETE

#define MEMTRACK_DELETE_VEC MemTrack::MemStamp(__FILE__, __func__, __LINE__) >>
#define delete_vec MEMTRACK_DELETE_VEC


#endif    // MEMTRACK_H_

