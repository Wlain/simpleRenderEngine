# 凹凸贴图

| 年代 |              算法               | 思想                                                                                                          |  
|----|:-----------------------------:|:------------------------------------------------------------------------------------------------------------|
| 1978 |     Bump mapping<br/>凹凸贴图     | 没有修改顶点的位置，计算顶点光强时，不是直接使用原始法向量，而是加一个扰动得到修改的法向量                                                               |
| 1984 | Displacement mapping<br/>移位贴图 | 直接做用于顶点，根据displacement map中对应顶点的像素值，使得顶点沿着法向移动，产生真正的<br/>**凹凸表面**                                           |
| 1996 |    Normal mapping<br/>法线贴图    | 没有修改顶点的位置，通过hight map获得法向量信息，而且对应的RGB信息可以表示向量的XYZ，利用<br/>这个信息计算光强，产生凹凸阴影的效果                                 |
| 2001 |   Parallax mapping<br/>视差贴图   | 没有修改顶点的位置，通过视线和height map的计算，陡峭的视角就给顶点更多的位移，平缓的就给较小<br/>的位移，通过视差获取更强的立体感。即利用height map进行了近似的texture offset。 |
| 2005 |    Relief mapping<br/>浮雕贴图    | 没有修改顶点的位置，更精确地找出观察者的视线与高度的交点，对应的纹理坐标则是位移的距离, 视线更精确的位移                                                       |