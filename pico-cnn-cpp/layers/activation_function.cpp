#include "activation_function.h"

namespace pico_cnn {
    namespace naive {

        ActivationFunction::ActivationFunction(std::string name, uint32_t id, op_type op) : Layer(name, id, op) {

        }

        ActivationFunction::~ActivationFunction() = default;

        void ActivationFunction::run(Tensor *input, Tensor *output) {
            this->activate(input, output);
        }

        void ActivationFunction::activate(Tensor *input, Tensor *output) {
            if(input->copy_data_into(output) != 0)
                PRINT_ERROR_AND_DIE("Attempted to copy Tensors of unequal shapes.");
        }

        ReLU::ReLU(std::string name, uint32_t id, op_type op) : ActivationFunction(name, id, op) {

        }

        ReLU::~ReLU() {

        }

        void ReLU::run(Tensor *input, Tensor *output) {
            this->activate(input, output);
        }

        void ReLU::activate(Tensor *input, Tensor *output) {
            uint32_t num_elements = input->num_elements();
            for(uint32_t element = 0; element < num_elements; element++) {
                output->access_blob(element) = (input->access_blob(element) < 0.0) ? 0.0 : input->access_blob(element);
            }
        }
    }
}