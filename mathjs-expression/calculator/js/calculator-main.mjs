import * as mainFunc from './main.mjs';
// setup math cal.
initMathCal();
/**
* setup math cal.
*/
function initMathCal() {
    // attach to execute.
    var calculatorSolver = document.getElementById('calculator_solver');
    calculatorSolver.addEventListener('click', () => {
        var inputExpression = document.getElementById('InputExpression');
        evaluateMathExpression(inputExpression.value);
    }, false);
}
/**
* evaluate math expression
* @param {string}	expression   the math expression.
*/
function evaluateMathExpression(expression) {
    // get current time.
    mainFunc.postJsonRequest("/api/math/exp", JSON.stringify({
        expression: expression
    }), (data) => {
        try {
            var mathResult = document.getElementById("OutputResult");
            mathResult.innerText = data.result;
        }
        catch (e) {
            // could not find element
            console.warn(e);
        }
    }, (error) => {
        console.error(error);
    });
}
