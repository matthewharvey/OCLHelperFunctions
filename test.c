#include <stdio.h>
#include <CL/cl.h>
#include <CL/opencl.h>

#include "OCLHelperFunctions.h"

int main()
{
    cl_int err;
    int i,j;
    cl_platform_id platform_ids[10];
    cl_uint num_platforms;
    err = clGetPlatformIDs(sizeof(platform_ids)/sizeof(platform_ids[0]), &platform_ids[0], &num_platforms);
    if (err != CL_SUCCESS)
    {
        printf("Could not get Platform IDs: %s\n", OCLErrorMessage(err));
        exit(1);
    }
    for (i = 0; i < num_platforms; i++)
    {
        cl_uint num_devices;
        cl_device_id dev_ids[10];
        err = clGetDeviceIDs(platform_ids[i], CL_DEVICE_TYPE_ALL, sizeof(dev_ids)/sizeof(dev_ids[0]), &dev_ids[0], &num_devices);
        if (err != CL_SUCCESS)
        {
            printf("Could not get Device IDs for platform %d: %s\n", i, OCLErrorMessage(err));
            continue;
        }
        for (j = 0; j < num_devices; j++)
            DescribeDevice(dev_ids[j]);
    }

    return 0;
}
