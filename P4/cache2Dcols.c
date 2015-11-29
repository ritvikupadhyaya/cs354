/*
* Ritvik Upadhyaya, Section 2
* Parth Kejriwal, Section 2
*/

#include <stdio.h>

int arr[3000][500];

int main(int argc, const char * argv[]) {
    int i,j;
    for (j = 0; j < 500; j++) {
        for (i = 0; i < 3000; i++) {
            arr[i][j] = i+j;
        }
        
    }
  return 0;
}
