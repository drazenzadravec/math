// math
// https://mathjs.org/index.html
// https://mathjs.org/docs/getting_started.html
// https://cdnjs.com/libraries/mathjs
import * as math from 'mathjs';
// import { sqrt } from 'mathjs' specific functions
export const handler = async (event) => {
    let response;
    // get math result
    let result = await mathExpression(event.expression);
    // response.
    response = {
        statusCode: 200,
        body: result
    };
    return response;
};
/**
* get the math expression
* @param {string}	expression  the context.
* @param {any}	options  the format options.
* @returns {Promise<any>} the response.
*/
export async function mathExpression(expression, options) {
    let result = "";
    try {
        let ans = math.evaluate(expression);
        // if format options
        if (options) {
            result = math.format(ans, options);
        }
        else {
            result = math.format(ans);
        }
    }
    catch (e) {
        result = "error";
    }
    return {
        result: result,
        options: options
    };
}
