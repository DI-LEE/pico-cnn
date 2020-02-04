#include "test_convolution.h"

// padding for 2d [start of height padding, start of width_padding, end of height padding, end of width padding]


int convolution1d_output_size(int input_size, int kernel_size, int stride, int start_padding, int end_padding) {
    return (input_size - kernel_size + start_padding + end_padding)/stride  + 1;
}

void convolution2d_output_size(int input_height, int input_width,
                               int kernel_height, int kernel_width,
                               int stride_height, int stride_width,
                               const int* padding, int* output) {
    output[0] = convolution1d_output_size(input_height, kernel_height, stride_height, padding[0], padding[2]);
    output[1] = convolution1d_output_size(input_width, kernel_width, stride_width, padding[1], padding[3]);
}

int test_convolution1d_naive() {

    printf("test_convolution_1d_naive()\n");
    int return_value = 0;

    #define input_size 11
    #define kernel_size 3
    #define expected_output_size 5
    fp_t error = 0.001;
    int stride =  2;
    int padding =  0;
    fp_t bias = -2;
    fp_t kernel[kernel_size] = {2, -1, 0};
    fp_t input[input_size] = {-9, 0, 3, -5, -10, 7, 3, -2, -2, 3,4};
    fp_t expected_output[expected_output_size] = {-20, 9, -29, 6, -9};

    assert(convolution1d_output_size(input_size, kernel_size, stride, padding, padding) == expected_output_size);
    fp_t* output = (fp_t*) malloc(expected_output_size * sizeof(fp_t));

    convolution1d_naive(input, input_size, output, kernel, kernel_size, stride, padding, bias);

    return_value = compare1dFloatArray(output, expected_output, expected_output_size, error);

    free(output);

    return return_value;

    #undef input_size
    #undef kernel_size
    #undef expected_output_size
}

int test_convolution2d_naive_1() {
    printf("test_convolution2d_naive_1()\n");
    int return_value = 0;

    #define input_height 4
    #define input_width 3
    #define kernel_size 3
    #define expected_output_height 4
    #define expected_output_width 3

    fp_t error = 0.001;
    int stride = 1 ;
    int padding[4] = {1,1,1,1};
    fp_t bias = 0;
    fp_t kernel[kernel_size*kernel_size] = {-5, -1, -3,
                                             10, 3,  0,
                                             4, -6,  6};
    fp_t input[input_height * input_width] =
     {-5,-4, -5,
      -6, 5, -10,
       8, 9, -3,
       0,-9, -1};
    fp_t expected_output[expected_output_height * expected_output_width] =
      {51,-176,  25,
        5, -41,  99,
      -39, 210,  36,
      -35, -67,-135};

    int* dimensions = (int*) malloc(2 * sizeof(int));
    convolution2d_output_size(input_height,input_width, kernel_size, kernel_size,
                              stride, stride, padding, dimensions);

    assert(dimensions[0] == expected_output_height);
    assert(dimensions[1] == expected_output_width);

    fp_t* output = (fp_t*) malloc(expected_output_width*expected_output_height * sizeof(fp_t));
    convolution2d_padding_naive(input, input_height, input_width, output, kernel,
                                    kernel_size, kernel_size, stride, stride,
                                    padding, bias);

    return_value = compare1dFloatArray(output, expected_output,expected_output_height * expected_output_width,error);

    free(dimensions);
    free(output);

    return return_value;

    #undef input_height
    #undef input_width
    #undef kernel_size
    #undef expected_output_width
    #undef expected_output_height


}

int test_convolution2d_naive_2(){

    printf("test_convolution2d_naive_2()\n");
    int return_value = 0;

    #define input_height 4
    #define input_width 3
    #define kernel_size 3
    #define expected_output_height 4
    #define expected_output_width 3

    fp_t error = 0.001;
    int stride = 1 ;
    int padding[4] = {1,1,1,1};
    fp_t bias = 0;
    fp_t kernel[kernel_size*kernel_size] = {0,0,0,
                                            0,0,0,
                                            0,0,0};
    fp_t input[input_height * input_width] =
     {-5,-4, -5,
      -6, 5, -10,
       8, 9, -3,
       0,-9, -1};
    fp_t expected_output[expected_output_height * expected_output_width] =
      {0,0,0,
       0,0,0,
       0,0,0,
       0,0,0};

    int* dimensions = (int*) malloc(2 * sizeof(int));
    convolution2d_output_size(input_height, input_width, kernel_size, kernel_size,
                              stride, stride, padding, dimensions);

    assert(dimensions[0] == expected_output_height);
    assert(dimensions[1] == expected_output_width);

    fp_t* output = (fp_t*) malloc(expected_output_width*expected_output_height * sizeof(fp_t));
    convolution2d_padding_naive(input, input_height, input_width, output, kernel,
                                    kernel_size, kernel_size, stride, stride,
                                    padding, bias);

    return_value = compare1dFloatArray(output, expected_output,expected_output_height * expected_output_width,error);

    free(dimensions);
    free(output);

    return return_value;

    #undef input_height
    #undef input_width
    #undef kernel_size
    #undef expected_output_width
    #undef expected_output_height

}

