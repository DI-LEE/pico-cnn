#include "pooling.h"

pico_cnn::naive::Pooling::Pooling(std::string name, uint32_t id, pico_cnn::op_type op, uint32_t *kernel_size,
                                  uint32_t *stride, uint32_t *padding) : Layer(name, id, op) {

    kernel_size_ = kernel_size;
    stride_ = stride;
    padding_ = padding;
}

void pico_cnn::naive::Pooling::run(pico_cnn::naive::Tensor *input, pico_cnn::naive::Tensor *output) {

    if (input->shape()->num_dimensions() == 4 || input->shape()->num_dimensions() == 3) {

        Tensor *input_tensor;

        if (padding_) {
            input_tensor = input->expand_with_padding(padding_);
        } else {
            input_tensor = input;
        }

        this->pool(input_tensor, output);

        if (padding_) {
            delete input_tensor->shape();
            delete input_tensor;
        }
    } else {
        PRINT_ERROR_AND_DIE("Not implemented for TensorShape: " << *input->shape());
    }
}