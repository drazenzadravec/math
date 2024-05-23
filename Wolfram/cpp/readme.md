C++ console app that can evaluate expressions by using the Wolfram Engine

### Usage
```cpp
.\MathWolfram.exe "Series[Sin[x], {x, 0, 15}]"
```

### Result
```cpp
     3    5      7       9        11          13             15
    x    x      x       x        x           x              x              16
x - -- + --- - ---- + ------ - -------- + ---------- - ------------- + O[x]
    6    120   5040   362880   39916800   6227020800   1307674368000
```



### Usage
```cpp
.\MathWolfram.exe "m = {{-2, 3}, {2, 1}}; b = {11, 9}; LinearSolve[m, b]"
```

### Result
```cpp
{2, 5}
```
