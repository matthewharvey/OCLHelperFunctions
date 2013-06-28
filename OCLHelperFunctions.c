#include <stdio.h>
#include <CL/cl.h>
#include <CL/opencl.h>

#include "OCLHelperFunctions.h"

typedef enum
{
    c_uint,
    c_ulong,
    c_size,
    c_size_three,
    c_bool,
    c_string,
    c_fp_config,
    c_cache_type,
    c_mem_type,
    c_device_type
} type;

typedef struct
{
    cl_int code;
    const char* description;
    type object_type;
} dev_param;

const dev_param parameters[] = {
    { CL_DEVICE_NAME,                           "Device Name",                          c_string        },
    { CL_DEVICE_TYPE,                           "Device Type",                          c_device_type   },
    { CL_DEVICE_VENDOR,                         "Device Vendor",                        c_string        },
    { CL_DEVICE_VERSION,                        "Device Version",                       c_string        },
    { CL_DRIVER_VERSION,                        "Driver Version",                       c_string        },
    { CL_DEVICE_PROFILE,                        "Supported Profile",                    c_string        },
    { CL_DEVICE_VENDOR_ID,                      "Vendor ID",                            c_uint          },
    { CL_DEVICE_AVAILABLE,                      "Device Available",                     c_bool          },
    { CL_DEVICE_MAX_CLOCK_FREQUENCY,            "Max Clock Freq",                       c_uint          },
    { CL_DEVICE_MAX_COMPUTE_UNITS,              "Max Compute Units",                    c_uint          },
    { CL_DEVICE_ADDRESS_BITS,                   "Device Address Bits",                  c_uint          },
    { CL_DEVICE_COMPILER_AVAILABLE,             "Compiler Available",                   c_bool          },
    { CL_DEVICE_ENDIAN_LITTLE,                  "Device Is Little Endian",              c_bool          },
    { CL_DEVICE_ERROR_CORRECTION_SUPPORT,       "Error Correction Support",             c_bool          },
    { CL_DEVICE_GLOBAL_MEM_CACHE_SIZE,          "Global Mem Cache Size",                c_ulong         },
    { CL_DEVICE_GLOBAL_MEM_CACHE_TYPE,          "Global Mem Cache Type",                c_cache_type    },
    { CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE,      "Global Mem Cacheline Size",            c_uint          },
    { CL_DEVICE_GLOBAL_MEM_SIZE,                "Global Mem Size",                      c_ulong         },
    { CL_DEVICE_IMAGE_SUPPORT,                  "Image Support",                        c_bool          },
    { CL_DEVICE_IMAGE2D_MAX_HEIGHT,             "2D Image Max Height",                  c_size          },
    { CL_DEVICE_IMAGE2D_MAX_WIDTH,              "2D Image Max Width",                   c_size          },
    { CL_DEVICE_IMAGE3D_MAX_DEPTH,              "3D Image Max Depth",                   c_size          },
    { CL_DEVICE_IMAGE3D_MAX_HEIGHT,             "3D Image Max Height",                  c_size          },
    { CL_DEVICE_IMAGE3D_MAX_WIDTH,              "3D Image Max Width",                   c_size          },
    { CL_DEVICE_LOCAL_MEM_SIZE,                 "Local Mem Size",                       c_ulong         },
    { CL_DEVICE_LOCAL_MEM_TYPE,                 "Local Mem Type",                       c_mem_type      },
    { CL_DEVICE_MAX_CONSTANT_ARGS,              "Max Constant Args",                    c_uint          },
    { CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE,       "Max Constant Buffer Size",             c_ulong         },
    { CL_DEVICE_MAX_MEM_ALLOC_SIZE,             "Max Mem Alloc Size",                   c_ulong         },
    { CL_DEVICE_MAX_PARAMETER_SIZE,             "Max Parameter Size",                   c_size          },
    { CL_DEVICE_MAX_READ_IMAGE_ARGS,            "Max Image Args per Kernel",            c_uint          },
    { CL_DEVICE_MAX_SAMPLERS,                   "Max Samplers Per Kernel",              c_uint          },
    { CL_DEVICE_MAX_WORK_GROUP_SIZE,            "Max Work Group Size",                  c_size          },
    { CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,       "Max Work Item Dimensions",             c_uint          },
    { CL_DEVICE_MAX_WORK_ITEM_SIZES,            "Max Work Item Sizes",                  c_size_three    },
    { CL_DEVICE_MAX_WRITE_IMAGE_ARGS,           "Max Write Images per Kernel",          c_uint          },
    { CL_DEVICE_HALF_FP_CONFIG,                 "Half Floating Point Capabilities",     c_fp_config     },
    { CL_DEVICE_SINGLE_FP_CONFIG,               "Single Floating Point Capabilities",   c_fp_config     },
    { CL_DEVICE_DOUBLE_FP_CONFIG,               "Double Floating Point Capabilities",   c_fp_config     },
    { CL_DEVICE_MEM_BASE_ADDR_ALIGN,            "Mem Base Address Align",               c_uint          },
    { CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE,       "Min Data Type Align Size",             c_uint          },
    { CL_DEVICE_PROFILING_TIMER_RESOLUTION,     "Profiling Timer Resolution",           c_size          },
    
    { CL_DEVICE_EXTENSIONS,                     "Supported Extensions",                 c_string        }
};


