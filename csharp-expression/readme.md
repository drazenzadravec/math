# C# Math Expression

C# math expression evaluator


### Usage
`
using Nequeo.Math;

Nequeo.Math.MathGenerics<string> exp = new Nequeo.Math.MathGenerics<string>();
double result  = exp.Expression<Double>("cos(x) * sin(x) * sqrt(x) * pi", 3.0, "x");
`
