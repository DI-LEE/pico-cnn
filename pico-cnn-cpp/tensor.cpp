#include "tensor.h"

namespace pico_cnn {
    namespace naive {

        Tensor::Tensor() {
            shape_ = TensorShape();
            data_ = nullptr;
        }

        // TODO: Check if copy-constructor is possible
//        Tensor::Tensor(const Tensor &other) {
//            shape_ = TensorShape(other.shape_);
//            data_ = new fp_t[shape_.total_num_elements()]();
//            std::memcpy(data_, other.data_, shape_.total_num_elements() * sizeof(fp_t));
//        }

        Tensor::Tensor(TensorShape &shape) {
            shape.freeze_shape();
            shape_ = shape;
            uint32_t tmp = shape_.total_num_elements();
            data_ = new fp_t[shape_.total_num_elements()]();
        }

        Tensor::~Tensor() {
            delete[](data_);
        }

        TensorShape &Tensor::shape() {
            return shape_;
        }

        uint32_t Tensor::size_bytes() {
            return shape_.total_num_elements() * sizeof(fp_t);
        }

        int32_t Tensor::copy_data_into(Tensor *dest) {
            if(this->shape() == dest->shape()) {
                std::memcpy(dest->data_, this->data_, size_bytes());
                return 0;
            } else {
                return -1;
            }
        }

        fp_t &Tensor::access(uint32_t x, ...) {
            va_list args;
            va_start(args, x);

            uint32_t dims = shape_.num_dimensions();
            uint32_t indexes[dims];

            indexes[0] = x;

            for(size_t i = 1; i < dims; i++) {
                indexes[i] = va_arg(args, uint32_t);
            }

            if(dims == 1) {

                return data_[x];

            } else if (dims == 2) {

                uint32_t *shape = shape_.shape();
                return data_[(indexes[0]*shape[1]) + (indexes[1])];

            } else if (dims == 3) {

                uint32_t *shape = shape_.shape();
                return data_[(indexes[0]*shape[1]*shape[2]) + (indexes[1]*shape[2]) + (indexes[2])];

            } else if (dims == 4) {

                uint32_t *shape = shape_.shape();
                return data_[(indexes[0]*shape[1]*shape[2]*shape[3]) + (indexes[1]*shape[2]*shape[3]) + (indexes[2]*shape[3]) + indexes[3]];

            } else {

                uint32_t offset = 0;
                uint32_t *shape = shape_.shape();
                for (size_t i = 0; i < dims; i++) {
                    offset += product(reinterpret_cast<int32_t *>(shape), i+1, dims) * indexes[i];
                }
                return *(data_+offset);

            }
        }
    }
}