void DescribeDevice(cl_device_id device)
{
    cl_int retval;
    unsigned int i;
    unsigned int arraySize = sizeof(parameters)/sizeof(parameters[0]);
    for (i = 0; i < arraySize; i++)
    {
        switch (parameters[i].object_type)
        {
        case c_uint:
        {
            cl_uint var;
            retval = clGetDeviceInfo(device, parameters[i].code, sizeof(var), &var, NULL);
            if (retval != CL_SUCCESS)
                printf("Failed to get %s : %s\n", parameters[i].description, OCLErrorMessage(retval));
            else
                printf("%s:\t%u\n", parameters[i].description, var);
            break;
        }
        case c_ulong:
        {
            cl_ulong var;
            retval = clGetDeviceInfo(device, parameters[i].code, sizeof(var), &var, NULL);
            if (retval != CL_SUCCESS)
                printf("Failed to get %s : %s\n", parameters[i].description, OCLErrorMessage(retval));
            else
                printf("%s:\t%lu\n", parameters[i].description, var);
            break;
        }
        case c_size:
        {
            size_t var;
            retval = clGetDeviceInfo(device, parameters[i].code, sizeof(var), &var, NULL);
            if (retval != CL_SUCCESS)
                printf("Failed to get %s : %s\n", parameters[i].description, OCLErrorMessage(retval));
            else
                printf("%s:\t%lu\n", parameters[i].description, (unsigned long)var);
            break;
        }
        case c_size_three:
        {
            size_t var[3];
            retval = clGetDeviceInfo(device, parameters[i].code, sizeof(var), &var, NULL);
            if (retval != CL_SUCCESS)
                printf("Failed to get %s : %s\n", parameters[i].description, OCLErrorMessage(retval));
            else
                printf("%s:\t(%lu, %lu, %lu)\n", parameters[i].description, var[0], var[1], var[2]);
            break;
        }
        case c_bool:
        {
            cl_bool var;
            retval = clGetDeviceInfo(device, parameters[i].code, sizeof(var), &var, NULL);
            if (retval != CL_SUCCESS)
                printf("Failed to get %s : %s\n", parameters[i].description, OCLErrorMessage(retval));
            else
                printf("%s:\t%s\n", parameters[i].description, var == CL_TRUE? "True" : "False");
            break;
        }
        case c_string:
        {
            char var[1024];
            retval = clGetDeviceInfo(device, parameters[i].code, sizeof(var), &var, NULL);
            if (retval != CL_SUCCESS)
                printf("Failed to get %s : %s\n", parameters[i].description, OCLErrorMessage(retval));
            else
                printf("%s:\t%s\n", parameters[i].description, var);
            break;
        }
        case c_fp_config:
        {
            cl_device_fp_config var;
            retval = clGetDeviceInfo(device, parameters[i].code, sizeof(var), &var, NULL);
            if (retval != CL_SUCCESS)
                printf("Failed to get %s : %s\n", parameters[i].description, OCLErrorMessage(retval));
            else
                printf("%s:\n"
                        "\tCL_FP_DENORM:\t\t%s\n"
                        "\tCL_FP_INF_NAN:\t\t%s\n"
                        "\tCL_FP_ROUND_TO_NEAREST:\t%s\n"
                        "\tCL_FP_ROUND_TO_ZERO:\t%s\n"
                        "\tCL_FP_ROUND_TO_INF:\t%s\n"
                        "\tCP_FP_FMA:\t\t\t%s\n",
                        parameters[i].description,
                        var & CL_FP_DENORM ? "True" : "False",
                        var & CL_FP_INF_NAN ? "True" : "False",
                        var & CL_FP_ROUND_TO_NEAREST ? "True" : "False",
                        var & CL_FP_ROUND_TO_ZERO ? "True" : "False",
                        var & CL_FP_ROUND_TO_INF ? "True" : "False",
                        var & CL_FP_FMA ? "True" : "False"
                        );
            break;
        }
        case c_cache_type:
        {
            cl_device_mem_cache_type var;
            retval = clGetDeviceInfo(device, parameters[i].code, sizeof(var), &var, NULL);
            if (retval != CL_SUCCESS)
                printf("Failed to get %s : %s\n", parameters[i].description, OCLErrorMessage(retval));
            else
            {
                if (var == CL_NONE)
                    printf("%s:\tCL_NONE\n", parameters[i].description);
                else if (var == CL_READ_ONLY_CACHE)
                    printf("%s:\tCL_READ_ONLY_CACHE\n", parameters[i].description);
                else if (var == CL_READ_WRITE_CACHE)
                    printf("%s:\tCL_READ_WRITE_CACHE\n", parameters[i].description);
                else
                    printf("%s:\tInvalid Value\n", parameters[i].description);
            }
            break;
        }
        case c_mem_type:
        {
            cl_device_local_mem_type var;
            retval = clGetDeviceInfo(device, parameters[i].code, sizeof(var), &var, NULL);
            if (retval != CL_SUCCESS)
                printf("Failed to get %s : %s\n", parameters[i].description, OCLErrorMessage(retval));
            else
            {
                if (var == CL_LOCAL)
                    printf("%s:\tCL_LOCAL\n", parameters[i].description);
                else if (var == CL_GLOBAL)
                    printf("%s:\tCL_GLOBAL\n", parameters[i].description);
                else
                    printf("%s:\tInvalid Value\n", parameters[i].description);
            }
            break;
        }
        case c_device_type:
        {
            cl_device_type var;
            retval = clGetDeviceInfo(device, parameters[i].code, sizeof(var), &var, NULL);
            if (retval != CL_SUCCESS)
                printf("Failed to get %s : %s\n", parameters[i].description, OCLErrorMessage(retval));
            else
            {
                printf("%s:\n"
                        "\tCL_DEVICE_TYPE_CPU:\t%s\n"
                        "\tCL_DEVICE_TYPE_GPU:\t%s\n"
                        "\tCL_DEVICE_TYPE_ACCELERATOR:\t%s\n"
                        "\tCL_DEVICE_TYPE_DEFAULT:\t%s\n",
                        parameters[i].description,
                        var & CL_DEVICE_TYPE_CPU ? "True" : "False",
                        var & CL_DEVICE_TYPE_GPU ? "True" : "False",
                        var & CL_DEVICE_TYPE_ACCELERATOR ? "True" : "False",
                        var & CL_DEVICE_TYPE_DEFAULT ? "True" : "False"
                        );
            }
            break;
        }
        default:
            printf("Error: Unknown object_type\n");
            break;
        }
    }
}

