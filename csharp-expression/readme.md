# C# Math Expression

C# math expression evaluator

<a href="https://nequeo-cdn.s3.ap-southeast-2.amazonaws.com/docs/ScientificDocument.htm" target="_blank">Mathematical expression usage docs</a>

### Usage
```csharp
using Nequeo.Math;

Nequeo.Math.MathGenerics<string> exp = new Nequeo.Math.MathGenerics<string>();
double result = exp.Expression<Double>("cos(x) * sin(x) * sqrt(x) * pi", 3.0, "x");
double result1 = exp.Expression<Double>("((34.8 * 23) * sqrt(9.0)) + pi");

System.Collections.Generic.Dictionary<string, double> vars = new System.Collections.Generic.Dictionary<string, double>();
vars.Add("x", 2.7);
vars.Add("y", 5.7);
vars.Add("z", 5.7);
double result2 = exp.ExpressionMulti<Double>("2y^5 * 6x^2 * z * pi", vars);

double mean = exp.Expression<Double>(
    " var x[25] := {                     " +
    "                 1,  2,  3,  4,  5, " +
    "                 6,  7,  8,  9, 10, " +
    "                11, 12, 13, 14, 15, " +
    "                16, 17, 18, 19, 20, " +
    "                21, 22, 23, 24, 25  " +
    "              };                    " +
    "                                    " +
    " avg(x)");
double standardDeviation = exp.Expression<Double>(
    " var x[25] := {                     " +
    "                 1,  2,  3,  4,  5, " +
    "                 6,  7,  8,  9, 10, " +
    "                11, 12, 13, 14, 15, " +
    "                16, 17, 18, 19, 20, " +
    "                21, 22, 23, 24, 25  " +
    "              };                    " +
    "                                    " +
    " sqrt(sum([x - avg(x)]^2) / x[])    ");
```

### Result
```cpp
result = -0.76020547948559836
result1 = 2404.3415926535895
result2 = 9425573.4288132936
mean = 13
standardDeviation = 7.2111025509279782
```
