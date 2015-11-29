#include <assert.h>
#include <stdlib.h>
#include "mem.h"

int main() {
   	assert(Mem_Init(4096) == 0);
   	void* ptr = Mem_Alloc(12);
	assert(ptr != NULL);
	assert(Mem_Free(ptr) == 0);
    assert(Mem_Free(NULL)== -1);
  	exit(0);
}
