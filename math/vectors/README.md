### Vectors (you should probably know this already)

Basics:
- Vectors are directions with strength/length
- Can have any dimensions, but usually work with 2-4
- 2D vectors with 3 coordinates have the z coordinate at 0

Scalar operations:
- Arithmetic operations: we add/substract etc. the vector with a scalar
Example: (1,2,3) + (4,5,6) = (5,7,9)
- Negation: we take the vector and reverse the direction
Example: (1,2,3) = (-1,-2,-3)
- Length: Use the Pythagoras theorem, in 2D case sqrt(pow(x, 2), pow(y, 2)), in 3D case just add pow(z, 2) to the equation
Displayed as ||v||
- Normalizing a vector: This is called a unit vector. Divide the vector by its length. Useful if you only care about the direction.

Vector-vector multiplication:
- Two cases: dot product and cross product
- Dot product: v . k = ||v|| . ||k|| . cos theta
  - Defines the angle between two vectors
  - Used to test if two vectors are orthogonal or parallel to each other
- Cross product: In 3D space, two non-parallel vectors which produce a third vector
  - Learn some linear algebra to learn more about this
  - Formula: ![cross_product](https://external-content.duckduckgo.com/iu/?u=http%3A%2F%2Fspiff.rit.edu%2Fclasses%2Fphys216%2Fworkshops%2Fw10c%2Fangmom%2Feqn_cross_by_ijk.gif&f=1&nofb=1)