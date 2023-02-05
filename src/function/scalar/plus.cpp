//
// Created by jinhai on 23-1-10.
//

#include "plus.h"
#include "function/scalar_function.h"
#include "function/scalar_function_set.h"

namespace infinity {

struct PlusFunction {
    template<typename TA, typename TB>
    static inline bool
    Run(TA value, TB &result) {
        NotImplementError("Not implemented plus function")
    }
};

template<>
inline bool
PlusFunction::Run(MixedT value, MixedT &result) {
    if (value.type == MixedValueType::kInteger || value.type == MixedValueType::kFloat) {
        result = value;
        return true;
    } else {
        result.type = MixedValueType::kNull;
        return false;
    }
}

void
RegisterPlusFunction(const UniquePtr<Catalog> &catalog_ptr) {
    String func_name = "+";

    SharedPtr<ScalarFunctionSet> function_set_ptr = MakeShared<ScalarFunctionSet>(func_name);

    // Plus operator
    ScalarFunction plus_int8(
            func_name,
            {DataType(LogicalType::kTinyInt)},
            DataType(LogicalType::kTinyInt),
            &ScalarFunction::NoOpFunction);
    function_set_ptr->AddFunction(plus_int8);

    ScalarFunction plus_int16(
            func_name,
            {DataType(LogicalType::kSmallInt)},
            DataType(LogicalType::kSmallInt),
            &ScalarFunction::NoOpFunction);
    function_set_ptr->AddFunction(plus_int16);

    ScalarFunction plus_int32(
            func_name,
            {DataType(LogicalType::kInteger)},
            DataType(LogicalType::kInteger),
            &ScalarFunction::NoOpFunction);
    function_set_ptr->AddFunction(plus_int32);

    ScalarFunction plus_int64(
            func_name,
            {DataType(LogicalType::kBigInt)},
            DataType(LogicalType::kBigInt),
            &ScalarFunction::NoOpFunction);
    function_set_ptr->AddFunction(plus_int64);

    ScalarFunction plus_int128(
            func_name,
            {DataType(LogicalType::kHugeInt)},
            DataType(LogicalType::kHugeInt),
            &ScalarFunction::NoOpFunction);
    function_set_ptr->AddFunction(plus_int128);

    ScalarFunction plus_float(
            func_name,
            {DataType(LogicalType::kFloat)},
            DataType(LogicalType::kFloat),
            &ScalarFunction::NoOpFunction);
    function_set_ptr->AddFunction(plus_float);

    ScalarFunction plus_double(
            func_name,
            {DataType(LogicalType::kDouble)},
            DataType(LogicalType::kDouble),
            &ScalarFunction::NoOpFunction);
    function_set_ptr->AddFunction(plus_double);

    ScalarFunction plus_decimal16(
            func_name,
            {DataType(LogicalType::kDecimal16)},
            DataType(LogicalType::kDecimal16),
            &ScalarFunction::NoOpFunction);
    function_set_ptr->AddFunction(plus_decimal16);

    ScalarFunction plus_decimal32(
            func_name,
            {DataType(LogicalType::kDecimal32)},
            DataType(LogicalType::kDecimal32),
            &ScalarFunction::NoOpFunction);
    function_set_ptr->AddFunction(plus_decimal32);

    ScalarFunction plus_decimal64(
            func_name,
            {DataType(LogicalType::kDecimal64)},
            DataType(LogicalType::kDecimal64),
            &ScalarFunction::NoOpFunction);
    function_set_ptr->AddFunction(plus_decimal64);

    ScalarFunction plus_decimal128(
            func_name,
            {DataType(LogicalType::kDecimal128)},
            DataType(LogicalType::kDecimal128),
            &ScalarFunction::NoOpFunction);
    function_set_ptr->AddFunction(plus_decimal128);

    ScalarFunction plus_mixed(
            func_name,
            {DataType(LogicalType::kMixed)},
            DataType(LogicalType::kMixed),
            &ScalarFunction::UnaryFunctionWithFailure<MixedT, MixedT, PlusFunction>);
    function_set_ptr->AddFunction(plus_mixed);

    catalog_ptr->AddFunctionSet(function_set_ptr);
}

}