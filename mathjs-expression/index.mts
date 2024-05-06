// math
// https://mathjs.org/index.html
// https://mathjs.org/docs/getting_started.html
// https://cdnjs.com/libraries/mathjs
// D:\Development\Version2022\ThirdPartyTools\math\mathjs\*

import * as math from 'mathjs';
// import { sqrt } from 'mathjs' specific functions

export const handler = async (event: MathRequest): Promise<MathResponse> => {

	let response: MathResponse;

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
export async function mathExpression(expression: string, options?: any): Promise<any> {

	let result: string = "";
	try {
		let ans: any = math.evaluate(expression);

		// if format options
		if (options) {
			result = math.format(ans, options);
		}
		else {
			result = math.format(ans);
		}
	} catch (e) {
		result = "error";
	}
	return {
		result: result,
		options: options
	};
}

/**
* math request model.
*/
export interface MathRequest {
	readonly expression: string;
	readonly options?: any;
}

/**
* math response model.
*/
export interface MathResponse {
	readonly statusCode: number;
	readonly body: string;
}