#pragma once

#include <string>

#include <common/printable.hpp>
#include <common/uuid.hpp>

#include <tensor/scalar.hpp>

namespace Construction {
    namespace Tensor {

        using Common::Unique;
        using Common::Printable;

        /**
            \class Coefficient

            A coefficient is a
         */
        class Variable : public AbstractScalar, Unique<Variable, 101>, Construction::Common::Printable {
        public:
            Variable(const std::string& name) : name(name), Printable(name), AbstractScalar(AbstractScalar::VARIABLE) { }
            Variable(const std::string& name, const std::string& printed_text) : name(name), Printable(printed_text), AbstractScalar(AbstractScalar::VARIABLE) { }

            Variable(const Variable& other) : name(other.name), Printable(other.printed_text), Unique(other.uuid) { }
            //Variable(Variable&& other) : name(std::move(other.name)), Printable(std::move(other.printed_text)), uuid(std::move(other.uuid)) { }
        public:
            std::string GetName() const { return name; }
            void SetName(const std::string& name) { this->name = name; }
        public:
            virtual ScalarPointer Clone() const override {
                return ScalarPointer(new Variable(*this));
            }
        private:
            std::string name;
        };

    }
}