const char* OCLErrorMessage(cl_int retval)
{
#ifndef NDEBUG
    const char* message = NULL;
    switch (retval)
    {
    case CL_SUCCESS:
        break;
    case CL_DEVICE_NOT_FOUND:
        message = "CL:Device not Found";
        break;
    case CL_DEVICE_NOT_AVAILABLE:
        message = "CL:Device not Available";
        break;
    case CL_COMPILER_NOT_AVAILABLE:
        message = "CL:Compiler not Available";
        break;
    case CL_MEM_OBJECT_ALLOCATION_FAILURE:
        message = "CL:Memory Object Allocation Failed";
        break;
    case CL_OUT_OF_RESOURCES:
        message = "CL:Out of Resources";
        break;
    case CL_OUT_OF_HOST_MEMORY:
        message = "CL:Out of Host Memory";
        break;
    case CL_PROFILING_INFO_NOT_AVAILABLE:
        message = "CL:Profiling info is not available";
        break;
    case CL_MEM_COPY_OVERLAP:
        message = "CL:Memory copy overlap";
        break;
    case CL_IMAGE_FORMAT_MISMATCH:
        message = "CL:Image Format Mismatch";
        break;
    case CL_IMAGE_FORMAT_NOT_SUPPORTED:
        message = "CL:Image Format Not Supported";
        break;
    case CL_BUILD_PROGRAM_FAILURE:
        message = "CL:Build Program Failure";
        break;
    case CL_MAP_FAILURE:
        message = "CL:Map Failure";
        break;
    case CL_INVALID_VALUE:
        message = "CL:Invalid Value";
        break;
    case CL_INVALID_DEVICE_TYPE:
        message = "CL:Invalid Device Type";
        break;
    case CL_INVALID_PLATFORM:
        message = "CL:Invalid Platform";
        break;
    case CL_INVALID_DEVICE:
        message = "CL:Invalid Device";
        break;
    case CL_INVALID_CONTEXT:
        message = "CL:Invalid Context";
        break;
    case CL_INVALID_QUEUE_PROPERTIES:
        message = "CL:Invalid Queue Properties";
        break;
    case CL_INVALID_COMMAND_QUEUE:
        message = "CL:Invalid Command Queue";
        break;
    case CL_INVALID_HOST_PTR:
        message = "CL:Invalid Host Pointer";
        break;
    case CL_INVALID_MEM_OBJECT:
        message = "CL:Invalid Memory Object";
        break;
    case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
        message = "CL:Invalid Image Format Descriptor";
        break;
    case CL_INVALID_IMAGE_SIZE:
        message = "CL:Invalid Image Size";
        break;
    case CL_INVALID_SAMPLER:
        message = "CL:Invalid Sampler";
        break;
    case CL_INVALID_BINARY:
        message = "CL:Invalid Binary";
        break;
    case CL_INVALID_BUILD_OPTIONS:
        message = "CL:Invalid Build Options";
        break;
    case CL_INVALID_PROGRAM:
        message = "CL:Invalid Program";
        break;
    case CL_INVALID_PROGRAM_EXECUTABLE:
        message = "CL:Invalid Program Executable";
        break;
    case CL_INVALID_KERNEL_NAME:
        message = "CL:Invalid Kernel Name";
        break;
    case CL_INVALID_KERNEL_DEFINITION:
        message = "CL:Invalid Kernel Definition";
        break;
    case CL_INVALID_KERNEL:
        message = "CL:Invalid Kernel";
        break;
    case CL_INVALID_ARG_INDEX:
        message = "CL:Invalid Argument Index";
        break;
    case CL_INVALID_ARG_VALUE:
        message = "CL:Invalid Argument Value";
        break;
    case CL_INVALID_ARG_SIZE:
        message = "CL:Invalid Argument Size";
        break;
    case CL_INVALID_KERNEL_ARGS:
        message = "CL:Invalid Kernel Arguments";
        break;
    case CL_INVALID_WORK_DIMENSION:
        message = "CL:Invalid Work Dimension";
        break;
    case CL_INVALID_WORK_GROUP_SIZE:
        message = "CL:Invalid Work Group Size";
        break;
    case CL_INVALID_WORK_ITEM_SIZE:
        message = "CL:Invalid Work Item Size";
        break;
    case CL_INVALID_GLOBAL_OFFSET:
        message = "CL:Invalid Global Offset";
        break;
    case CL_INVALID_EVENT_WAIT_LIST:
        message = "CL:Invalid Event Wait List";
        break;
    case CL_INVALID_EVENT:
        message = "CL:Invalid Event";
        break;
    case CL_INVALID_OPERATION:
        message = "CL:Invalid Operation";
        break;
    case CL_INVALID_GL_OBJECT:
        message = "CL:Invalid GL Object";
        break;
    case CL_INVALID_BUFFER_SIZE:
        message = "CL:Invalid Buffer Size";
        break;
    case CL_INVALID_MIP_LEVEL:
        message = "CL:Invalid Mip Level";
        break;
    case CL_INVALID_GLOBAL_WORK_SIZE:
        message = "CL:Invalid Global Work Size";
        break;
    default:
        message = "CL:Unknown Error";
        break;
    }

#endif
    return message;
}
