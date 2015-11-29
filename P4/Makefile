#Ritvik Upadhyaya and Parth Kejriwal
#Section 2
#CS 354 Assignment 4
all: cache1D_runall cache2D_runall

compileall: cache1D cache2Drows cache2Dcols

cache1D: cache1D.c
	gcc -o cache1D cache1D.c -Wall -m32

cache1D_runall: cache1D_4 cache1D_32 cache1D_64
	
cache1D_4: cache1D
	/p/course/cs354-common/public/cache/pin -t /p/course/cs354-common/public/cache/source/tools/Memory/obj-ia32/allcache.so -is 16384 -ia 1 -ib 4 -ds 16384 -da 1 -db 4 -- cache1D

cache1D_32: cache1D
	/p/course/cs354-common/public/cache/pin -t /p/course/cs354-common/public/cache/source/tools/Memory/obj-ia32/allcache.so -is 16384 -ia 1 -ib 32 -ds 16384 -da 1 -db 32 -- cache1D

cache1D_64: cache1D	
	/p/course/cs354-common/public/cache/pin -t /p/course/cs354-common/public/cache/source/tools/Memory/obj-ia32/allcache.so -is 16384 -ia 1 -ib 64 -ds 16384 -da 1 -db 64 -- cache1D

cache2D: cache2Drows cache2Dcols

cache2Drows: cache2Drows.c
	gcc -o cache2Drows cache2Drows.c -Wall -m32

cache2Dcols: cache2Dcols.c
	gcc -o cache2Dcols cache2Dcols.c -Wall -m32

cache2D_runall: cache2Drows_run cache2Dcols_run

cache2Drows_run: cache2Drows
	/p/course/cs354-common/public/cache/pin -t /p/course/cs354-common/public/cache/source/tools/Memory/obj-ia32/allcache.so -is 16384 -ia 1 -ib 64 -ds 16384 -da 1 -db 64 -- cache2Drows

cache2Dcols_run: cache2Dcols
	/p/course/cs354-common/public/cache/pin -t /p/course/cs354-common/public/cache/source/tools/Memory/obj-ia32/allcache.so -is 16384 -ia 1 -ib 64 -ds 16384 -da 1 -db 64 -- cache2Dcols

