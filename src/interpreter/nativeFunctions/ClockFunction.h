//
// Created by kemal on 1/16/2024.
//

#ifndef MATURSKI_CLOCKFUNCTION_H
#define MATURSKI_CLOCKFUNCTION_H

#include <memory>
#include "Callable.h"
#include "ValueType.h"
#include "NumericValue.h"

RuntimeValuePtr clockNative(Interpreter* interpreter, std::vector<RuntimeValuePtr> args);
int clockArity();
std::shared_ptr<Callable> makeClockCallable();

#endif //MATURSKI_CLOCKFUNCTION_H
