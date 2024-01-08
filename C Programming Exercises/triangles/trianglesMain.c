#include "triangles.h"

int main(void)
{
    char cahrToPaint;
    int size;

    printf("Please enter triangle base size and a har to paint:\n");
    scanf("%d %c", &size, &cahrToPaint);

    printf("Calling StraightAngle:\n");
    StraightAngle(size, cahrToPaint);
    printf("Calling ReversedStraightAngle:\n");
    ReversedStraightAngle(size, cahrToPaint);
    printf("Calling Triangleisosceles:\n");
    Triangleisosceles(size, cahrToPaint);
    printf("Calling Pyramid:\n");
    Pyramid(size, cahrToPaint);
    printf("Calling ReversedPyramid:\n");
    ReversedPyramid(size, cahrToPaint);
    printf("Calling Diamond:\n");
    Diamond(size, cahrToPaint);
}