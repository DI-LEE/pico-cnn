/**
 * @brief Local response normalization (LRN) activation function.
 *
 * @author Alexander Jung (University of Tuebingen, Chair for Embedded Systems)
 */
#ifndef PICO_CNN_LRN_H
#define PICO_CNN_LRN_H

#include <cmath>

#include "../../parameters.h"
#include "../../tensor.h"
#include "../layer.h"

#include "activation_function.h"

namespace pico_cnn {
    namespace naive {
        class LRN : ActivationFunction {
        public:
            LRN(std::string name, uint32_t id, op_type op, const fp_t alpha, const fp_t beta, const uint16_t n);
            ~LRN();

            void run(Tensor *input, Tensor *output) override;

        private:
            const fp_t alpha_, beta_;
            const uint16_t n_;

            void activate(Tensor *input, Tensor *output) override;
        };
    }
}

#endif //PICO_CNN_LRN_H
