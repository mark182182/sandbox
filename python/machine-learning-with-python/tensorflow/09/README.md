## Core Learning Algorithms: Clustering

### Notes:

- <b>Clustering</b>: Unsupervised learning algorithm, works for a very specific set of information, involves the grouping of data points
- Data points in different groups should have highly dissimilar properties and/or features
- Reference for algorihms: https://towardsdatascience.com/the-5-clustering-algorithms-data-scientists-need-to-know-a36d136ef68
- Basic algorihm of K-Means:
  - Step 1. Randomly pick K points to place K centroids
  - Step 2. Assign all of the data points to the centroids by distance. The closest centroid to a point is the one it is assigned to.
  - Step 3. Average all of the points belonging to each centroid to find the middle of those clusters (center of mass). Palce the corresponding centroids into that position.
  - Step 4. Reassign every point once again to the closest centroid
  - Step 5. Repeat steps 3-4 until no point changes which centroid it belongs to

### Questions:

Which of the following steps is <b>not</b> part of the K-Means algorithm?

- Shuffle the K points so they're redistributed randomly.
