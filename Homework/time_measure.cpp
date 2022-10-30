#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

int main()
{
    struct timeval start, end;
    long mtime, seconds, useconds;    
    gettimeofday(&start, NULL);
    
    usleep(5000);
    
    gettimeofday(&end, NULL);
    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;
    
    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
    printf("Elapsed time: %ld milliseconds\n", mtime);
    
    mtime = ((seconds) * 1000000 + useconds) + 0.5;
    printf("Elapsed time: %ld microseconds\n", mtime);
    
    return 0;
}