>*可参考[LaTeX公式手册](https://www.cnblogs.com/1024th/p/11623258.html)*
# Basic Structure

```latex
\documentclass{article}
\begin{document}
text
\end{document}
```
# Grammars

## 2.1 Basic Grammars
1. comment: begin with `%`
2. quotation: use  `` ` `` on the left side, and use `'` on the right side. (or double `` ` `` on the left side and double `'` on the right side)
3. some special characters %, #, &, $: precede it with a backslash, for example \\%
4. $: mark mathematics in text, like $\theta=x^2$
5. 省略号：`\ldots`
6. display equations: use 
```latex
\begin{equation}
\Theta=\sum_{k=1}^n\theta_k
\end{equation}
```
7. itemize environment:
```latex
\begin{itemize}
\item class1
\item class2
\end{itemize}
```
8. enumerate environment:
   take itemize environment for example
```latex
\begin{enumerate}
\item biscuit
\item cookies
\end{enumerate}
```
9. equation*: for unmunbered equations

---
## 2.2 Packages

```latex
\usepackage{amsmath} % to use equation*, operatorname, align, align*
\usepackage{ctex} % to use Chinese
```

---
## 2.3 Mathematics

1. use caret `^` for superscripts and underscore `_` for subscripts
$$
\sum_{k=1}^n \omega_k^{k^2}
$$
2. Greek letters:
	- $\alpha$    
	- $\beta$    
	- $\omega$   $\Omega$
	- $\delta$    $\Delta$
	- $\gamma$    $\Gamma$
	- $\epsilon$
	- $\zeta$
	- $\eta$
	- $\theta$    $\Theta$
	- $\lambda$    $\Lambda$
	- $\mu$
	- $\xi$    $\Xi$
	- $\pi$    $\Pi$
	- $\sigma$    $\Sigma$
	- $\rho$
	- $\phi$    $\Phi$
	- $\varphi$
	- $\psi$    $\Psi$
	- $\varsigma$
	- $\nu$
	- $\iota$
	- $\tau$
	- $\upsilon$
	- $\chi$
1.  common notations: learn it at [[LaTeX常用数学符号|common notations]]
2. Use `\begin{equation}`and`\end{equation}`to show a big equation
```latex
\begin{equation}
	\omega = 2\theta
\end{equation}
```
$$
\omega = 2 \theta
$$
And use `\begin{equation*}` and `\end{euqation*}` to show a unnumbered equation
5. Use `\frac` for fractions:
```latex
\begin{equation*}
	\frac{x^2}{y}
\end{equation*}
```
$$
\frac{x^2}{y}
$$
6. Use `\operatorname` for functions
```latex
\begin{equation}
\operatorname{f_n}(x)
\end{equation}
```
$$
\operatorname{f_n}(x)
$$
7. Use `\align*` for a sequence of equations:
```latex
\begin{align*}
(x + 1)^3 &= (x + 1)(x + 1)(x + 1)\\ % use a double backslash \\ to start a new row
&= x^3 + 3 x^2 + 3 x + 1 % use & on the left of =
\end{align*}
```
$$
\begin{align*}
(x + 1)^3 &= (x+1)(x+1)(x+1)\\
&= x^3+3x^2+3x+1
\end{align*}
$$
8. Use `\infty` for $\infty$
9. 

# Structured documents
## 3.1 Title and abstract

```latex
\documentclass{article} % the class of the document
\usepackage{amsmath}
\usepackage{ctex} % use packages

\title{The Title}

\author{The Author}

\date{\today} % tell the compiler about the title

\begin{document}
\maketitle % to really create the title

\begin{abstract}
abstract goes there \ldots
\end{abstract}

\end{document}
```

## 3.2 Sections and Subsections

1. use `\section{sectionName}` or `\subsection{subsectionName}` to create the sections
```latex
\section{Introduction}
The problem of \ldots
\section{Method}
We investigated \ldots
\subsection{Preparation}
\subsetion{Data Collection}
\section{Results}
\section{Conclusion}
\end{document}
```

## 3.3 Labels and Cross-References

>*Use `\label` and `\ref` for automatic numbering*
>*Use `\eqref` in package `amsmath` for referencing equations*

e.g:
```latex
\documentclass{article}
\usepackage{amsmath} % to use \eqref

\title{The Title}
\author{The Author}

\begin{document}
\maketitle

\section{Introduction}
\label{sec:intro}
In Section \ref{sec:method}, we \ldots

\section{Method}
\label{sec:method}

\begin{equation}
\label{eq:euler}
e^{i\pi} + 1 = 0
\end{equation}

By equation \eqref{eq:euler}, we have \ldots

\end{document}
```

---
# Figures and Tables
## 4.1 Graphics
1. Require the package `graphicx`, which provides the `\includegraphics` command
2. format:
```latex
\includegraphics[Optional Arguments]{graghicName}
```
3. e.g:
```latex
\includegraphics[width = 0.5\textwidth, angle = 270]{gerbil}
```
It means the image named gerbil takes up 30% of the width of the surrounding text and rotates the angle of 270°
4. **Floats**: allow the LaTeX where the figure will go, e.g:
```latex
\documentclass{article}
\usepackage{graphicx}
\begin{document}

Figure \ref{fig:gerbil} shows that \ldots
\begin{figure}
\centering % center the figure
\includegraphics[width = 0.3\textwidth]{gerbil}
\caption{\label{fig:gerbil}Aww\ldots.} % use \caption to be referenced with \ref
\end{figure}

\end{document}
```

## 4.2 Tables
1. use the tabular environment from the package `tabularx`
2. e.g:
```latex
\begin{tabular}{lrr} % lrr means "left right right"
Item & Qty & Unit \$ \\ % use \\ to start a new line
Widget & 1 & 199.99 \\ % use & to seperate columns
Gadget & 2 & 399.99 \\
Cable & 3 & 19.99 \\
\end{tabular}
```
3. e.g:
```latex
\begin{tabular}{|l|r|r|} \hline % use |l|r|r| to show vertical lines
Item & Qty & Unit \$ \\ \hline % use \hline to show horizontal lines
Widget & 1 & 199.99 \\
Gadget & 2 & 399.99 \\
Cable & 3 & 19.99 \\ \hline
\end{tabular}
```
---
# 5. Bibliographies

