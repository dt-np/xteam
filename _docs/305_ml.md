---
title: 305 - Machine Learning 
use_math: true
---

**Contents**
* TOC
{:toc}


## Machine Learning 
### Support Vector Machines(SVMs)
Support Vector Machine is used to classify events, by dividing the dataset into two categories. As a typical algorithm of machine learning, it consists a vector-like training set  

$$\left\{(\mathbf{x_{1}},y_{1}),(\mathbf{x_{2}},y_{2}),...,(\mathbf{x_{N}},y_{N})\right\}$$ 

Here,$$y_{i}\in\left\{+1,-1\right\}$$,represents the category label. $$x_{i}\in \mathbb{R}^{d}$$ is the feature vector in vector space.

First, SVM constructs the sample data as d-dimensional feature vectors. Then the problem can be solved in this vector space by creating a so-called “hyperplane” dividing two regions. The support vectors is vectors which are closest to the hyperplane in vector space. 

A d-dimensional hyperplane can be expressed as $$\mathbf{w}\circ\mathbf{x}+b=0$$ .
 
$$\mathbf{w}$$ is a d-dimensional vector which determines the presence of hyperplane. With the fixed hyperplane, the other vectors(data points) $$(\mathbf{x}_{i},y_{i})$$ satisfy a condition of $$y_{i}(\mathbf{w}\circ\mathbf{x}_{i}+b)\geq1$$

