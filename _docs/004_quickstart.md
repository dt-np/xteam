---
title: 004 - Quick Start 
use_math: true 
---

**Contents**
* TOC
{:toc}

## Distributed Analysis Scheme 

What is the "Distributed Analysis Scheme"? Here is a [talk](https://indico.ihep.ac.cn//event/6253/session/7/contribution/30/material/slides/0.pdf) by [Xin](/members/Xin_Shi). 

## Common Tools for new comers 

Here is a nice [talk](https://indico.ihep.ac.cn/event/7614/session/9/material/0/0.pdf) given by [Suyu](/members/Suyu_Xiao/). 

## MarkDown Syntax 

How to write the MarkDown page like in this web? One can check [here](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet). 

## MathJax 

Just need to set the following in the page: 

```yaml
---
use_math: true 
---
```

the the following LaTeX code

```tex
$$
\kappa=\frac{\int D(E) \phi(E) d E}{95 M e V m b \cdot \Phi}=\frac{\Phi_{e q}}{\Phi}
$$
```
will generate: 

$$
\kappa=\frac{\int D(E) \phi(E) d E}{95 M e V m b \cdot \Phi}=\frac{\Phi_{e q}}{\Phi}
$$

this one

```tex
Calculate the induced current on the targeted electrode: $$i(t) = \vec{E_w}(\vec{x}) \cdot \vec{v}(\vec{x},t) \cdot q$$
```
will generate:

Calculate the induced current on the targeted electrode: $$i(t) = \vec{E_w}(\vec{x}) \cdot \vec{v}(\vec{x},t) \cdot q$$
