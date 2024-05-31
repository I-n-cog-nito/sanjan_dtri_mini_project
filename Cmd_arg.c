#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[])
{
    float result = 0;
    //printf("Enter (AREA/PERIMETER/VOLUME || CIRCLE/RECTANGLE/TRIANGLE || LENGHT(RADIUS)(TRIANGLE SIDE1)/BREADTH(BASE)(TRIANGLE SIDE2)/(TRIANGLE SIDE3)\n");
    //printf("AREA RECTANGLE 10.0 5.0 0.0\n\n ");

    if (argc < 2)
    {
        printf("No Arguments Entered! \n");
        return 1; // Return error
    }

    //AREA

    if(!(strcmp(argv[1],"AREA")))
    {
        if(!(strcmp(argv[2],"CIRCLE")))
        {
            float radius = atof(argv[3]);
            result = 3.14*radius*radius;
            printf("The area of circle of radius %f is %fsq.units\n",radius,result);
        }
        else if(!(strcmp(argv[2],"RECTANGLE")))
        {
            float length = atof(argv[3]);
            float breadth = atof(argv[4]);
            result = length*breadth;
            printf("The area of rectangle of length %f and breadth %f is %fsq.units\n",length,breadth,result);
        }
        else if(!(strcmp(argv[2],"TRIANGLE")))
        {
            float base = atof(argv[3]);
            float height = atof(argv[4]);
            result = 0.5*base*height;
            printf("The area of triangle of base %f and height %f is %fsq.units\n",base,height,result);
        }
        else
        {
            printf("Invalid Arguments!");
        }
    }

    //PERIMETER
    else if(!(strcmp(argv[1],"PERIMETER")))
    {
        if(!(strcmp(argv[2],"CIRCLE")))
        {
            float radius = atof(argv[3]);
            result = 2*3.14*radius;
            printf("The perimeter of circle of radius %f is %funits\n",radius,result);
        }
        else if(!(strcmp(argv[2],"RECTANGLE")))
        {
            float length = atof(argv[3]);
            float breadth = atof(argv[4]);
            result = 2*(length+breadth);
            printf("The perimeter of rectangle of length %f and breadth %f is %funits\n",length,breadth,result);
        }
        else if(!(strcmp(argv[2],"TRIANGLE")))
        {
            float t1 = atof(argv[3]);
            float t2 = atof(argv[4]);
            float t3 = atof(argv[5]);
            result = t1+t2+t3;
            printf("The perimeter of triangle of sides %f,%f and %f is %funits\n",t1,t2,t3,result);
        }
        else
        {
            printf("Invalid Arguments!");
        }
    }

    //VOLUME
    else if(!(strcmp(argv[1],"VOLUME")))
    {
        if(!(strcmp(argv[2],"SPHERE")))
        {
            float radius = atof(argv[3]);
            result = (4/3)*3.14*radius*radius*radius;
            printf("The volume of sphere of radius %f is %fcubic units\n",radius,result);
        }
        else if(!(strcmp(argv[2],"CUBOID")))
        {
            float length = atof(argv[3]);
            float breadth = atof(argv[4]);
            float height = atof(argv[5]);
            result = length*breadth*height;
            printf("The volume of cuboid of length %f, breadth %f and height %f is %fcubic units\n",length,breadth,height,result);
        }
        else if(!(strcmp(argv[2],"CYLINDER")))
        {
            float radius = atof(argv[3]);
            float height = atof(argv[4]);
            result = 3.14*radius*radius*height;
            printf("The volume of cylinder of radius %f and height %f is %fcubic units\n",radius,height,result);
        }
        else if(!(strcmp(argv[2],"CONE")))
        {
            float radius = atof(argv[3]);
            float height = atof(argv[4]);
            result = 3.14*radius*radius*(height/3);
            printf("The volume of cone of radius %f and height %f is %fcubic units\n",radius,height,result);
        }
        else
        {
            printf("Invalid Arguments!");
        }
    }
    else
    {
        printf("Invalid Arguments!");
    }

    return 0;
}
