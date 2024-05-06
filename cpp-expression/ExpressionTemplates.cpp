/* Company :       Nequeo Pty Ltd, http://www.dznequeo.net/
*  Copyright :     Copyright � Nequeo Pty Ltd 2017 http://www.dznequeo.net/
*
*  File :          ExpressionTemplates.cpp
*  Purpose :       Expression Templates class.
*
*/

/*
Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

#include "stdafx.h"

#include "exprtk.hpp"

namespace Nequeo {
	namespace Math {

		///	<summary>
		///	Template calls container.
		///	</summary>
		class TemplateContainer
		{
		public:
			///	<summary>
			///	Expression template for open expression.
			///	</summary>
			template<typename T>
			inline T ExecuteOpen(const std::string& expressionString)
			{
				exprtk::symbol_table<T> symbol_table;
				symbol_table.add_constants();

				// Register the expression.
				exprtk::expression<T> expression;
				expression.register_symbol_table(symbol_table);

				// Compile the expression.
				exprtk::parser<T> parser;
				parser.compile(expressionString, expression);

				// Execute the expresion and return the result.
				return expression.value();
			}

			///	<summary>
			///	Expression template for single variable expression.
			///	</summary>
			template<typename T>
			inline T ExecuteExpression(const std::string& expressionString, T& x, const std::string& variableName)
			{
				// Add the vraibale.
				exprtk::symbol_table<T> symbol_table;
				symbol_table.add_constant(variableName, x);
				symbol_table.add_constants();

				// Register the expression.
				exprtk::expression<T> expression;
				expression.register_symbol_table(symbol_table);

				// Compile the expression.
				exprtk::parser<T> parser;
				parser.compile(expressionString, expression);

				// Execute the expresion and return the result.
				return expression.value();
			}

			///	<summary>
			///	Expression template for single variable expression.
			///	</summary>
			template<typename T>
			inline T ExecuteExpressionMulti(const std::string& expressionString, const std::map<std::string, T>& variables)
			{
				std::map<std::string, T>::template iterator var_Iter;

				// Add the vraibale.
				exprtk::symbol_table<T> symbol_table;

				// For each variable.
				for (const auto& vars : variables)
				{
					std::string varName = vars.first;
					T currentValue = vars.second;

					// Add the variable.
					symbol_table.add_constant(varName, currentValue);
				}

				symbol_table.add_constants();

				// Register the expression.
				exprtk::expression<T> expression;
				expression.register_symbol_table(symbol_table);

				// Compile the expression.
				exprtk::parser<T> parser;
				parser.compile(expressionString, expression);

				// Execute the expresion and return the result.
				return expression.value();
			}

			///	<summary>
			///	Expression template for single variable expression.
			///	</summary>
			template<typename T>
			inline T ExecuteExpressionDerivative(const std::string& expressionString, T& x, const std::string& variableName, const std::map<std::string, T>& variables)
			{
				std::map<std::string, T>::template iterator var_Iter;

				// Add the vraibale.
				exprtk::symbol_table<T> symbol_table;
				symbol_table.add_variable(variableName, x);

				// For each variable.
				for (const auto& vars : variables)
				{
					std::string varName = vars.first;
					T currentValue = vars.second;

					// Add the variable.
					symbol_table.add_constant(varName, currentValue);
				}

				symbol_table.add_constants();

				// Register the expression.
				exprtk::expression<T> expression;
				expression.register_symbol_table(symbol_table);

				// Compile the expression.
				exprtk::parser<T> parser;
				parser.compile(expressionString, expression);

				// Execute the expresion and return the result.
				return exprtk::derivative(expression, variableName);
			}

			///	<summary>
			///	Expression template for single variable expression.
			///	</summary>
			template<typename T>
			inline T ExecuteExpressionSecondDerivative(const std::string& expressionString, T& x, const std::string& variableName, const std::map<std::string, T>& variables)
			{
				std::map<std::string, T>::template iterator var_Iter;

				// Add the vraibale.
				exprtk::symbol_table<T>  symbol_table;
				symbol_table.add_variable(variableName, x);

				// For each variable.
				for (const auto& vars : variables)
				{
					std::string varName = vars.first;
					T currentValue = vars.second;

					// Add the variable.
					symbol_table.add_constant(varName, currentValue);
				}

				symbol_table.add_constants();

				// Register the expression.
				exprtk::expression<T> expression;
				expression.register_symbol_table(symbol_table);

				// Compile the expression.
				exprtk::parser<T> parser;
				parser.compile(expressionString, expression);

				// Execute the expresion and return the result.
				return exprtk::second_derivative(expression, variableName);
			}

			///	<summary>
			///	Expression template for single variable expression.
			///	</summary>
			template<typename T>
			inline T ExecuteExpressionThirdDerivative(const std::string& expressionString, T& x, const std::string& variableName, const std::map<std::string, T>& variables)
			{
				std::map<std::string, T>::template iterator var_Iter;

				// Add the vraibale.
				exprtk::symbol_table<T> symbol_table;
				symbol_table.add_variable(variableName, x);

				// For each variable.
				for (const auto& vars : variables)
				{
					std::string varName = vars.first;
					T currentValue = vars.second;

					// Add the variable.
					symbol_table.add_constant(varName, currentValue);
				}

				symbol_table.add_constants();

				// Register the expression.
				exprtk::expression<T> expression;
				expression.register_symbol_table(symbol_table);

				// Compile the expression.
				exprtk::parser<T> parser;
				parser.compile(expressionString, expression);

				// Execute the expresion and return the result.
				return exprtk::third_derivative(expression, variableName);
			}

			///	<summary>
			///	Expression template for single variable expression.
			///	</summary>
			template<typename T>
			inline T ExecuteExpressionIntegrate(const std::string& expressionString, T& x, const std::string& variableName, const T& a, const T& b, const std::map<std::string, T>& variables)
			{
				std::map<std::string, T>::template iterator var_Iter;

				// Add the vraibale.
				exprtk::symbol_table<T> symbol_table;
				symbol_table.add_variable(variableName, x);

				// For each variable.
				for (const auto& vars : variables)
				{
					std::string varName = vars.first;
					T currentValue = vars.second;

					// Add the variable.
					symbol_table.add_constant(varName, currentValue);
				}

				symbol_table.add_constants();

				// Register the expression.
				exprtk::expression<T> expression;
				expression.register_symbol_table(symbol_table);

				// Compile the expression.
				exprtk::parser<T> parser;
				parser.compile(expressionString, expression);

				// Execute the expresion and return the result.
				return exprtk::integrate(expression, variableName, a, b);
			}

			///	<summary>
			///	Expression template for single variable expression.
			///	</summary>
			template<typename T>
			inline bool ExecuteExpressionCompute(const std::string& expressionString, T& result)
			{
				// Execute the expresion and return the result.
				return exprtk::compute(expressionString, result);
			}

			///	<summary>
			///	Expression template for single variable expression.
			///	</summary>
			template<typename T>
			inline bool ExecuteExpressionCompute(const std::string& expressionString, const T& x, T& result)
			{
				// Execute the expresion and return the result.
				return exprtk::compute(expressionString, x, result);
			}

			///	<summary>
			///	Expression template for single variable expression.
			///	</summary>
			template<typename T>
			inline bool ExecuteExpressionCompute(const std::string& expressionString, const  T& x, const T& y, T& result)
			{
				// Execute the expresion and return the result.
				return exprtk::compute(expressionString, x, y, result);
			}

			///	<summary>
			///	Expression template for single variable expression.
			///	</summary>
			template<typename T>
			inline bool ExecuteExpressionCompute(const std::string& expressionString, const T& x, const T& y, const T& z, T& result)
			{
				// Execute the expresion and return the result.
				return exprtk::compute(expressionString, x, y, z, result);
			}
		};
	}
}