int test_convolution2d_naive_3() {

    int return_value = 0;
    printf("test_convolution2d_naive_3()\n");


    #define input_height 8
    #define input_width 6
    #define kernel_height 1
    #define kernel_width 3
    #define expected_output_height 10
    #define expected_output_width 8

    fp_t error = 0.001;

    const int padding[4] = {0,1,2,3};
    int stride_height = 1;
    int stride_width = 1;
    fp_t bias = 0;

    fp_t kernel[kernel_height*kernel_width] = {-3, -1, 0};

    fp_t input[input_height*input_width] =
      {8,  9,   9,  6, -10, 10,
      10, -8,   2,  6,  -3, -8,
       9,  0,   7, 10,  -7,  5,
      -8,  2,  -8,  9,  -3, -5,
      -2,  5,  -4, -1,   5, -1,
      -7, -6,   1, -8,   9, -6,
      -2, -4, -10,  6, -10, -2,
       2,  5,   1, -7,   3, -1};

    fp_t expected_output[expected_output_height * expected_output_width] =
      {  -8, -33, -36, -33,  -8,  20, -30, 0,
        -10, -22,  22, -12, -15,  17,  24, 0,
         -9, -27,  -7, -31, -23,  16,  -15, 0,
          8,  22,   2,  15, -24,  14, 15, 0,
          2,   1, -11,  13,  -2, -14, 3, 0,
          7,  27,  17,   5,  15, -21, 18, 0,
          2,  10,  22,  24,  -8,  32, 6, 0,
         -2, -11, -16,   4,  18,  -8, 3, 0,
          0,   0,   0,   0,   0,   0,  0, 0,
          0,   0,   0,   0,   0,   0,  0, 0
       };

    int* dimensions = (int*) malloc(2 * sizeof(int));
    convolution2d_output_size(input_height, input_width, kernel_height, kernel_width,
                              stride_height, stride_width, padding, dimensions);

    assert(dimensions[0] == expected_output_height);
    assert(dimensions[1] == expected_output_width);

    fp_t* output = (fp_t*) malloc(expected_output_width*expected_output_height * sizeof(fp_t));

    convolution2d_padding_naive(input, input_height, input_width, output,
                                kernel, kernel_height, kernel_width,
                                stride_height, stride_width, padding, bias);

    return_value = compare1dFloatArray(output, expected_output, expected_output_height * expected_output_width,error);

    free(dimensions);
    free(output);

    return return_value;

    #undef input_height
    #undef input_width
    #undef kernel_height
    #undef kernel_width
    #undef expected_output_width
    #undef expected_output_height


}

int test_convolution2d_naive_4() {

    int return_value = 0;
    printf("test_convolution2d_naive_4()\n");


    #define input_height 8
    #define input_width 6
    #define kernel_height 1
    #define kernel_width 3
    #define expected_output_height 5
    #define expected_output_width 3

    fp_t error = 0.001;

    int padding[4] = {0,1,2,3};
    int stride_height = 2;
    int stride_width = 3;
    fp_t bias = 0;

    fp_t kernel[kernel_height*kernel_width] = {-3, -1, 0};

    fp_t input[input_height*input_width] =
      {8,  9,   9,  6, -10, 10,
      10, -8,   2,  6,  -3, -8,
       9,  0,   7, 10,  -7,  5,
      -8,  2,  -8,  9,  -3, -5,
      -2,  5,  -4, -1,   5, -1,
      -7, -6,   1, -8,   9, -6,
      -2, -4, -10,  6, -10, -2,
       2,  5,   1, -7,   3, -1};

    fp_t expected_output[expected_output_height * expected_output_width] =
      {  -8, -33, -30,
         -9, -31, -15,
          2,  13,   3,
          2,  24,   6,
          0,   0,   0
       };

    int* dimensions = (int*) malloc(2 * sizeof(int));
    convolution2d_output_size(input_height, input_width, kernel_height, kernel_width,
                              stride_height, stride_width, padding, dimensions);

    assert(dimensions[0] == expected_output_height);
    assert(dimensions[1] == expected_output_width);

    fp_t* output = (fp_t*) malloc(expected_output_width*expected_output_height * sizeof(fp_t));

    convolution2d_padding_naive(input, input_height, input_width, output,
                                kernel, kernel_height, kernel_width,
                                stride_height, stride_width, padding, bias);

    return_value = compare1dFloatArray(output, expected_output, expected_output_height*expected_output_width,error);

    free(dimensions);
    free(output);

    return return_value;

    #undef input_height
    #undef input_width
    #undef kernel_height
    #undef kernel_width
    #undef expected_output_width
    #undef expected_output_height


}

