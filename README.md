warp-paper
======
'Accelerating GPU Workload Simulation using Microsoft WARP'; a study into the performance of WARP (Windows Advanced Rasterization Platform) - a high-speed software rasterizer introduced by Microsoft in the Direct3D 11 runtime.

---

Click [here](http://bit.ly/MicrosoftWarpPdf) for a compiled version of the article.

Abstract
------

A convenient approach toward more transparent debugging and profiling of GPU-accelerated applications is to simulate GPU-bound workloads on CPUs. This approach is also applicable in situations where target hardware is simply not available, as is often the case with server-side applications, or would require too many system resources to initialize. However, when simulating GPU-bound workloads on CPUs, one may experience severe performance losses due to computational overhead.

Consequently, the subject of this study is performance variations between three device drivers of the DirectX framework; using DirectCompute and the high speed software rasterizer WARP (Windows Advanced Rasterization Platform). The performance of WARP is compared to that of traditional GPU hardware acceleration and the standard driver for software rasterization - the Reference Device Driver.

Experimental results show a major performance boost when compared to that of software rasterization using the reference device driver, indicating that performance losses traditionally obstructing simulation of throughput-oriented workloads on CPUs may be sufficiently amended by technologies, such as WARP, to the degree that simulation may be considered viable for extended use above and beyond that of current in-development utilities.

BibTeX
------

```latex
@inproceedings{nilsson:warp:2014,
    author = {Nilsson, Eric},
    title = {Accelerating GPU Workload Simulation using Microsoft WARP},
    editor = {Dickinson, Patrick},
    booktitle = {15th International Conference on Intelligent Games and Simulation},
    number = {15},
    pages = {115--120},
    month = {September},
    year = {2014},
    organization = {University of Lincoln},
    isbn = {978-90-77381-85-4},
    publisher = {EUROSIS-ETI},
    series = {GAME-ON},
}
```
