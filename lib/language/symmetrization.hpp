#pragma once

#include <language/command.hpp>
#include <language/argument.hpp>
#include <language/api.hpp>

#include <tensor/index.hpp>
#include <tensor/tensor.hpp>

#include <generator/base_tensor.hpp>

using Construction::Tensor::Tensor;

namespace Construction {
    namespace Language {

        CLI_COMMAND(Symmetrize, true)

            std::string Help() const {
                return "Symmetrize(<Tensors>, <Indices>)";
            }

            static bool Cachable() {
                return false;
            }

            TensorContainer Execute() const {
                TensorContainer result = GetTensors(0);

                for (int i=1; i<Size(); i++) {
                    result = API::Symmetrize(result, GetIndices(i));
                }

                return result;
            }

        };

        REGISTER_COMMAND(Symmetrize);
        REGISTER_ARGUMENT(Symmetrize, 0, ArgumentType::TENSOR);
        REGISTER_REPEATED_ARGUMENT(Symmetrize, 1, ArgumentType::INDEX);

        CLI_COMMAND(AntiSymmetrize, true)

            std::string Help() const {
                return "AntiSymmetrize(<Tensors>, <Indices>)";
            }

            static bool Cachable() {
                return false;
            }

            TensorContainer Execute() const {
                return API::AntiSymmetrize(GetTensors(0), GetIndices(1));
            }

        };

        REGISTER_COMMAND(AntiSymmetrize);
        REGISTER_ARGUMENT(AntiSymmetrize, 0, ArgumentType::TENSOR);
        REGISTER_ARGUMENT(AntiSymmetrize, 1, ArgumentType::INDEX);

        CLI_COMMAND(ExchangeSymmetrize, true)

            std::string Help() const {
                return "ExchangeSymmetrize(<Tensors>, <Indices>)";
            }

            static bool Cachable() {
                return true;
            }

            TensorContainer Execute() const {
                return API::ExchangeSymmetrize(GetTensors(0), GetIndices(1));
            }

        };

        REGISTER_COMMAND(ExchangeSymmetrize);
        REGISTER_ARGUMENT(ExchangeSymmetrize, 0, ArgumentType::TENSOR);
        REGISTER_ARGUMENT(ExchangeSymmetrize, 1, ArgumentType::INDEX);

        CLI_COMMAND(BlockSymmetrize, true)

            std::string Help() const {
                return "BlockSymmetrize(<Tensors>, <Indices>, ...)";
            };

            static bool Cachable() {
                return true;
            }

            TensorContainer Execute() const {
                std::vector<Indices> indices;
                for (int i=1; i<Size(); i++) {
                    indices.push_back(GetIndices(i));
                }
                return API::BlockSymmetrize(GetTensors(0), indices);
            }

        };

        REGISTER_COMMAND(BlockSymmetrize);
        REGISTER_ARGUMENT(BlockSymmetrize, 0, ArgumentType::TENSOR);
        REGISTER_REPEATED_ARGUMENT(BlockSymmetrize, 1, ArgumentType::INDEX);


        CLI_COMMAND(IsSymmetric, false)

            std::string Help() const {
                return "IsSymmetric(<Tensors>, <Indices>)";
            }

            static bool Cachable() {
                return false;
            }

            TensorContainer Execute() const {
                auto tensors = GetTensors(0);
                auto indices = GetIndices(1);

                for (auto& tensor : tensors) {
                    if (!API::IsSymmetric(tensor, indices)) {
                        std::cout << "   \033[32m" << "false" << "\033[0m" << std::endl;
                        std::cout << "   \033[32m" << tensor->ToString() << " is not." << std::endl;
                        return TensorContainer();
                    }
                }

                std::cout << "  \033[32m" << "true" << "\033[0m" << std::endl;
                return TensorContainer();
            }

        };

        REGISTER_COMMAND(IsSymmetric);
        REGISTER_ARGUMENT(IsSymmetric, 0, ArgumentType::TENSOR);
        REGISTER_ARGUMENT(IsSymmetric, 1, ArgumentType::INDEX);

    }
}