int test_convolution2d_naive_5() {
    int return_value = 0;
    printf("test_convolution2d_naive_5()\n");


    #define input_height 7
    #define input_width 5
    #define kernel_height 5
    #define kernel_width 3
    #define expected_output_height 3
    #define expected_output_width 3

    fp_t error = 0.001;

    int padding[4] = {1, 2, 4, 0};
    int stride_height = 3;
    int stride_width = 2;
    fp_t bias = 0.4;

    fp_t kernel[kernel_height*kernel_width] =
       {-3, -4,  1,
        -5,  5,  2,
         1,  2, -1,
        -1,  1, -4,
        -4, -2,  5};

    fp_t input[input_height*input_width] =
      {4, 13,  13,  -2,   6,
      -7, 15, -11,  -9, -15,
      -8, -3,   2,   6,  -9,
       1, -8,  13,  -6,  -7,
      -6, -6,  13,  13,   8,
     -15, 14, -12,   8,   1,
       3,  6,   7, -12,   2};

       //padded
       // 0, 0,  0,  0,   0,    0,   0,
       // 0, 0,  4,  13,  13,  -2,   6,
       // 0, 0,  -7, 15, -11,  -9, -15,
       // 0, 0,  -8, -3,   2,   6,  -9,
       // 0, 0,   1, -8,  13,  -6,  -7,
       // 0, 0,  -6, -6,  13,  13,   8,
       // 0, 0, -15, 14, -12,   8,   1,
       // 0, 0,  3,  6,   7, -12,   2,
       // 0, 0,  0,  0,   0,   0,   0,
       // 0, 0,  0,  0,   0,   0,   0,
       // 0, 0,  0,  0,   0,   0,   0,
       // 0, 0,  0,  0,   0,   0,   0,

    fp_t expected_output[expected_output_height * expected_output_width] =
      { 52.4, 179.4, -111.6,
        75.4, 76.4, -94.6,
         -8.6, 6.4, -85.6};

    int* dimensions = (int*) malloc(2 * sizeof(int));
    convolution2d_output_size(input_height, input_width, kernel_height, kernel_width,
                              stride_height, stride_width, padding, dimensions);

    assert(dimensions[0] == expected_output_height);
    assert(dimensions[1] == expected_output_width);

    fp_t* output = (fp_t*) malloc(expected_output_width*expected_output_height*sizeof(fp_t));

    convolution2d_padding_naive(input, input_height, input_width, output,
                                kernel, kernel_height, kernel_width,
                                stride_height, stride_width, padding, bias);

    return_value = compare1dFloatArray(output, expected_output, expected_output_height*expected_output_width,error);

    free(dimensions);
    free(output);

    return return_value;

    #undef input_height
    #undef input_width
    #undef kernel_height
    #undef kernel_width
    #undef expected_output_width
    #undef expected_output_height
}

int test_add_channel2d_naive() {

    printf("test_add_channel2d_naive()\n");
    int return_value = 0;

    #define input_width 4
    #define input_height 3
    fp_t error = 0.001;

    fp_t input1[input_height*input_width] =
     {-6,-4, 3, -5,
       3, 4, 2,  8,
      -5, 6, 1, -4};

    fp_t input2[input_height*input_width] =
     {1, -3, -1,  5,
     -7,  7,  6, -5,
      7, -5,  4, -6};
    fp_t expected_output[input_height*input_width] =
     {-5, -7, 2,  0,
      -4, 11, 8,  3,
       2,  1, 5,-10};

    add_channel2d_naive(input1, input2, input_height, input_width);

    return_value = compare1dFloatArray(input1, expected_output, input_height * input_width, error);

    return return_value;

    #undef input_width
    #undef input_height
}