The perpendicular distance of two support vectors divided by hyperplane is called margin, equivalent to $$\|\mathbf{w}\|^{-1}$$.To optimize the results of classification is to maximize the margin of categories. In other words, our classification task is to find a minimum of $$\|\mathbf{w}\|$$ in reality.[<sup>[1]</sup>](#refer-anchor-1)

Based on Lagrange multiplier method, we can successfully construct a Lagrangian and the problem transforms to

$$min\quad L=\frac{1}{2}||\mathbf{w}||^{2}-\Sigma_{i=1}^{N}\alpha_{i}(y_{i}(\mathbf{w}\circ\mathbf{x}_{i}+b)-1)$$

$$s.t.\quad\Sigma_{i=1}^{N}\alpha_{i}y_{i}=0$$

Here in Lagrangian , $$\alpha$$ is multiplier, and $$0\leq\alpha\leq C$$, $$C$$ is called penalty parameter. The constraint above ensures the KKT conditions.

By solving this optimization problem numerically, we get the optimal solution $$\alpha^{*}$$ and $$\mathbf{w}^{*}=\Sigma_{i=1}^{N}\alpha_{i}^{*}y_{i}x_{i}$$, $$b^{*}=y_{i}-\Sigma_{i=1}^{N}\alpha_{i}^{*}y_{i}(x_{i}x_{j})$$. The index j corresponds to $$\alpha_{j}>0$$ which is a random component of $$\alpha^{*}$$.

Finally, the decision function of classification is given as $$m=sign(\mathbf{w}^{*}\circ\mathbf{x}_{i}+b^{*})$$.

### Support Vector Machines with a quantum kernel method

The reason for using the kernel method is that the vectors we construct are not linearly separable in their own feature space. In this case, the hyperplane is hard to express.  

An efficient way to deal with this occasion is to consider a feature map from present feature space to a high-dimension space, which is called kernel method in classical computing.[<sup>[2]</sup>](#refer-anchor-2) Then the data shall be linearly separable. Researchers has founded that we can use the inner product of feature map to construct the classifier without knowing the specific mathematical expression. Generally, we call the inner product as kernel. However, due to the particular quantity for computing, it is nearly inaccessible to accomplish the mission. This is called “Curse of Dimensionality” by Richard E. Bellman.  

On the other hand, quantum space, also called “Hilbert space”, has a distinctive excellence to deal with the huge computing quantity. The probability of quantum state makes it possible to map any feature vectors in quantum space at the same time, which undoubtedly reduce the time complexity. Combining with quantum kernel method, it is easy to use SVM by mapping the data sample vectors into Hilbert space. [<sup>[3]</sup>](#refer-anchor-3)

### Variational Quantum Classification

Since the quantum kernel method has its talented advantage to deal with such complex classification task, a corresponding machine-learning algorithm based on quantum physics is necessary to be developed. The ultimate task for machine learning is to get a mature model, able to find out the best solution of a question after training with a number of datapoints. As mentioned above, SVMs train the vectors to determine the best location of hyperplane. While we apply kernel method mapping the datapoints from classical space to quantum space, hyperplane acts as an operator exerting on the quantum states. The expectation value of the operator for the quantum states(datapoints) determine whether to label them +1 or -1. In other words, we assign the label according to the outcome with the largest probability estimate. Therefore, it's needed to choose a cost function, by optimizing it the probability of assigning wrong label can be minimized. This quantum machine learning algorithm is called variational quantum classification.  

During the quantum computing process, quantum states were dealt by quantum circuit which consists a series of unitary gates. At the end of circuit, the measurement gates are needed to observe the probability performance of the output states. Like classical logic circuit, it is possible to utilize these unitary gates to realize algorithms in a quantum way. To apply the measurement gate sufficiently, the probability distribution from output states to their eigenstates usually shows the result of algorithm.

#### Variational Approach in Quantum Physics

It is accessible to use variational idea searching for the ground state of a system, especially when the interaction of components is hard to calculate as well as it is unable to give an exact eigen solution of Schrodinger equation. In this case, we usually randomly construct a wave function as trial function and get a beginning form of the average value of Hamiltonian. According to Ritz's variational method, the average value contains several undetermined parameters which is tunable. Then to acquire the energy value of the ground state, we should require its variation equals to zero, which is equivalent to the derivative of the average value with respect to each parameter equals to zero. In numerical simulation, SPSA or SPGD algorithm is available to handle the question. Therefore, the variational approach is reasonable both in physics and computing.

#### Quantum Circuit Classifier Using Variational Method

In quantum circuits, states are represented by a combination of 0 and 1 based on spin representation which means the eigen states are combined with 0,1. Characteristic of superposition allows circuit to deal with 2^n eigen states at the same time, while n is the number of qubits, increasingly improving the parallelism of computing.  

The score of classification for a training sample is assessed by a so-called cost function, which features the difference between measured values and practical labels. Thus the circuit we constructs should contains all parameters of cost function so that the calculation on a classical computer can give optimal parameters of cost function. Under these parameters, the model tends to be a valid classifier.  

Considering the operation towards quantum states in Hilbert space must be unitary, we use rotation gate to both encode the feature vectors and realize variational approach. When encode the input state, it is equivalent to use kernel method, mapping the previous sample vectors into 2^n-dimensional Hilbert space. Then the encoded states will be inputted into supervised learning circuit to measure the average value of Pauli-Z operator in order to evaluate the cost function. If the parameters in cost function aren't tuned well, a successive optimization would be conducted in classical computers. Consequently, this kind of feedback contributes a valid classifier.[<sup>[4]</sup>](#refer-anchor-4)

## Reference
<div id="refer-anchor-1"></div>
[1]Vojtech Havlicek, et al. Supervised learning with quantum-enhanced feature spaces. Nature, 2019, 567:209-212. <https://www.nature.com/articles/s41586-019-0980-2.pdf>

<div id="refer-anchor-2"></div>
[2]Boser, B. E., Guyon, I. M. & Vapnik, V. N. A training algorithm for optimal margin classifers. In Proc. 5th Annual Workshop on Computational Learning Theory 144–152 (ACM, 1992).<http://www.svms.org/training/BOGV92.pdf>

<div id="refer-anchor-3"></div>
[3]Maria Schuld. Quantum machine learning models are kernel methods.  <https://arxiv.org/pdf/2101.11020.pdf>

<div id="refer-anchor-4"></div>
[4]Koji Terashi, et al. Event Classification with Quantum Machine Learning in High-Energy Physics.  <https://arxiv.org/pdf/2002.09935.pdf>
