//
// Created by jinhai on 23-2-7.
//

#pragma once

#include "expression/base_expression.h"
#include "expression_state.h"
#include "expression/reference_expression.h"

namespace infinity {

class ExpressionEvaluator {
public:
    void
    Execute(const SharedPtr<BaseExpression>& expression,
            SharedPtr<ExpressionState>& state,
            const Vector<SharedPtr<DataBlock>>& input_data_block,
            Vector<SharedPtr<ColumnVector>>& output_column_vector);

    void
    Execute(const SharedPtr<BaseExpression>& expr,
            SharedPtr<ExpressionState>& state,
            Vector<SharedPtr<ColumnVector>>& output_column_vector);

    void
    Execute(const SharedPtr<AggregateExpression>& expr,
            SharedPtr<ExpressionState>& state,
            Vector<SharedPtr<ColumnVector>>& output_column_vector);

    void
    Execute(const SharedPtr<CastExpression>& expr,
            SharedPtr<ExpressionState>& state,
            Vector<SharedPtr<ColumnVector>>& output_column_vector);

    void
    Execute(const SharedPtr<CaseExpression>& expr,
            SharedPtr<ExpressionState>& state,
            Vector<SharedPtr<ColumnVector>>& output_column_vector);

    void
    Execute(const SharedPtr<ConjunctionExpression>& expr,
            SharedPtr<ExpressionState>& state,
            Vector<SharedPtr<ColumnVector>>& output_column_vector);

    void
    Execute(const SharedPtr<ColumnExpression>& expr,
            SharedPtr<ExpressionState>& state,
            Vector<SharedPtr<ColumnVector>>& output_column_vecto);

    void
    Execute(const SharedPtr<FunctionExpression>& expr,
            SharedPtr<ExpressionState>& state,
            Vector<SharedPtr<ColumnVector>>& output_column_vector);

    void
    Execute(const SharedPtr<BetweenExpression>& expr,
            SharedPtr<ExpressionState>& state,
            Vector<SharedPtr<ColumnVector>>& output_column_vector);

    void
    Execute(const SharedPtr<ValueExpression>& expr,
            SharedPtr<ExpressionState>& state,
            Vector<SharedPtr<ColumnVector>>& output_column_vector);

    void
    Execute(const SharedPtr<ReferenceExpression>& expr,
            SharedPtr<ExpressionState>& state,
            Vector<SharedPtr<ColumnVector>>& output_column_vector);

private:
    Vector<SharedPtr<DataBlock>> input_data_blocks_;
    bool in_aggregate_{false};
};

}