# Genetic Programming
## Smooth Curve Fitting

Smooth curve fitting is the process of constructing a curve, or mathematical function, that approximately fits a series of data points.


In this assignment, you are given set of points and you will use the genetic algorithm to find the best coefficients to fit a curve (polynomial equation) to these points such that the distance between the polynomial and the points is minimum.

### Implementation Notes:

- Each coefficient is a floating point between [-10, 10].
- The fitness function is the mean square error (MSE). The best individual is the one with the smallest fitness function because we want to minimize MSE.
- Use tournament selection.
- Use 2-point crossover.
- Use non-uniform mutation.
- Given a file of M data sets (i.e. M test cases), for each case, print and save the list of coefficients and the total error. You must write the output to a file.

### Input File Structure:

- First line: M represents number of sets.
- Each set consists of: Line N D, where N is number of points and D is the requested polynomial degree. This is followed by N lines each one representing an (x, y) point.

### Input Example:
```
1
4 2
1 5
2 8
3 13
4 20
```

This example has 1 test case which has 4 points, and the requested degree is 2 (a0, a1, a2).

### Output File Structure:

- Consists of M lines, each line has D+1 coefficients followed by “Error =” Total Error.

### Output Example:

```
1.33, 0.12, 4.09, Error = 2.1563
```