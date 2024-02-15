
# 一、问题概述

>与[最大匹配问题相近](Algorithm/Graph/Maximum%20Flow.md#^b1f48e)，但此处待匹配元素具有偏好

> [!question] 稳定匹配问题
> 给定两个集合 $X$ 和 $Y$，满足条件：$\forall x \in X$，$x$ 对 $Y$ 中的元素具有“偏好”，即对有向边 $x\rightarrow y$ 有加权；对 $y \in Y$ 同理。现欲求 $X$ 和 $Y$ 之间的一个最佳匹配 $M$，使得 $M$ 满足：
> 1. $\forall (x,y) \in M$，其中 $x\in X$，$y\in Y$，存在边 $x \rightarrow y$ 与边 $y \rightarrow x$；
> 2. 对任意未匹配的对 $(x,y)$，均有 $x$ 较 $y$ 而言更“偏好” $M(x)$， $y$ 较 $x$ 而言更偏好 $M(y)$

# 二、算法实现

## Deferred Acceptance Algorithm

1. **条件**：对于给定的两个相同大小的集合 $X, Y$，其中任意一个集合的任意一个元素 $a$ 均对另一个集合中的元素具有给定的偏好。
2. 大致过程：当 $X$ 中有还未匹配的元素时，将其记为 $x$，按照 $x$ 的偏好顺序从高到低依次匹配 $Y$ 中的元素 $y$
	1. $y$ 未匹配过：直接将 $x$ 和 $y$ 进行匹配
	2. $y$ 已经匹配了元素 $x'$，若 $y$ 更偏好 $x$，则将 $x'$ 与 $y$ 取消匹配，将 $x$ 与 $y$ 进行匹配；若 $y$ 更偏好 $x'$，则继续遍历 $x$ 的偏好
	3. 进行步骤2.1和2.2，直到 $x$ 被匹配或 $Y$ 中无元素可以与 $x$ 匹配

伪代码实现：
```pseudo
DEFERRED-ACCEPTANCE(X, Y):
	unpairedX = X
	while !unpairedX.empty():
		select x from unpairedX
		for y in x's prefers by non-increasing order:
			if y is unpaired:
				pair x with y
			else if y prefers x better than its current pair:
				unpair y with its current pair
				pair x with y
				unpairedX.remove(x)	
```

为了加快在`x`的偏好中选择出未被匹配的`y`的速度，可以使用一个属性记录已经尝试将`x`与其偏好表上前`k`个`y`配对，在下一次想为`x`配对时，直接从`x`的第`k+1`个偏好开始配对即可